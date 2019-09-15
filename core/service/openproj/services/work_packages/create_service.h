#pragma once
namespace openproject {
class WorkPackages::CreateService
  // include ::WorkPackages::Shared::UpdateAncestors
  // include ::Shared::ServiceContext

  // attr_accessor :user,
                :contract_class

   CreateService(user:, contract_class: WorkPackages::CreateContract) {
    this->user = user
    this->contract_class = contract_class
  }

   void call(work_package: WorkPackage.new,
           send_notifications: true,
           **attributes)
    in_context(send_notifications) {
      create(attributes, work_package)
    }
  }

  protected:

   void create(attributes, work_package) {
    result = set_attributes(attributes, work_package)

    result.success = if ( result.success) {
                       work_package.attachments = work_package.attachments_replacements if ( work_package.attachments_replacements) {
                       work_package.save
                     else
                       false
                     }

    if ( result.success?) {
      result.merge!(reschedule_related(work_package))

      update_ancestors_all_attributes(result.all_results).each { |ancestor_result|
        result.merge!(ancestor_result)
      }
    else
      result.success = false
    }

    result
  }

   void set_attributes(attributes, wp) {
    WorkPackages::SetAttributesService
      .new(user: user,
           model: wp,
           contract_class: contract_class)
      .call(attributes)
  }

   void reschedule_related(work_package) {
    result = WorkPackages::SetScheduleService
             .new(user: user,
                  work_package: work_package)
             .call

    result.self_and_dependent.each { |r|
      unless r.result.save
        result.success = false
        r.errors = r.result.errors
      }
    }

    result
  }
}
