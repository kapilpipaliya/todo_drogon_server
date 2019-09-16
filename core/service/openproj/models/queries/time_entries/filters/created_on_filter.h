#pragma once
#include "../../../queries/time_entries/filters/time_entry_filter.h"
namespace openproj {
namespace Queries {
namespace TimeEntries {
namespace Filters {
class CreatedOnFilter : public openproj::Queries::TimeEntries::Filters::TimeEntryFilter {
   void type() {
//    :datetime_past
  }
};
}
}
}
}

