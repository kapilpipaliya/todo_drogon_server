#pragma once
//
namespace openproj {
namespace QueryN::Highlighting {
  // extend ActiveSupport::Concern

  namespace PrependValidHighlightingSubset {
//     void valid_subset!() {
//      super
//      valid_highlighting_subset!
//    }
  }

//  included {
//    prepend PrependValidHighlightingSubset

//    QUERY_HIGHLIGHTING_MODES = %i[inline none status type priority].freeze

//    serialize :highlighted_attributes, Array

//    // validates_inclusion_of :highlighting_mode,
//                           in: QUERY_HIGHLIGHTING_MODES,
//                           allow_nil: true,
//                           allow_blank: true

//    validate :attributes_highlightable?

//     void valid_highlighting_subset!() {
//      this->highlighted_attributes = valid_highlighting_subset
//    }

//     void available_highlighting_columns() {
//      this->available_highlighting_columns ||= available_columns.select(&:highlightable?)
//    }

//     void highlighted_columns() {
//      columns = available_highlighting_columns.group_by(&:name)

//      valid_highlighting_subset
//        .map { |name| columns[name.to_sym] }
//        .flatten
//        .uniq
//    }

//     void highlighted_attributes() {
//      return [] unless EnterpriseToken.allows_to?(:conditional_highlighting)

//      val = super

//      if ( val.present?) {
//        val.map(&:to_sym)
//      else
//        highlighted_attributes_from_setting
//      }
//    }

//     void highlighting_mode() {
//      return :none unless EnterpriseToken.allows_to?(:conditional_highlighting)

//      val = super

//      if ( val.present?) {
//        val.to_sym
//      else
//        highlighting_mode_from_setting
//      }
//    }

//     void default_highlighting_mode() {
//      QUERY_HIGHLIGHTING_MODES.first
//    }

//     void attributes_highlightable?() {
//      // Test that chosen attributes intersect with allowed columns
//      difference = highlighted_attributes - available_highlighting_columns.map { |col| col.name.to_sym }
//      if ( difference.any?) {
//        errors.add(:highlighted_attributes,
//                   I18n.t(:error_attribute_not_highlightable,
//                          attributes: difference.map(&:to_s).map(&:capitalize).join(', ')))
//      }
//    }

//    private:

//     void valid_highlighting_subset() {
//      available_names = available_highlighting_columns.map(&:name)

//      highlighted_attributes & available_names
//    }

//     void highlighted_attributes_from_setting() {
//      settings = Setting.work_package_list_default_highlighted_attributes || []
//      values = settings.map(&:to_sym)
//      available_names = available_highlighting_columns.map(&:name)
//      values & available_names
//    }

//     void highlighting_mode_from_setting() {
//      value = Setting.work_package_list_default_highlighting_mode.to_sym

//      if ( QUERY_HIGHLIGHTING_MODES.include? value) {
//        value
//      else
//        default_highlighting_mode
//      }
//    }
  }
}
