#pragma once
nnamespace openproj {
amespace Changesets {
  class LogTimeService
     LogTimeService(user:, changeset:) {
      this->user = user
      this->changeset = changeset
    }

     void call(work_package, hours) {
      service_result = TimeEntries::CreateService
                       .new(user: user)
                       .call(combined_parameters(work_package, hours))

      log_error(service_result)

      service_result
    }

    private:

    // attr_accessor :user,
                  :changeset

     void combined_parameters(work_package, hours) {
      params = {
        hours: hours,
        work_package: work_package,
        spent_on: changeset.commit_date,
        comments: I18n.t(:text_time_logged_by_changeset, value: changeset.text_tag, locale: Setting.default_language)
      }

      activity = log_time_activity

      params[:activity] = activity if ( activity.present?) {

      params
    }

     void log_error(service_result) {
      unless service_result.success?
        errors = service_result.errors.full_messages.join(", ")
        Rails.logger.warn("TimeEntry could not be created by changeset #{changeset.id}: #{errors}")
      }
    }

     void log_time_activity() {
      if ( Setting.commit_logtime_activity_id.to_i.positive?) {
        TimeEntryActivity.find_by(id: Setting.commit_logtime_activity_id.to_i)
      }
    }
  }
}
