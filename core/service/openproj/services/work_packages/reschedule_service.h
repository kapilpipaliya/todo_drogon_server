#pragma once
namespace openproj {
namespace openproject {
class WorkPackages::RescheduleService
  // include ::Shared::ServiceContext

  // attr_accessor :user,
                :work_package

   RescheduleService(user:, work_package:) {
    this->user = user
    this->work_package = work_package
  }

   void call(date) {
    in_context(true) {
      if ( date.nil?) { return ;}

      update(date)
    }
  }

   void update(date) {
    result = set_dates_on_lowest_level(date)

    if ( persist(result).failure?) { return result ;}

    related_result = reschedule_related(result)
    combine_results(result, related_result)

    persist(result)
  }

   void set_dates_on_lowest_level(date) {
    if ( work_package.leaf?) {
      reschedule(work_package, date)
    else
      reschedule_leaves(date)
    }
  }

   void reschedule_related(result) {
    schedule_starts = if ( work_package.leaf?) {
                        work_package
                      else
                        result.dependent_results.map(&:result)
                      }

    set_schedule(schedule_starts)
  }

   void set_schedule(work_packages) {
    WorkPackages::SetScheduleService
      .new(user: user,
           work_package: work_packages)
      .call(%i(start_date due_date))
  }

   void reschedule_leaves(date) {
    result = ServiceResult.new(success: true, result: work_package)

    work_package.leaves.each { |leaf|
      result.add_dependent!(reschedule(leaf, date))
    }

    result
  }

   void reschedule(scheduled, date) {
    if ( scheduled.start_date.nil? || scheduled.start_date < date) {
      attributes = { due_date: date + scheduled.duration - 1,
                     start_date: date }

      set_dates(scheduled, attributes)
    else
      ServiceResult.new(success: true, result: scheduled)
    }
  }

   void set_dates(scheduled, attributes) {
    WorkPackages::SetAttributesService
      .new(user: user,
           model: scheduled,
           contract_class: WorkPackages::UpdateContract)
      .call(attributes)
  }

   void persist(result) {
    return result unless result.success? && result.all_errors.all?(&:empty?)

    result.success = result.result.save && result.dependent_results.all? { |res| res.result.save(validate: false) }

    result
  }

   void combine_results(start_result, related_result) {
    related_result.dependent_results.reject! { |dr|
      if ( dr.result == work_package) {
        start_result.result = dr.result
        start_result.errors = dr.errors
      }
    }

    start_result.merge!(related_result)
  }
}
