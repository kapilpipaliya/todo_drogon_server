#pragma once
#include "../../../queries/versions/filters/version_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Versions {
namespace Filters {
class SharingFilter : public openproj::models::Queries::Versions::Filters::VersionFilter {
   void allowed_values() {
//    VersionN::VERSION_SHARINGS.map { |name|
//      [I18n.t(:"label_version_sharing_#{name}"), name]
//    }
  }

   void type() {
//    :list
  }

   void key() {
//    :sharing
  }
};
}
}
}
}
}