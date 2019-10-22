#pragma once
#include "../../../queries/time_entries/filters/time_entry_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace TimeEntries {
namespace Filters {
class CreatedOnFilter : public openproj::models::Queries::TimeEntries::Filters::TimeEntryFilter {
   void type() {
//    :datetime_past
  }
};
}
}
}
}

}