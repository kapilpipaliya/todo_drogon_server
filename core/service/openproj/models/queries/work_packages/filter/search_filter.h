#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class SearchFilter  : openproj::models::Queries::WorkPackages::Filter::WorkPackageFilter {
  // include Queries::WorkPackages::Filter::OrFilterForWpMixin
  // include Queries::WorkPackages::Filter::FilterOnTsvMixin

//  CONTAINS_OPERATOR = '~'.freeze

//  CE_FILTERS = [
//    Queries::WorkPackages::Filter::FilterConfiguration.new(
//      Queries::WorkPackages::Filter::SubjectFilter,
//      :subject,
//      CONTAINS_OPERATOR
//    ),
//    Queries::WorkPackages::Filter::FilterConfiguration.new(
//      Queries::WorkPackages::Filter::DescriptionFilter,
//      :subject,
//      CONTAINS_OPERATOR
//    ),
//    Queries::WorkPackages::Filter::FilterConfiguration.new(
//      Queries::WorkPackages::Filter::CommentFilter,
//      :subject,
//      CONTAINS_OPERATOR
//    )
//  ].freeze

//  EE_TSV_FILTERS = [
//    Queries::WorkPackages::Filter::FilterConfiguration.new(
//      Queries::WorkPackages::Filter::AttachmentContentFilter,
//      :subject,
//      CONTAINS_OPERATOR
//    ),
//    Queries::WorkPackages::Filter::FilterConfiguration.new(
//      Queries::WorkPackages::Filter::AttachmentFileNameFilter,
//      :subject,
//      CONTAINS_OPERATOR
//    )
//  ].freeze

   void key() {
//    :search
  }

   void name() {
//    :search
  }

   void type() {
//    :search
  }

   void human_name() {
//    I18n.t('label_search')
  }

   void custom_field_configurations() {
//    custom_fields =
//      if ( context&.project) {
//        context.project.all_work_package_custom_fields.select { |custom_field|
//          %w(text string).include?(custom_field.field_format) &&
//            custom_field.is_filter == true &&
//            custom_field.searchable == true
//        }
//      else
//        ::WorkPackageCustomField
//          .filter
//          .for_all
//          .where(field_format: %w(text string),
//                 is_filter: true,
//                 searchable: true)
//      }

//    custom_fields.map { |custom_field|
//      Queries::WorkPackages::Filter::FilterConfiguration.new(
//        Queries::WorkPackages::Filter::CustomFieldFilter,
//        "cf_#{custom_field.id}",
//        CONTAINS_OPERATOR
//      )
//    }
  }

   void filter_configurations() {
//    list = CE_FILTERS

//    list += custom_field_configurations
//    if ( attachment_filters_allowed?) { list += EE_TSV_FILTERS ;}
//    list
  }

  private:

//   void attachment_filters_allowed?() {
//    EnterpriseToken.allows_to?(:attachment_filters) && OpenProject::Database.allows_tsv?
//  }
};
}
}
}
}

}