namespace Projects {
  class DeleteProjectJob : public ApplicationJob {
    // include OpenProject::LocaleHelper

    attr_reader :user_id,
                :project_id

     DeleteProjectJob(user_id:, project_id:) {
      this->user_id = user_id
      this->project_id = project_id
    }

     void perform() {
      service = ::Projects::DeleteProjectService.new(user: user, project: project)
      call = service.call(delayed: false)

      if ( call.failure?) {
        logger.error("Failed to delete project #{project} in background job: #{call.errors.join("\n")}")
      }
    rescue StandardError => e
      logger.error('Encountered an error when trying to delete project '\
                   "'#{project_id}' : #{e.message} #{e.backtrace.join("\n")}")
    }

    private:

     void user() {
      this->user ||= User.find user_id
    }

     void project() {
      this->project ||= Project.find project_id
    }

     void logger() {
      Delayed::Worker.logger
    }
  }
}
