#pragma once
#include "../../../queries/work_packages/columns/work_package_column.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Columns {
class RelationColumn : public openproj::models::Queries::WorkPackages::Columns::WorkPackageColumn {
  // attr_accessor :type

   void granted_by_enterprise_token() {
//    EnterpriseToken.allows_to?(:work_package_query_relation_columns)
  }

//  private_class_method :granted_by_enterprise_token
};
}
}
}
}
}