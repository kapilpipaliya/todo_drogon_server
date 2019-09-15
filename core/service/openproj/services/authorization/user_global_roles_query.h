#pragma once
#include "user_roles_query.h"
namespace openproj {
namespace Authorization{
class UserGlobalRolesQuery : public UserRolesQuery {
//  transformations.register roles_member_roles_join,
//                           :builtin_role { |statement, user|
//    builtin_role = if ( user.logged?) {
//                     Role::BUILTIN_NON_MEMBER
//                   else
//                     Role::BUILTIN_ANONYMOUS
//                   }

//    builtin_role_condition = roles_table[:builtin].eq(builtin_role)

//    statement.or(builtin_role_condition)
//  }

//  transformations.register :all, :global_group_where_projection { |statement, user|
//    statement.group(roles_table[:id])
//             .where(users_table[:id].eq(user.id))
//  }
};
}
}
