#pragma once
#include "../base_query.h"
namespace openproj {
namespace models {
namespace Queries {
namespace TimeEntries {
class TimeEntryQuery : public openproj::models::Queries::BaseQuery {
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

}