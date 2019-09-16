#pragma once
#include "../base_query.h"
namespace openproj {
namespace Queries {
namespace TimeEntries {
class TimeEntryQuery : public openproj::Queries::BaseQuery {
   void model() {
//    TimeEntry
  }

   void default_scope() {
//    TimeEntry.visible(User.current)
  }
};
}
}
}

