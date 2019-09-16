#pragma once
#include "../../../queries/projects/filters/project_filter.h"
namespace openproj {
namespace Queries {
namespace Projects {
namespace Filters {
class ParentFilter : public openproj::Queries::Projects::Filters::ProjectFilter {
   void type() {
//    :list_optional
  }

   void key() {
//    :parent_id
  }

   void allowed_values() {
//    this->allowed_values ||= begin
//      ::Project.visible.pluck(:id).map { |id| [id, id.to_s] }
    }
  };
}
}
}
}
