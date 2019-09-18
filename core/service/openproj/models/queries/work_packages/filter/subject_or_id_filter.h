#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class SubjectOrIdFilter  : openproj::models::Queries::WorkPackages::Filter::WorkPackageFilter {
  // include Queries::WorkPackages::Filter::OrFilterForWpMixin

//  CONTAINS_OPERATOR = '~'.freeze
//  EQUALS_OPERATOR = '='.freeze

//  FILTERS = [
//    Queries::WorkPackages::Filter::FilterConfiguration.new(
//      Queries::WorkPackages::Filter::SubjectFilter,
//      :subject,
//      CONTAINS_OPERATOR
//    ),
//    Queries::WorkPackages::Filter::FilterConfiguration.new(
//      Queries::WorkPackages::Filter::IdFilter,
//      :id,
//      EQUALS_OPERATOR
//    )
//  ].freeze

   void key() {
//    :subject_or_id
  }

   void name() {
//    :subject_or_id
  }

   void type() {
//    :search
  }

   void human_name() {
//    I18n.t('label_subject_or_id')
  }

   void filter_configurations() {
//    FILTERS
  }
};
}
}
}
}
}