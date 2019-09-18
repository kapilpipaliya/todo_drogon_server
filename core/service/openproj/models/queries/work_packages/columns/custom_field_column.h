#pragma once
#include "../../../queries/work_packages/columns/work_package_column.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Columns {
class CustomFieldColumn : public openproj::models::Queries::WorkPackages::Columns::WorkPackageColumn {
//   CustomFieldColumn(custom_field) {
//    super

//    set_name! custom_field
//    set_sortable! custom_field
//    set_groupable! custom_field
//    set_summable! custom_field

//    this->cf = custom_field
//  }

//   void set_name!(custom_field) {
//    this->name = "cf_#{custom_field.id}".to_sym
//  }

//   void set_sortable!(custom_field) {
//    this->sortable = custom_field.order_statements || false
//  }

//   void set_groupable!(custom_field) {
//    if ( groupable_custom_field?(custom_field)) { this->groupable = custom_field.group_by_statements ;}
//    this->groupable ||= false
//  }

//   void set_summable!(custom_field) {
//    this->summable = %w(float int).include?(custom_field.field_format)
//  }

//   void groupable_custom_field?(custom_field) {
//    %w(list date bool int).include?(custom_field.field_format)
//  }

//   void caption() {
//    this->cf.name
//  }

//   void custom_field() {
//    this->cf
//  }

//   void value(work_package) {
//    work_package.formatted_custom_value_for(this->cf.id)
//  }

//   void sum_of(work_packages) {
//    if ( work_packages.respond_to?(:joins)) {
//      // we can't perform the aggregation on the SQL side. Try to filter useless rows to reduce work.
//      work_packages = work_packages
//                      .joins(:custom_values)
//                      .where(custom_values: { custom_field: this->cf })
//                      .where("#{CustomValue.table_name}.value IS NOT NULL")
//                      .where("#{CustomValue.table_name}.value != ''")
//    }

//    // TODO: eliminate calls of this method with an Array and drop the :compact call below
//    work_packages.map { |wp| value(wp) }.compact.reduce(:+)
//  }

//   void instances(context = nil) {
//    if ( context) {
//      context.all_work_package_custom_fields
//    else
//      WorkPackageCustomField.all
//    }
//      .reject { |cf| cf.field_format == 'text' }
//      .map { |cf| new(cf) }
//  }
};
}
}
}
}
}