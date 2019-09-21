#pragma once
#include "filters/base.h"
namespace openproj {
namespace models {
namespace Queries {
class NotExistingFilter : public openproj::models::Queries::Filters::Base {
//   void available?() {
//    false
//  }

   void type() {
//    :inexistent
  }

   void key() {
//    :not_existent
  }

   void human_name() {
//    name.to_s.blank? ? type : name.to_s
  }

//  validate :always_false

   void always_false() {
//    errors.add :base, I18n.t(:"activerecord.errors.messages.does_not_exist")
  }

  // deactivating superclass validation
   void validate_inclusion_of_operator() {}

   void to_hash() {
//    {
//      non_existent_filter: {
//        operator: operator,
//        values: values
//      }
//    }
  }

   void scope() {
    // TODO: remove switch once the WP query is a
    // subclass of Queries::Base
//    model = if ( context.respond_to?(:model)) {
//              context.model
//            else
//              WorkPackage
//            }

//    model.unscoped
  }

   void attributes_hash() {
//    nil
  }
};
}
}
}