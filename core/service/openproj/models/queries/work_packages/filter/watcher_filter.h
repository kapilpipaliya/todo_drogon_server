#pragma once
#include "../../../queries/work_packages/filter/principal_base_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class WatcherFilter  : openproj::Queries::WorkPackages::Filter::PrincipalBaseFilter {
//   void allowed_values() {
//    this->allowed_values ||= begin
//      // populate the watcher list with the same user list as other user filters
//      // if ( the user has the :view_work_package_watchers permission) {
//      // in at least one project
//      // TODO: this could be differentiated
//      // more, e.g. all users could watch issues in public projects,
//      // but won't necessarily be shown here
//      values = me_allowed_value
//      if ( User.current.allowed_to?(:view_work_package_watchers, project, global: project.nil?)) {
//        values += principal_loader.user_values
//      }
//      values
//    }
//  }

   void type() {
//    :list
  }

   void key() {
//    :watcher_id
  }

   void where() {
//    if ( User.current.admin?) {
//      // Admins can always see all watchers
//      where_any_watcher
//    else
//      where_allowed_watchers
//    }
  }

  private:

   void where_any_watcher() {
//    db_table = Watcher.table_name
//    db_field = 'user_id'

//    <<-SQL
//      #{WorkPackage.table_name}.id #{operator == '=' ? 'IN' : 'NOT IN'}
//        (SELECT #{db_table}.watchable_id
//         FROM #{db_table}
//         WHERE #{db_table}.watchable_type='WorkPackage'
//           AND #{::Queries::Operators::Equals.sql_for_field values_replaced, db_table, db_field})
//    SQL
  }

   void where_allowed_watchers() {
//    sql_parts = []

//    if ( User.current.logged? && user_id = values_replaced.delete(User.current.id.to_s)) {
//      // a user can always see his own watched issues
//      sql_parts << where_self_watcher(user_id)
//    }
//    // filter watchers only in projects the user has the permission to view watchers in
//    sql_parts << where_watcher_in_view_watchers_allowed

//    sql_parts.join(' OR ')
  }

//   void where_self_watcher(user_id) {
//    <<-SQL
//      #{WorkPackage.table_name}.id #{operator == '=' ? 'IN' : 'NOT IN'}
//        (SELECT #{db_table}.watchable_id
//         FROM #{db_table}
//         WHERE #{db_table}.watchable_type='WorkPackage'
//         AND #{::Queries::Operators::Equals.sql_for_field [user_id], db_table, db_field})
//    SQL
//  }

   void where_watcher_in_view_watchers_allowed() {
//    <<-SQL
//      #{WorkPackage.table_name}.id #{operator == '=' ? 'IN' : 'NOT IN'}
//        (SELECT #{db_table}.watchable_id
//         FROM #{db_table}
//         WHERE #{db_table}.watchable_type='WorkPackage'
//           AND #{::Queries::Operators::Equals.sql_for_field values_replaced, db_table, db_field})
//           AND #{Project.table_name}.id IN
//             (#{view_watcher_allowed_scoped.to_sql})
//    SQL
  }

   void db_table() {
//    Watcher.table_name
  }

   void db_field() {
//    'user_id'
  }

   void view_watcher_allowed_scoped() {
//    Project
//      .allowed_to(User.current, :view_work_package_watchers)
//      .select("#{Project.table_name}.id")
  }
};
}
}
}
}
