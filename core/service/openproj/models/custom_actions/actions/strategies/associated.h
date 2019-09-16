#pragma once
namespace openproj {
namespace CustomActions::Actions::Strategies::Associated {
  // include CustomActions::ValidateAllowedValue
  // include CustomActions::ValuesToInteger

   void allowed_values() {
//    this->allowed_values ||= begin
//      options = associated
//                .map { |value, label| { value: value, label: label } }

//      if ( required?) {
//        options
//      else
//        options.unshift(value: nil, label: I18n.t('placeholders.default'))
//      }
//    }
  }

//   void apply(work_package) {
//    work_package.send(:"#{key}_id=", values.first)
//  }

   void type() {
//    :associated_property
  }

   void associated() {
//    raise 'Not implemented error'
  }

//   void validate(errors) {
//    validate_allowed_value(errors, :actions)
//    super
//  }
};
}
