#pragma once
#include "query_filter.h"
namespace openproj {
namespace Queries {
namespace Queries {
namespace Filters {
class HiddenFilter : public openproj::Queries::Queries::Filters::QueryFilter {
   void key() {
//    :hidden
  }

   void allowed_values() {
//    [
//      [I18n.t(:general_text_yes), OpenProject::Database::DB_VALUE_TRUE],
//      [I18n.t(:general_text_no), OpenProject::Database::DB_VALUE_FALSE]
//    ]
  }

   void type() {
//    :list
  }

   void type_strategy() {
//    this->type_strategy ||= ::Queries::Filters::Strategies::BooleanList.new self
  }
};
}
}
}
}

