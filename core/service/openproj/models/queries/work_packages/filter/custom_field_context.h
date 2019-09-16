#pragma once
namespace openproj {
namespace Queries::WorkPackages::Filter::CustomFieldContext {
//  class << self {
//     void custom_field_class() {
//      ::WorkPackageCustomField
//    }

//     void model() {
//      ::WorkPackage
//    }

//     void custom_fields(context) {
//      if ( context&.project) {
//        context.project.all_work_package_custom_fields
//      else
//        custom_field_class
//          .filter
//          .for_all
//          .where
//          .not(field_format: %w(user version))
//      }
//    }

//     void where_subselect_joins(custom_field) {
//      cf_types_db_table = 'custom_fields_types'
//      cf_projects_db_table = 'custom_fields_projects'
//      cv_db_table = CustomValue.table_name
//      work_package_db_table = WorkPackage.table_name

//      joins = "LEFT OUTER JOIN #{cv_db_table}
//                 ON #{cv_db_table}.customized_type='WorkPackage'
//                 AND #{cv_db_table}.customized_id=#{work_package_db_table}.id
//                 AND #{cv_db_table}.custom_field_id=#{custom_field.id}
//               JOIN #{cf_types_db_table}
//                 ON #{cf_types_db_table}.type_id =  #{work_package_db_table}.type_id
//                 AND #{cf_types_db_table}.custom_field_id = #{custom_field.id}"

//      unless custom_field.is_for_all
//        joins += " JOIN #{cf_projects_db_table}
//                     ON #{cf_projects_db_table}.project_id = #{work_package_db_table}.project_id
//                     AND #{cf_projects_db_table}.custom_field_id = #{custom_field.id}"
//      }

//      joins
//    }
//  }
}
}
