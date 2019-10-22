namespace openproj {
namespace helper {
namespace RolesHelper {
//   void setable_permissions(role) {
//    // Use the base contract for now as we are only interested in the setable permissions
//    // which do not differentiate.
//    contract = Roles::BaseContract.new(role, current_user)

//    contract.assignable_permissions
//  }

//   void grouped_setable_permissions(role) {
//    group_permissions_by_module(setable_permissions(role))
//  }

//  private:

//   void group_permissions_by_module(perms) {
//    perms_by_module = perms.group_by { |p| p.project_module.to_s }
//    ::OpenProject::AccessControl
//      .sorted_modules
//      .select { |module_name| perms_by_module[module_name].present? }
//      .map { |module_name|
//      [module_name, perms_by_module[module_name]]
//    }
//  }
}
}
}
