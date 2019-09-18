#pragma once
#include "./base.h"
namespace openproj {
namespace models {
namespace Queries::Filters::Shared {
  namespace CustomFields {
    class Bool : public Base {
       void allowed_values() {
//        [
//          [I18n.t(:general_text_yes), OpenProject::Database::DB_VALUE_TRUE],
//          [I18n.t(:general_text_no), OpenProject::Database::DB_VALUE_FALSE]
//        ]
      }

       void type() {
//        :list
      }

      protected:

       void type_strategy_class() {
//        ::Queries::Filters::Strategies::BooleanList
      }
    };
  }
}
}
}