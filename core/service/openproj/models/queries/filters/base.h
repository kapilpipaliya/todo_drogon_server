#ifndef dkfjdskfjdskf
#define dkfjdskfjdskf
#pragma once
//#include "queries/operators"

namespace openproj {
namespace Queries {
namespace Filters {
class Base {
  // include ActiveModel::Validations

//   void i18n_scope() {
//    :activerecord
//  }

  // class_attribute :model,
//                  :filter_params

//  this->filter_params = %i(operator values)

  // attr_accessor :context, *filter_params
//  attr_reader :name
//  alias :field :name

//   Base(name, options = {}) {
//    this->name = name.to_sym
//    this->context = options[:context]

//    this->class.filter_params.each { |param_field|
//      send("#{param_field}=", options[param_field])
//    }
//  }

  //
  // Treat the constructor as private, as the filter MAY need to check
  // the options before accepting them as a filter.
  //
  // Use +#create+ instead.
//  private_class_method :new

  //
  // Creates a filter instance with the given name if the options are acceptable.
  // Raises an +InvalidFilterError+ if the given filter cannot be created with this option.
//   void create!(name: key, **options) {
//    new(name, options)
//  }

//   void [](name) {
//    send(name)
//  }

//   void filter_instance_options() {
//    values = filter_params.map { |key| [key, send(key)] }
//    initial_options.merge(Hash[values])
//  }

//   virtual void human_name() = 0;

//   virtual void type() = 0;

//   void allowed_values() {
//    nil
//  }

//   void valid_values!() {
//    type_strategy.valid_values!
//  }

//   void available?() {
//    true
//  }

//   void available_operators() {
//    type_strategy.supported_operator_classes
//  }

//   void default_operator() {
//    type_strategy.default_operator_class
//  }

//   void scope() {
//    scope = model.where(where)
//    if ( joins) { scope = scope.joins(joins) ;}
//    scope
//  }

//   void key() {
//    to_s.demodulize.underscore.gsub(/_filter$/, '').to_sym
//  }

//   void connection() {
//    model.connection
//  }

//   void all_for(context = nil) {
//    create!(name: key, context: context)
//  }

//   void where() {
//    operator_strategy.sql_for_field(values, this->class.model.table_name, this->class.key)
//  }

//   void joins() {
//    nil
//  }

//   void includes() {
//    nil
//  }

//  validate :validate_inclusion_of_operator,
//           :validate_presence_of_values,
//           :validate_values

//   void values() {
//    this->values || []
//  }

  // Values may contain an internal representation for some filters
//  alias :values_replaced :values

//   void values=(values) {
//    this->values = Array(values).map(&:to_s)
//  }

  // Does the filter filter on other models, e.g. User, Status
//   void ar_object_filter?() {
//    false
//  }

  // List of objects the value represents
  // is empty if the filter does not filter on other AR objects
//   void value_objects() {
//    []
//  }

//   void operator_class() {
//    operator_strategy
//  }

//   void error_messages() {
//    messages = errors
//               .full_messages
//               .join(" #{I18n.t('support.array.sentence_connector')} ")

//    errors.full_message(human_name, messages)
//  }

  protected:

//   void type_strategy() {
//    this->type_strategy ||= Queries::Filters::STRATEGIES[type].new(self)
//  }

//   void operator_strategy() {
//    type_strategy.operator
//  }

//   void validate_inclusion_of_operator() {
//    unless operator && available_operators.map(&:to_sym).include?(operator.to_sym)
//      errors.add(:operator, :inclusion)
//    }
//  }

   void validate_presence_of_values() {
//    if ( operator_strategy && operator_strategy.requires_value? && (values.nil? || values.reject(&:blank?).empty?)) {
//      errors.add(:values, I18n.t('activerecord.errors.messages.blank'))
//    }
  }

   void validate_values() {
//    type_strategy.validate
  }
};
}
}
}

#endif
