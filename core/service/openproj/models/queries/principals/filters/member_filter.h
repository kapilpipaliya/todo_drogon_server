#pragma once
#include "../../../queries/principals/filters/principal_filter.h"
namespace openproj {
namespace Queries {
namespace Principals {
namespace Filters {
class MemberFilter : public openproj::Queries::Principals::Filters::PrincipalFilter {
   void allowed_values() {
//    Project.active.all.map { |project|
//      [project.name, project.id]
//    }
  }

   void type() {
//    :list_optional
  }

   void key() {
//    :member
  }

   void scope() {
//    default_scope = Principal.includes(:members)

//    case operator
//    when '='
//      default_scope.where(members: { project_id: values })
//    when '!'
//      default_scope.where.not(members: { project_id: values })
//    when '*'
//      default_scope.where.not(members: { project_id: nil })
//    when '!*'
//      default_scope.where.not(id: Member.select(:user_id).uniq)
//    }
  }
};
}
}
}
}
