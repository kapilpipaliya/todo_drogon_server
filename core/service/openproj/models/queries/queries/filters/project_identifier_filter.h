#pragma once
#include "../../queries/filters/query_filter.h"
namespace openproj {
namespace Queries {
namespace Queries {
namespace Filters {
class ProjectIdentifierFilter : public openproj::Queries::Queries::Filters::QueryFilter {
   void type() {
//    :list
  }

   void key() {
//    :project_identifier
  }

   void joins() {
//    :project
  }

   void where() {
//    operator_strategy.sql_for_field(values, 'projects', 'identifier')
  }

   void allowed_values() {
//    Project.visible.pluck(:name, :identifier)
  }
};
}
}
}
}
