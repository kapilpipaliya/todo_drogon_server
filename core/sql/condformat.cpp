#include "condformat.h"
#include <boost/algorithm/string/replace.hpp>
#include <string>
#include <utility>
#include "../strfns.h"
#include "query.h"
namespace sql {

CondFormat::CondFormat(const std::string& filter, const std::string& encoding)
    : m_filter(filter) {
  if (!filter.empty())
    m_sqlCondition =
        filterToSqlCondition(filter, sql::PG_TYPES::TEXT, encoding);
}

std::string CondFormat::filterToSqlCondition(const std::string& value,
                                             sql::PG_TYPES column_type,
                                             const std::string& encoding) {
  // Check for any special comparison operators at the beginning of the value
  // string. If there are none default to LIKE.
  std::string op = "LIKE";
  std::string val;
  std::string val2;
  std::string escape;
  bool numeric = false;
  bool ok = false;
  std::size_t* pos = nullptr;
  std::size_t* numericp = nullptr;

  // range/BETWEEN operator
  if (value.find('~') != std::string::npos) {
    auto sepIdx = value.find('~');
    val = value.substr(0, sepIdx);
    val2 = value.substr(sepIdx + 1);
    float valf = stof(val, pos);
    if (pos) {
      float val2f = stof(val2, pos);
      ok = valf < val2f;
    }
  }
  if (ok) {
    op = "BETWEEN";
    numeric = true;
  } else {
    val.clear();
    val2.clear();
    if (value.substr(0, 2) == ">=" || value.substr(0, 2) == "<=" ||
        value.substr(0, 2) == "<>") {
      // Check if we're filtering for '<> NULL'. In this case we need a special
      // comparison operator.
      if (value.substr(0, 2) == "<>" && value.substr(2) == "NULL") {
        // We are filtering for '<>NULL'. Override the comparison operator to
        // search for NULL values in this column. Also treat search value (NULL)
        // as number, in order to avoid putting quotes around it.
        op = "IS NOT";
        numeric = true;
        val = "NULL";
      } else if (value.substr(0, 2) == "<>" && value.substr(2) == "''") {
        // We are filtering for "<>''", i.e. for everything which is not an
        // empty string
        op = "<>";
        numeric = true;
        val = "''";
      } else {
        stof(value.substr(2), numericp);  // set numeric
        op = value.substr(0, 2);
        val = value.substr(2);
      }
    } else if (value.substr(0, 1) == ">" || value.substr(0, 1) == "<") {
      stof(value.substr(1), numericp);
      op = value.substr(0, 1);
      val = value.substr(1);
    } else if (value.substr(0, 1) == "=") {
      val = value.substr(1);

      // Check if value to compare with is 'NULL'
      if (val != "NULL") {
        // It's not, so just compare normally to the value, whatever it is.
        op = "=";
      } else {
        // It is NULL. Also treat search value (NULL) as number,
        // in order to avoid putting quotes around it.
        op = "IS";
        numeric = true;
      }
      if (val != "NULL") {
        switch (column_type) {
          case sql::PG_TYPES::INT4:
          case sql::PG_TYPES::INT8:
            val = std::to_string(
                stof(val, numericp));  // may be risky:
                                       // https://stackoverflow.com/a/35345427
            break;
          case sql::PG_TYPES::PSJSON:
            numeric = false;
            break;
          default:
            break;
        }
      }
    } else if (value.substr(0, 1) == "/" &&
               value.substr(value.size() - 1, 1) == "/" && value.length() > 2) {
      val = value.substr(1, value.length() - 2);
      op = "REGEXP";
      numeric = false;
    } else if (value.substr(0, 1) == "{" &&
               value.substr(value.size() - 1, 1) == "}") {
      if (value.length() > 2) {
        val = "ANY('" + value + "')";
        op = "=";
        numeric = true;
      } else {
        val = "";
      }
    } else {
      switch (column_type) {
        case sql::PG_TYPES::INT4:
        case sql::PG_TYPES::INT8:
          val = value;
          op = "=";
          numeric = true;
          break;
        case sql::PG_TYPES::ENUM: {
          if (!value.empty()) {
            val = "'" + value + "'";
          }
          op = "=";
          break;
        }
        case sql::PG_TYPES::TEXT: {
          // Keep the default LIKE operator

          // Set the escape character if one has been specified in the settings
          // dialog
          std::string escape_character = "\\";
          if (escape_character == "'") escape_character = "''";
          if (escape_character.length()) escape = std::string("ESCAPE '\\'");

          // Add % wildcards at the start and at the beginning of the filter
          // query, but only if there weren't set any wildcards manually. The
          // idea is to assume that a user who's just typing characters expects
          // the wildcards to be added but a user who adds them herself knows
          // what she's doing and doesn't want us to mess up her query.
          if (value.find('%') == std::string::npos) {
            val = value;
            val = "%" + val;
            val = val + "%";
          }

          break;
        }
        default:
          val = value;
      }
    }
  }
  //    if(val.empty())
  //        val = value;

  if (val.empty() || val == "%" || val == "%%") return std::string();

  // Quote and escape value, but only if it's not numeric and not the empty
  // string sequence
  if (!numeric && !numericp && val != "''" &&
      (column_type == sql::PG_TYPES::TEXT ||
       column_type == sql::PG_TYPES::PSJSON)) {
    boost::replace_all(val, "'", "''");
    val = "'" + val + "'";
  }

  std::string whereClause(op + " " + val);
  if (!val2.empty()) whereClause += " AND " + val2;
  whereClause += " " + escape;
  return whereClause;
}
}  // namespace sql
