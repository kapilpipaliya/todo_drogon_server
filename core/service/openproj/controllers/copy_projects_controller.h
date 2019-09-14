#pragma once
#include "application_controller.h"
class CopyProjectsController : public ApplicationController {
  // before_action :find_project
  // before_action :authorize

   void copy() {
//    this->copy_project = project_copy

//    if ( this->copy_project.valid?) {
//      enqueue_copy_job

//      flash[:notice] = I18n.t('copy_project.started',
//                              source_project_name: this->project.name,
//                              target_project_name: permitted_params.project[:name])
//      redirect_to origin
//    else
//      render action: copy_action
//    }
  }

   void copy_project() {
//    this->copy_project = Project.copy_attributes(this->project)
//    if ( this->copy_project) {
//      if ( Setting.sequential_project_identifiers?) { this->copy_project.identifier = Project.next_identifier ;}

//      render action: copy_action
//    else
//      redirect_to :back
//    }
//  rescue ActiveRecord::RecordNotFound
//    redirect_to :back
  }

  private:

   void copy_action() {
//    from = (%w(admin settings).include?(params[:coming_from]) ? params[:coming_from] : 'settings')

//    "copy_from_#{from}"
  }

   void project_copy() {
//    copy_project = Project.new
//    copy_project.attributes = permitted_params.project

//    // cannot use set_allowed_parent! as it requires a persisted project
//    if ( copy_project.allowed_parent?(params['project']['parent_id'])) {
//      copy_project.parent_id = params['project']['parent_id']
//    }

//    copy_project
  }

   void origin() {
//    params[:coming_from] == 'admin' ? projects_path : settings_project_path(this->project.id)
  }

   void enqueue_copy_job() {
//    copy_project_job = CopyProjectJob.new(user_id: User.current.id,
//                                          source_project_id: this->project.id,
//                                          target_project_params: target_project_params,
//                                          associations_to_copy: params[:only],
//                                          send_mails: params[:notifications] == '1')

//    Delayed::Job.enqueue copy_project_job, priority: ::ApplicationJob.priority_number(:low)
  }

   void target_project_params() {
//    this->copy_project
//      .attributes
//      .compact
//      .with_indifferent_access
//      .merge(custom_field_values: this->copy_project.custom_value_attributes)
  }
};
