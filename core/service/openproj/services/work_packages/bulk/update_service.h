#pragma once
namespace openproj {
namespace WorkPackages {
  namespace Bulk {
    class UpdateService {
      // include ::Shared::ServiceContext
      // include ::HookHelper

      // attr_accessor :user, :work_packages, :permitted_params

//       UpdateService(user:, work_packages:) {
//        this->user = user
//        this->work_packages = work_packages
//      }

//       void call(params:) {
//        this->permitted_params = PermittedParams.new(params, user)
//        in_context(true) {
//          bulk_update(params)
//        }
//      }

      private:

//       void bulk_update(params) {
//        saved = []
//        errors = {}

//        work_packages.each { |work_package|
//          work_package.add_journal(user, params[:notes])

//          // filter parameters by whitelist and add defaults
//          attributes = parse_params_for_bulk_work_package_attributes params, work_package.project

//          call_hook(:controller_work_packages_bulk_edit_before_save, params: params, work_package: work_package)

//          service_call = WorkPackages::UpdateService
//                         .new(user: user, model: work_package)
//                         .call(attributes.merge(send_notifications: params[:send_notification] == '1').symbolize_keys)

//          if ( service_call.success?) {
//            saved << work_package.id
//          else
//            errors[work_package.id] = service_call.errors.full_messages
//          }
//        }

//        ServiceResult.new success: errors.empty?, result: saved, errors: errors
//      }

//       void parse_params_for_bulk_work_package_attributes(params, project) {
//        return {} unless params.has_key? :work_package

//        safe_params = permitted_params.update_work_package project: project
//        attributes = safe_params.reject { |_k, v| v.blank? }
//        attributes.keys.each { |k|
//          if ( attributes[k] == 'none') { attributes[k] = '' ;}
//        }
//        if ( attributes[:custom_field_values]) { attributes[:custom_field_values].reject! { |_k, v| v.blank? } ;}
//        if ( not attributes.has_key?(:custom_field_values) or attributes[:custom_field_values].empty?) { attributes.delete :custom_field_values ;}
//        attributes.to_h
//      }
    };
  }
}
}
