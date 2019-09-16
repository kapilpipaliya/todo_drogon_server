#pragma once
#include "../../../queries/relations/filters/relation_filter.h"
namespace openproj {
namespace Queries {
  namespace Relations {
    namespace Filters {
      class IdFilter : public openproj::Queries::Relations::Filters::RelationFilter {
         void type() {
//          :integer
        }

         void key() {
//          :id
        }
      };
    }
  }
}
    }
