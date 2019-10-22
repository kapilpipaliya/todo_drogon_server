#pragma once
#include "../../../queries/relations/filters/relation_filter.h"
namespace openproj {
namespace models {
namespace Queries {
  namespace Relations {
    namespace Filters {
      //
      // Filters relations by work package ID in either `from` or `to` position of a relation.
      // For instance:
      //   Given relations [{ from_id: 3, to_id: 7 }, { from_id: 8, to_id: 3}]
      //   filtering by involved=3 would yield both these relations.
      class InvolvedFilter : public openproj::models::Queries::Relations::Filters::RelationFilter {
        // include ::Queries::Relations::Filters::VisibilityChecking

         void type() {
//          :integer
        }

         void key() {
//          :involved
        }

        private:

//         void visibility_checked_sql(operator_string, values, visible_sql) {
//          concatenation = if ( operator == "=") {
//                            "OR"
//                          else
//                            "AND"
//                          }

//          sql = <<-SQL.strip_heredoc
//            (from_id #{operator_string} (?) AND to_id IN (#{visible_sql}))
//             #{concatenation} (to_id #{operator_string} (?) AND from_id IN (#{visible_sql}))
//          SQL

//          [sql, values, values]
//        }
      };
    }
  }
}
    }
}