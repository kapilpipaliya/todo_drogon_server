#pragma once
#include "../../../queries/time_entries/filters/time_entry_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace TimeEntries {
namespace Filters {
class WorkPackageFilter : public openproj::models::Queries::TimeEntries::Filters::TimeEntryFilter {
   void allowed_values() {
//    this->allowed_values ||= begin
//      // We don"t care for the first value as we do not display the values visibly
//      ::WorkPackage.visible.pluck(:id).map { |id| [id, id.to_s] }
//    }
  }

   void type() {
//    :list_optional
  }

   void key() {
//    :work_package_id
  }
};
}
}
}
}
}