#pragma once
namespace openproj {
namespace Authorization {
class EnterpriseService {
  // attr_accessor :token

//  GUARDED_ACTIONS = %i(define_custom_style
//                       multiselect_custom_fields
//                       edit_attribute_groups
//                       work_package_query_relation_columns
//                       attribute_help_texts
//                       two_factor_authentication
//                       ldap_groups
//                       custom_fields_in_projects_list
//                       custom_actions
//                       conditional_highlighting
//                       readonly_work_packages
//                       attachment_filters
//                       board_view).freeze

//   EnterpriseService(token) {
//    this->token = token
//  }

//  // Return a true ServiceResult if ( the token contains this particular action.) {
//   void call(action) {
//    allowed =
//      if ( token.nil? || token.token_object.nil? || token.expired?) {
//        false
//      else
//        process(action)
//      }

//    result(allowed)
//  }

//  private:

//   void process(action) {
//    // Every non-expired token
//    GUARDED_ACTIONS.include?(action)
//  }

//   void result(bool) {
//    ServiceResult.new(success: bool, result: bool)
//  }
};
}
}
