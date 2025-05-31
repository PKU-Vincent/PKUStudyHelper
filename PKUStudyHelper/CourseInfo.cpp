#include "CourseInfo.h"

int parseStartPeriod(const QString& periodStr) {
    QRegularExpression rx("第(\\d+)");
    QRegularExpressionMatch match=rx.match(periodStr);
    if (match.hasMatch()) {
        return match.captured(1).toInt();
    }
    return 0;
}

QString mergePeriods(const QVector<QString>& periods) {
    static QMap<QString, int> numMap = {
        {"第一节", 1}, {"第二节", 2}, {"第三节", 3}, {"第四节", 4},
        {"第五节", 5}, {"第六节", 6}, {"第七节", 7}, {"第八节", 8},
        {"第九节", 9}, {"第十节", 10}, {"第十一节", 11}, {"第十二节", 12}
    };
    static QMap<int, QString> revMap;
    if (revMap.isEmpty()) {
        for (auto it = numMap.begin(); it != numMap.end(); ++it) {
            revMap[it.value()] = it.key();
        }
    }

    QVector<int> nums;
    for (const QString& p : periods) {
        if (numMap.contains(p)) {
            nums.append(numMap[p]);
        }
    }
    std::sort(nums.begin(), nums.end());

    QVector<QString> merged;
    if (nums.isEmpty()) return "";

    int start = nums[0];
    int prev = start;

    for (int i = 1; i < nums.size(); ++i) {
        int n = nums[i];
        if (n == prev + 1) {
            prev = n;
        } else {
            if (start == prev) {
                merged.append(revMap[start]);
            } else {
                QString s = revMap[start];
                QString e = revMap[prev];
                merged.append(s.left(2) + "-" + e.right(e.length()-1));
            }
            start = prev = n;
        }
    }
    if (start == prev) {
        merged.append(revMap[start]);
    } else {
        QString s = revMap[start];
        QString e = revMap[prev];
        merged.append(s.left(2) + "-" + e.right(e.length()-1));
    }

    return merged.join("，");
}

QVector<CourseInfo> parseSchedule(const QVector<QMap<QString, QString>>& scheduleEntries) {
    QVector<CourseInfo> courses;
    static const QMap<QString, QString> dayNameMap = {
        {"mon", "星期一"},
        {"tue", "星期二"},
        {"wed", "星期三"},
        {"thu", "星期四"},
        {"fri", "星期五"},
        {"sat", "星期六"},
        {"sun", "星期日"}
    };

    for (const auto& entry : scheduleEntries) {
        QString timeNum = entry.value("timeNum", "");
        for (auto it = dayNameMap.begin(); it != dayNameMap.end(); ++it) {
            QString dayCode = it.key();
            QString dayName = it.value();

            if (!entry.contains(dayCode)) continue;

            QString courseRaw = entry.value(dayCode).trimmed();
            if (courseRaw.isEmpty()) continue;

            QStringList lines = courseRaw.split('\n');
            QString courseName = lines.isEmpty() ? "" : lines[0].trimmed();
            QString courseDetail = lines.size() > 1 ? lines.mid(1).join('\n').trimmed() : "";

            QVector<QString> periods;
            if (timeNum.contains('-')) {
                QStringList parts = timeNum.split('-');
                if (parts.size() == 2) {
                    static QMap<QString, int> numMap = {
                        {"第一节", 1}, {"第二节", 2}, {"第三节", 3}, {"第四节", 4},
                        {"第五节", 5}, {"第六节", 6}, {"第七节", 7}, {"第八节", 8},
                        {"第九节", 9}, {"第十节", 10}, {"第十一节", 11}, {"第十二节", 12}
                    };
                    int s = numMap.value(parts[0], 0);
                    int e = numMap.value(parts[1], 0);
                    for (int i = s; i <= e; ++i) {
                        for (auto key : numMap.keys()) {
                            if (numMap[key] == i) {
                                periods.append(key);
                                break;
                            }
                        }
                    }
                }
            } else {
                periods.append(timeNum);
            }

            CourseInfo c{courseName, dayName, periods, courseDetail};
            courses.append(c);
        }
    }
    return courses;
}

ParsedScheduleResult parseAndCategorizeSchedule(const QVector<QMap<QString, QString>>& scheduleEntries) {
    QVector<CourseInfo> parsedCourses = parseSchedule(scheduleEntries);

    // 先整体按（星期+起始节次）排序
    static QMap<QString, int> weekdayOrder = {
        {"星期一", 1}, {"星期二", 2}, {"星期三", 3},
        {"星期四", 4}, {"星期五", 5}, {"星期六", 6}, {"星期日", 7}
    };

    std::sort(parsedCourses.begin(), parsedCourses.end(), [](const CourseInfo& a, const CourseInfo& b){
        int dayA = weekdayOrder.value(a.weekday, 0);
        int dayB = weekdayOrder.value(b.weekday, 0);
        if (dayA != dayB) return dayA < dayB;

        int startA = a.periods.isEmpty() ? 0 : parseStartPeriod(a.periods.first());
        int startB = b.periods.isEmpty() ? 0 : parseStartPeriod(b.periods.first());
        return startA < startB;
    });

    ParsedScheduleResult result;
    QSet<QString> added;

    // 依次插入两个索引，顺序保持排序后顺序
    for (const CourseInfo& c : parsedCourses) {
        result.name_index[c.name].append(c);
        result.time_index[c.weekday].append(c);
        if(!added.contains(c.name))
        {
            result.name_list.append(c.name);
            added.insert(c.name);
        }
    }

    return result;
}
