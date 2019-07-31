#ifndef CONDFORMAT_H
#define CONDFORMAT_H

#include <QString>
#include <QColor>
#include "core/connection/pdb.h"
// Conditional formatting for given format to table cells based on a specified condition.
class CondFormat
{
public:
    CondFormat() = default;
    explicit CondFormat(const QString& filter, QColor  foreground, QColor  background, const QString& encoding = QString());

    static QString filterToSqlCondition(const QString& value, PG_TYPES column_type, const QString& encoding = QString());

private:
    QString m_sqlCondition;
    QString m_filter;
    QColor m_bgColor;
    QColor m_fgColor;

public:
    QString sqlCondition() const
    {
        return m_sqlCondition;
    }
    QString filter() const
    {
        return m_filter;
    }
    QColor backgroundColor() const
    {
        return m_bgColor;
    }
    QColor foregroundColor() const
    {
        return m_fgColor;
    }

};

#endif // CONDFORMAT_H
