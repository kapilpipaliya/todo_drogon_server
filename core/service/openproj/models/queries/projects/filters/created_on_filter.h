#pragma once
#include "../../../queries/projects/filters/project_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Projects {
namespace Filters {
class CreatedOnFilter : public openproj::models::Queries::Projects::Filters::ProjectFilter {
   void type() {
//    :datetime_past
  }

//   void available?() {
//    User.current.admin?
//  }
};
}
}
}
}

}