#include "application_controller.h"
class CategoriesController : public ApplicationController {
  // menu_item :settings
  // model_object Category
  // before_action :find_model_object, except: [:new, :create]
  // before_action :find_project_from_association, except: [:new, :create]
  // before_action :find_project, only: [:new, :create]
  // before_action :authorize

   void new_() {
//    this->category = this->project.categories.build
  }

   void create() {
//    this->category = this->project.categories.build
//    this->category.attributes = permitted_params.category

//    if ( this->category.save) {
//      respond_to { |format|
//        format.html {
//          flash[:notice] = l(:notice_successful_create)
//          redirect_to controller: '/project_settings', action: 'show', tab: 'categories', id: this->project
//        }
//        format.js {
//          render locals: { project: this->project, category: this->category }
//        }
//      }
//    else
//      respond_to { |format|
//        format.html {
//          render action: :new
//        }
//        format.js {
//          render(:update) { |page| page.alert(this->category.errors.full_messages.join('\n')) }
//        }
//      }
//    }
  }

   void update() {
//    this->category.attributes = permitted_params.category
//    if ( this->category.save) {
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to controller: '/project_settings', action: 'show', tab: 'categories', id: this->project
//    else
//      render action: 'edit'
//    }
  }

   void destroy() {
//    this->issue_count = this->category.work_packages.size
//    if ( this->issue_count == 0) {
//      // No issue assigned to this category
//      this->category.destroy
//      redirect_to controller: '/project_settings', action: 'show', id: this->project, tab: 'categories'
//      return
//    } else if ( params[:todo]) {
//      if ( params[:todo] == 'reassign') { reassign_to = this->project.categories.find_by(id: params[:reassign_to_id]) ;}
//      this->category.destroy(reassign_to)
//      redirect_to controller: '/project_settings', action: 'show', id: this->project, tab: 'categories'
//      return
//    }
//    this->categories = this->project.categories - [this->category]
  }

  private:

  // Wrap ApplicationController's find_model_object method to set
  // this->category instead of just this->category
   void find_model_object() {
//    super
//    this->category = this->object
  }

   void find_project() {
//    this->project = Project.find(params[:project_id])
//  rescue ActiveRecord::RecordNotFound
//    render_404
//  }
};
