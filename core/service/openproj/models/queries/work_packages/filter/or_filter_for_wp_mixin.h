#pragma once
namespace openproj {
namespace Queries::WorkPackages::Filter::OrFilterForWpMixin {
  // extend ActiveSupport::Concern

//  included {
//    validate :minimum_one_filter_valid
//  }

//   void filters() {
//    if ( this->filters) {
//      update_instances
//    else
//      this->filters = create_instances
//    }

//    this->filters.keep_if ((&:validate)) {
//  }

//   void joins() {
//    filters.map(&:joins).flatten.compact
//  }

//   void includes() {
//    filters.map(&:includes).flatten.uniq.reject(&:blank?)
//  }

//   void where() {
//    filters.map(&:where).join(' OR ')
//  }

//   virtual void filter_configurations() = 0;

//   void create_instances() {
//    filter_configurations.map { |conf|
//      conf.filter_class.create!(name: conf.filter_name,
//                                context: context,
//                                operator: conf.operator,
//                                values: values)
//    }
//  }

//   void update_instances() {
//    configurations = filter_configurations

//    this->filters.each_with_index { |filter, index|
//      filter.operator = configurations[index].operator
//      filter.values = values
//    }
//  }

//   void ar_object_filter?() {
//    false
//  }

//   void minimum_one_filter_valid() {
//    if ( filters.empty?) {
//      errors.add(:values, :invalid)
//    }
//  }
}
}
