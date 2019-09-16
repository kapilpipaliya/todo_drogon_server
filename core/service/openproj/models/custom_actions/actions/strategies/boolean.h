#pragma once
namespace openproj {
namespace CustomActions::Actions::Strategies::Boolean {
  // include CustomActions::ValidateAllowedValue

   void allowed_values() {
//    [
//      { label: I18n.t(:general_text_yes), value: OpenProject::Database::DB_VALUE_TRUE },
//      { label: I18n.t(:general_text_no), value: OpenProject::Database::DB_VALUE_FALSE }
//    ]
  }

   void type() {
//    :boolean
  }

//   void validate(errors) {
//    validate_allowed_value(errors, :actions)
//    super
//  }
}
}
