#pragma once
#include "../../services/base_services/create.h"
namespace openproj {
namespace Roles{
class CreateService : public BaseServices::Create {
  // include Roles::NotifyMixin

  private:

//   void create(params) {
//    copy_workflow_id = params.delete(:copy_workflow_from)

//    super_call = super

//    if ( super_call.success?) {
//      copy_workflows(copy_workflow_id, super_call.result)

//      notify_changed_roles(:added, super_call.result)
//    }

//    super_call
//  }

//   void new_instance(params) {
//    if ( params.delete(:global_role)) {
//      GlobalRole.new
//    else
//      super
//    }
//  }

//   void copy_workflows(copy_workflow_id, role) {
//    if ( copy_workflow_id.present? && (copy_from = Role.find_by(id: copy_workflow_id))) {
//      role.workflows.copy_from_role(copy_from)
//    }
//  }
};
}
}
