#pragma once
#include "activerecord.h"
namespace openproj {
class WorkPackageCustomField : public CustomField {
//  has_and_belongs_to_many :projects,
//                          join_table: "#{table_name_prefix}custom_fields_projects#{table_name_suffix}",
//                          foreign_key: 'custom_field_id'
//  has_and_belongs_to_many :types,
//                          join_table: "#{table_name_prefix}custom_fields_types#{table_name_suffix}",
//                          foreign_key: 'custom_field_id'
  // has_many :work_packages,
//           through: :work_package_custom_values

  // scope :visible_by_user, ->(user) {
//    if ( user.allowed_to_globally?(:edit_projects)) {
//      all
//    else
//      where(projects: { id: Project.visible(user) })
//        .where(types: { id: Type.enabled_in(Project.visible(user)) })
//        .or(where(is_for_all: true).references(:projects, :types))
//        .includes(:projects, :types)
//    }
//  }

   void summable() {
//    ids = Setting.work_package_list_summable_columns.map { |column_name|
//      if ( match = /cf_(\d+)/.match(column_name)) {
//        match[1]
//      }
//    }.compact

//    where(id: ids)
  }

   void type_name() {
//    :label_work_package_plural
  }
};
}
