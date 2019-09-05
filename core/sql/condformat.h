#ifndef CONDFORMAT_H
#define CONDFORMAT_H
#include <string>
#include "query.h"

// Conditional formatting for given format to table cells based on a specified condition.
class CondFormat
{
public:
    CondFormat() = default;
    explicit CondFormat(const std::string& filter, const std::string& encoding = std::string());

    static std::string filterToSqlCondition(const std::string& value, PG_TYPES column_type, const std::string& encoding = std::string());

private:
    std::string m_sqlCondition;
    std::string m_filter;

public:
    [[nodiscard]] std::string sqlCondition() const
    {
        return m_sqlCondition;
    }
    [[nodiscard]] std::string filter() const
    {
        return m_filter;
    }

};

#endif // CONDFORMAT_H
