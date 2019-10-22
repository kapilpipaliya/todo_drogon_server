#pragma once
#include "../../../queries/relations/filters/relation_filter.h"
namespace openproj {
namespace models {
namespace Queries {
  namespace Relations {
    namespace Filters {
      class FromFilter : public openproj::models::Queries::Relations::Filters::RelationFilter {
        // include ::Queries::Relations::Filters::VisibilityChecking

         void type() {
//          :integer
        }

         void key() {
//          :from_id
        }

        private:

//         void visibility_checked_sql(operator, values, visible_sql) {
//          ["from_id #{operator} (?) AND to_id IN (#{visible_sql})", values]
//        }
      };
    }
  }
}
    }
}