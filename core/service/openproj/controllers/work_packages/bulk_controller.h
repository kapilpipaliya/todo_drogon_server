#pragma once
#include "../application_controller.h"
namespace openproj {
namespace controller {
namespace WorkPackages {

class BulkController : public ApplicationController {
  // before_action :find_work_packages
  // before_action :authorize

  // include ProjectsHelper
  // include CustomFieldsHelper
  // include RelationsHelper
  // include QueriesHelper
  // include IssuesHelper

   void edit() {
//    setup_edit
  }

   void update() {
//    this->call = ::WorkPackages::Bulk::UpdateService
//      .new(user: current_user, work_packages: this->work_packages)
//      .call(params: params)

//    if ( this->call.success?) {
//      flash[:notice] = t(:notice_successful_update)
//      redirect_back_or_default(controller: '/work_packages', action: :index, project_id: this->project)
//    else
//      this->bulk_errors = this->call.errors
//      setup_edit
//      render action: :edit
//    }
  }

   void destroy() {
//    unless WorkPackage.cleanup_associated_before_destructing_if_required(this->work_packages, current_user, params[:to_do])

//      respond_to { |format|
//        format.html {
//          render locals: { work_packages: this->work_packages,
//                           associated: WorkPackage.associated_classes_to_address_before_destruction_of(this->work_packages) }
//        }
//        format.json {
//          render json: { error_message: 'Clean up of associated objects required' }, status: 420
//        }
//      }

//    else

//      destroy_work_packages(this->work_packages)

//      respond_to { |format|
//        format.html {
//          redirect_back_or_default(project_work_packages_path(this->work_packages.first.project))
//        }
//        format.json {
//          head :ok
//        }
//      }
//    }
  }

  private:

   void setup_edit() {
//    this->available_statuses = this->projects.map { |p| Workflow.available_statuses(p) }.inject { |memo, w| memo & w }
//    this->custom_fields = this->projects.map(&:all_work_package_custom_fields).inject { |memo, c| memo & c }
//    this->assignables = this->projects.map(&:possible_assignees).inject { |memo, a| memo & a }
//    this->responsibles = this->projects.map(&:possible_responsibles).inject { |memo, a| memo & a }
//    this->types = this->projects.map(&:types).inject { |memo, t| memo & t }
  }

//   void destroy_work_packages(work_packages) {
//    work_packages.each { |work_package|
//      begin
//        WorkPackages::DeleteService
//          .new(user: current_user,
//               model: work_package.reload)
//          .call
//      rescue ::ActiveRecord::RecordNotFound
//        // raised by #reload if ( work package no longer exists) {
//        // nothing to {, work package was already deleted (eg. by a parent)
//      }
//    }
//  }

   void user() {
//    current_user
  }

   void default_breadcrumb() {
//    l(:label_work_package_plural)
  }
};
}
}
}
