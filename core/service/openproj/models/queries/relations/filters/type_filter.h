#pragma once
#include "../../../queries/relations/filters/relation_filter.h"
namespace openproj {
namespace models {
namespace Queries {
  namespace Relations {
    namespace Filters {
      class TypeFilter : public openproj::models::Queries::Relations::Filters::RelationFilter {
         void allowed_values() {
//          ::Relation::TYPES.map { |_, value|
//            [I18n.t(value[:name]), value[:sym]]
//          }
        }

         void type() {
//          :list
        }

         void key() {
//          :type
        }

         void where() {
//          Array(values).map { |value|
//            column = Relation.relation_column(value)

//            operator_strategy.sql_for_field(['1'],
//                                            this->class.model.table_name,
//                                            column)
//          }.join(' OR ')
        }
      };
    }
  }
}
}
}