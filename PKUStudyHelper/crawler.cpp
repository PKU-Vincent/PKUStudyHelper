#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QRegularExpression>

// 公共函数：调用Python脚本获取数据,并将数据从JSON解析为Qt可用的QJsonDocument对象
QJsonDocument callPythonScript(const QString& functionName,
                               const QString& stuId,
                               const QString& password,
                               bool verifySSL = true) {
    QProcess process;
    QString python = "python";
    QString scriptPath = "new_course.py";  //运行的时候切换成实际的路径

#ifdef Q_OS_WIN
    python = "python.exe";
#elif defined(Q_OS_MACOS) || defined(Q_OS_LINUX)
    python = "python3";
#endif

    QStringList arguments;
    arguments << functionName << stuId << password << (verifySSL ? "true" : "false");

    process.start(python, QStringList() << scriptPath << arguments);
    if (!process.waitForFinished(30000)) { // 30秒超时
        return QJsonDocument::fromJson(R"({"error": "Timeout waiting for script"})");
    }


    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
        QString error = "Script error: " + process.readAllStandardError();
        return QJsonDocument::fromJson(QString(R"({"error": "%1"})").arg(error).toUtf8());
    }

    QByteArray output = process.readAllStandardOutput();
    QByteArray errorOutput = process.readAllStandardError();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(output, &parseError);

    qDebug() << "Python 标准输出:" << QString::fromUtf8(output);
    if (!errorOutput.isEmpty()) {
        qDebug() << "Python错误输出:" << errorOutput;
    }

    if (parseError.error != QJsonParseError::NoError) {
        return QJsonDocument::fromJson(R"({"error": "Invalid JSON output from script"})");
    }

    return doc;
}

// 1. 获取课程表
QMap<int, QMap<int, QString>> fetchSchedule(const QString& stuId,
                                            const QString& password,
                                            bool verifySSL = true) {
    QJsonDocument doc = callPythonScript("get_schedule", stuId, password, verifySSL);
    QMap<int, QMap<int, QString>> schedule;//{周几：{课时：课程信息，}，}

    if (doc.object().contains("error")) {
        qDebug() << "Error fetching schedule:" << doc.object()["error"].toString();
        return schedule;
    }

    QJsonObject jsonSchedule = doc.object();
    for (int day = 1; day <= 7; day++) {
        QString dayKey = QString::number(day);//将整数转换为字符串形式
        if (jsonSchedule.contains(dayKey)) {
            QJsonObject dayObj = jsonSchedule[dayKey].toObject();//一天有课的所有课时
            for (auto period = dayObj.begin(); period != dayObj.end(); period++) {//遍历所有有课的课时
                int periodNum = period.key().toInt();//转换为数字
                QString courseinfo = period.value().toString();//解析该课时的课程信息
                schedule[day][periodNum] = courseinfo;//记录在schedule中
            }
        }
    }

    return schedule;
}

// 2. 获取GPA
float fetchGPA(const QString& stuId,
               const QString& password,
               bool verifySSL = true,
               bool* ok = nullptr) {
    QJsonDocument doc = callPythonScript("get_gpa", stuId, password, verifySSL);//这个doc形式是{“gpa":一个浮点数}

    if (ok) *ok = false;
    if (doc.object().contains("error")) {
        qDebug() << "Error fetching GPA:" << doc.object()["error"].toString();
        return 0.0f;
    }

    if (doc.object().contains("gpa")) {
        bool conversionOk = false;
        float gpa = doc.object()["gpa"].toString().toFloat(&conversionOk);
        if (ok) *ok = conversionOk;
        return conversionOk ? gpa : 0.0f;
    }

    qDebug() << "GPA field not found in response";
    return 0.0f;
}

// 3. 获取课程列表
QMap<int, QString> fetchCourses(const QString& stuId,
                                const QString& password,
                                bool verifySSL = true) {
    QJsonDocument doc = callPythonScript("get_courses", stuId, password, verifySSL);
    //此处doc的结构是{“数字”：[课程名，教学网网址],}
    QMap<int, QString> courses;

    if (doc.object().contains("error")) {
        qDebug() << "Error fetching courses:" << doc.object()["error"].toString();
        return courses;
    }

    if (doc.isObject()) {
        QJsonObject coursesObj = doc.object();
        for (auto keyIt = coursesObj.begin(); keyIt != coursesObj.end(); keyIt++) {
            // 获取索引并转换
            bool ok;
            int index = keyIt.key().toInt(&ok);
            if (!ok) continue; // 跳过无效键

            // 获取值数组
            if (keyIt.value().isArray()) {
                QJsonArray courseArray = keyIt.value().toArray();

                // 确保数组至少有一个元素（课程名称）
                if (courseArray.size() > 0) {
                    courses[index] = courseArray[0].toString();
                }
            }
        }
    } else {
        qDebug() << "Unexpected response format: expected object";
    }

    return courses;
}

struct ParsedCourseInfo {
    QString name;
    QString classroom;
    QString teacher;
    QString remark;
    QString exam_info;
};

QString extractClassroom(const QString &info) {
    QRegularExpression classroomRegex(R"(([一二三四五六七八九十理文地]教[0-9]{0,4}))");
    QRegularExpressionMatchIterator it = classroomRegex.globalMatch(info);

    while (it.hasNext()) {
        auto match = it.next();
        QString room = match.captured(1).trimmed();
        if (!room.isEmpty()) {
            return room;  // 只返回第一个匹配的教室
        }
    }
    return "";  // 没有匹配到教室返回空字符串
}

ParsedCourseInfo parseCourseInfo(const QString &info) {
    ParsedCourseInfo result;

    QStringList lines = info.split(QRegularExpression("[\\n\\r]"), Qt::SkipEmptyParts);
    if (!lines.isEmpty()) {
        result.name = lines[0].trimmed();
    }

    QRegularExpression teacherRegex(u8R"(教师[:：]([\p{Han}，,、\s]+))");
    QRegularExpression remarkRegex(u8R"(备注[:：]([^\n]*)?)");
    QRegularExpression examRegex(u8R"(考试信息[:：]([^\n]*)?)");

    QRegularExpressionMatch match;

    // 提取教室（只取第一个）
    result.classroom = extractClassroom(info);

    if ((match = teacherRegex.match(info)).hasMatch()) {
        result.teacher = match.captured(1).trimmed();
    }
    if ((match = remarkRegex.match(info)).hasMatch()) {
        result.remark = match.captured(1).trimmed();
    }
    if ((match = examRegex.match(info)).hasMatch()) {
        result.exam_info = match.captured(1).trimmed();
    }

    return result;
}
