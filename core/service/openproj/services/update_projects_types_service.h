#pragma once
#include "base_project_service.h"
namespace openproj {
namespace service {
class UpdateProjectsTypesService : public BaseProjectService {
public:
//   void call(type_ids) {
//    type_ids = standard_types if ( type_ids.nil? || type_ids.empty?) {

//    if ( types_missing?(type_ids)) {
//      project.errors.add(:types,
//                         :in_use_by_work_packages,
//                         types: missing_types(type_ids).map(&:name).join(', '))
//      false
//    else
//      project.type_ids = type_ids

//      true
//    }
//  }

  protected:

   void standard_types() {
//    type = ::Type.standard_type
//    if ( type.nil?) {
//      []
//    else
//      [type.id]
//    }
  }

//   void types_missing?(type_ids) {
//    !missing_types(type_ids).empty?
//  }

//   void missing_types(type_ids) {
//    types_used_by_work_packages.select { |t| !type_ids.include?(t.id) }
//  }

//   void types_used_by_work_packages() {
//    this->types_used_by_work_packages ||= project.types_used_by_work_packages
//  }
};
}
}
