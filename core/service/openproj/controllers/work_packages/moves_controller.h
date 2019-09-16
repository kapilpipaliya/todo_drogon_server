#pragma once
#include "../application_controller.h"
namespace openproj {
namespace controller {
namespace WorkPackages {

class MovesController : public ApplicationController {
//  default_search_scope :work_packages
  // before_action :find_work_packages, :check_project_uniqueness
  // before_action :authorize

   void new_() {
//    prepare_for_work_package_move
  }

   void create() {
//    prepare_for_work_package_move

//    new_type = params[:new_type_id].blank? ? nil : this->target_project.types.find_by(id: params[:new_type_id])

//    unsaved_work_package_ids = []
//    moved_work_packages = []

//    this->work_packages.each { |work_package|
//      work_package.reload

//      call_hook(:controller_work_packages_move_before_save,
//                params: params,
//                work_package: work_package,
//                target_project: this->target_project,
//                copy: !!this->copy)

//      service_call = WorkPackages::MoveService
//                     .new(work_package, current_user)
//                     .call(this->target_project,
//                           new_type,
//                           copy: this->copy,
//                           attributes: permitted_create_params,
//                           journal_note: this->notes)

//      if ( service_call.success?) {
//        moved_work_packages << service_call.result
//      } else if ( this->copy) {
//        unsaved_work_package_ids.concat dependent_error_ids(work_package.id, service_call)
//      else
//        unsaved_work_package_ids << work_package.id
//      }
//    }

//    set_flash_from_bulk_work_package_save(this->work_packages, unsaved_work_package_ids)

//    if ( params[:follow]) {
//      if ( this->work_packages.size == 1 && moved_work_packages.size == 1) {
//        redirect_to work_package_path(moved_work_packages.first)
//      else
//        redirect_to project_work_packages_path(this->target_project || this->project)
//      }
//    else
//      redirect_back_or_default(project_work_packages_path(this->project))
//    }
  }

//   void set_flash_from_bulk_work_package_save(work_packages, unsaved_work_package_ids) {
//    if ( unsaved_work_package_ids.empty? and not work_packages.empty?) {
//      flash[:notice] = this->copy ? l(:notice_successful_create) : l(:notice_successful_update)
//    else
//      flash[:error] = l(:notice_failed_to_save_work_packages,
//                        count: unsaved_work_package_ids.size,
//                        total: work_packages.size,
//                        ids: '#' + unsaved_work_package_ids.join(', #'))
//    }
//  }

  //
  // When copying, add work package ids that are failing
//   void dependent_error_ids(parent_id, service_call) {
//    ids = service_call
//      .results_with_errors(include_self: false)
//      .map { |result| result.context[:copied_from]&.id }
//      .compact

//    if ( ids.present?) {
//      joined = ids.map {|id| "##{id}" }.join(" ")
//      ["#{parent_id} (+ children errors: #{joined})"]
//    else
//      [parent_id]
//    }
//  }

   void default_breadcrumb() {
//    l(:label_move_work_package)
  }

  private:

  // Check if ( project is unique before bulk operations) {
   void check_project_uniqueness() {
//    unless this->project
//      // TODO: let users bulk move/copy work packages from different projects
//      render_error message: :'work_packages.move.unsupported_for_multiple_projects', status: 400
//      return false
//    }
  }

   void prepare_for_work_package_move() {
//    this->work_packages = this->work_packages.includes(:ancestors)
//    this->copy = params.has_key? :copy
//    this->allowed_projects = WorkPackage.allowed_target_projects_on_move(current_user)
//    if ( params[:new_project_id]) { this->target_project = this->allowed_projects.detect { |p| p.id.to_s == params[:new_project_id].to_s } ;}
//    this->target_project ||= this->project
//    this->types = this->target_project.types
//    this->available_statuses = Workflow.available_statuses(this->project)
//    this->notes = params[:notes]
//    this->notes ||= ''

//    // When copying, avoid copying elements when any of their ancestors
//    // are in the set to be copied
//    if ( this->copy) {
//      this->work_packages = remove_hierarchy_duplicates
//    }
  }

  // Check if a parent work package is also selected for copying
   void remove_hierarchy_duplicates() {
//    // Get all ancestors of the work_packages to copy
//    selected_ids = this->work_packages.pluck(:id)

//    this->work_packages.reject { |wp|
//      wp.ancestors.where(id: selected_ids).exists?
//    }
  }

   void permitted_create_params() {
//    params
//      .permit(:assigned_to_id,
//              :responsible_id,
//              :start_date,
//              :due_date,
//              :status_id,
//              :priority_id)
//      .to_h
//      .reject { |_, v| v.blank? }
  }
};
}
}
}
