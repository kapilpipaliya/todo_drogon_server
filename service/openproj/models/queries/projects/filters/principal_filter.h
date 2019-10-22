#pragma once
#include "../../../queries/projects/filters/project_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Projects {
namespace Filters {
class PrincipalFilter : public openproj::models::Queries::Projects::Filters::ProjectFilter {
   void type() {
//    :list_optional
  }

   void allowed_values() {
//    this->allowed_values ||= begin
//      ::Principal.pluck(:id).map { |id| [id, id.to_s] }
//    }
  }

   void scope() {
//    super.includes(:memberships).references(:members)
  }

   void where() {
//    operator_strategy.sql_for_field(values, "members", "user_id")
  }
};
}
}
}
}
}