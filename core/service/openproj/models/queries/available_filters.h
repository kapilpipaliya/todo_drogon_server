#pragma once
//require_dependency 'queries/filters'

namespace openproj{
namespace Queries::AvailableFilters {
//   void included(base) {
//    base.extend(ClassMethods)
//  }

  namespace ClassMethods {
     void registered_filters() {
//      Queries::Register.filters[self]
    }

//     void find_registered_filter(key) {
//      registered_filters.detect { |f|
//        f.key === key.to_sym
//      }
//    }
//  }

   void available_filters() {
//    uninitialized = registered_filters - already_initialized_filters

//    uninitialized.each { |filter|
//      initialize_filter(filter)
//    }

//    initialized_filters.select(&:available?)
  }

//   void filter_for(key, no_memoization = false) {
//    filter = get_initialized_filter(key, no_memoization)

//    if ( filter.nil?) { raise ::Queries::Filters::MissingError ;}

//    filter
//  rescue ::Queries::Filters::InvalidError => e
//    Rails.logger.error "Failed to register filter for #{key}: #{e} \n" \
//                       "Falling back to non-existing filter."
//    non_existing_filter(key)
//  rescue ::Queries::Filters::MissingError => e
//    Rails.logger.error "Failed to find filter for #{key}: #{e} \n" \
//                       "Falling back to non-existing filter."
//    non_existing_filter(key)
//  }

//  private:

//   void non_existing_filter(key) {
//    Queries::NotExistingFilter.create!(name: key)
//  }

//   void get_initialized_filter(key, no_memoization) {
//    filter = find_registered_filter(key)

//    return unless filter

//    if ( no_memoization) {
//      filter.create!(name: key)
//    else
//      initialize_filter(filter)

//      find_initialized_filter(key)
//    }
//  }

//   void initialize_filter(filter) {
//    if ( already_initialized_filters.include?(filter)) { return ;}
//    already_initialized_filters << filter

//    new_filters = filter.all_for(context)

//    initialized_filters.push(*Array(new_filters))
//  }

//   void find_registered_filter(key) {
//    this->class.find_registered_filter(key)
//  }

//   void find_initialized_filter(key) {
//    initialized_filters.detect { |f|
//      f.name == key.to_sym
//    }
//  }

   void already_initialized_filters() {
//    this->already_initialized_filters ||= []
  }

   void initialized_filters() {
//    this->initialized_filters ||= []
  }

//   void registered_filters() {
//    this->class.registered_filters
//  }
}
}
}
