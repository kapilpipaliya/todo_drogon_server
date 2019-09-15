#pragma once
namespace openproj {
namespace Projects {
  class DeleteProjectService {
    // attr_accessor :user, :project
    // include Concerns::Contracted

//     DeleteProjectService(user:, project:) {
//      this->user = user
//      this->project = project
//      this->contract_class = ::Projects::DeleteContract
//    }

    //
    // Deletes the given user if allowed.
    //
    // @return True if the project deletion has been initiated, false otherwise.
//     void call(delayed: true) {
//      result, errors = validate_and_yield(project, user) { delete_or_schedule_deletion(delayed) }
//      ServiceResult.new(success: result, errors: errors)
//    }

    private:

//     void delete_or_schedule_deletion(delayed) {
//      if ( delayed) {
//        // Archive the project
//        project.archive
//        Delayed::Job.enqueue DeleteProjectJob.new(user_id: user.id, project_id: project.id),
//                             priority: ::ApplicationJob.priority_number(:low)
//        true
//      else
//        delete_project!
//      }
//    }

     bool delete_project() {
//      OpenProject::Notifications.send('project_deletion_imminent', project: this->project_to_destroy)

//      if ( project.destroy) {
//        ProjectMailer.delete_project_completed(project, user: user).deliver_now
//        true
//      else
//        ProjectMailer.delete_project_failed(project, user: user).deliver_now
//        false
//      }
    }
  };
}
}
