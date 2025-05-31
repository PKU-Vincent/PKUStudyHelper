#ifndef COURSEINFO_H
#define COURSEINFO_H

#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QVector>
#include <QString>
#include <QRegularExpression>
#include <algorithm>
#include<QSet>

struct CourseInfo {
    QString name;
    QString weekday;
    QVector<QString> periods;
    QString detail;
};

struct ParsedScheduleResult {
    QMap<QString, QVector<CourseInfo>> name_index;
    QMap<QString, QVector<CourseInfo>> time_index;
    QVector<QString> name_list;
};

// 仅保留函数声明
int parseStartPeriod(const QString& periodStr);
QString mergePeriods(const QVector<QString>& periods);
QVector<CourseInfo> parseSchedule(const QVector<QMap<QString, QString>>& scheduleEntries);
ParsedScheduleResult parseAndCategorizeSchedule(const QVector<QMap<QString, QString>>& scheduleEntries);

#endif
