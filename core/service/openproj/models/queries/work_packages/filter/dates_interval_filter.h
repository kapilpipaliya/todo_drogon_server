#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class DatesIntervalFilter : public openproj::Queries::WorkPackages::Filter::WorkPackageFilter {
  // include Queries::Operators::DateRangeClauses

   void type() {
//    :date
  }

   void where() {
//    lower_boundary, upper_boundary = values.map { |v| v.blank? ? nil : Date.parse(v) }

//    <<-SQL
//      (work_packages.start_date < '#{quoted_date_from_utc(lower_boundary)}' AND
//       work_packages.due_date > '#{quoted_date_from_utc(lower_boundary)}') OR
//      (#{date_range_clause('work_packages', 'start_date', lower_boundary, upper_boundary)}) OR
//      (#{date_range_clause('work_packages', 'due_date', lower_boundary, upper_boundary)})
//    SQL
  }

   void type_strategy() {
//    this->type_strategy ||= Queries::Filters::Strategies::DateInterval.new(self)
  }

   void connection() {
//    ActiveRecord::Base::connection
  }
};
}
}
}
}

