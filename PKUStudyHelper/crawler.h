#ifndef CRAWLER_H
#define CRAWLER_H

#include <QMap>
#include <QString>
#include <QJsonDocument>

// 调用Python脚本，返回QJsonDocument结果
QJsonDocument callPythonScript(const QString& functionName,
                               const QString& stuId,
                               const QString& password,
                               bool verifySSL = true);

// 获取课程表，返回格式为：{周几: {课时: 课程名}}
QMap<int, QMap<int, QString>> fetchSchedule(const QString& stuId,
                                            const QString& password,
                                            bool verifySSL = true);

// 获取GPA，ok指示是否转换成功
float fetchGPA(const QString& stuId,
               const QString& password,
               bool verifySSL = true,
               bool* ok = nullptr);

// 获取课程列表，返回格式为：{索引: 课程名}
QMap<int, QString> fetchCourses(const QString& stuId,
                                const QString& password,
                                bool verifySSL = true);

struct ParsedCourseInfo {
    QString name;
    QString classroom;
    QString teacher;
    QString remark;
    QString exam_info;
};

ParsedCourseInfo parseCourseInfo(const QString &info);

#endif // CRAWLER_H
