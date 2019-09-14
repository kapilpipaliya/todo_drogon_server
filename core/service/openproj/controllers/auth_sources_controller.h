#pragma once
#include "application_controller.h"
namespace openproject {
class AuthSourcesController : public ApplicationController {
public:
  // include PaginationHelper
  // layout 'admin'

  // before_action :require_admin
  // before_action :block_if_password_login_disabled

   void index() {
//    this->auth_sources = AuthSource.page(page_param)
//                    .per_page(per_page_param)

//    render 'auth_sources/index'
  }

   void new_() {
//    this->auth_source = auth_source_class.new
//    render 'auth_sources/new'
  }

   void create() {
//    this->auth_source = auth_source_class.new permitted_params.auth_source
//    if ( this->auth_source.save) {
//      flash[:notice] = l(:notice_successful_create)
//      redirect_to action: 'index'
//    else
//      render 'auth_sources/new'
//    }
  }

   void edit() {
//    this->auth_source = AuthSource.find(params[:id])
//    render 'auth_sources/edit'
  }

   void update() {
//    this->auth_source = AuthSource.find(params[:id])
//    updated = permitted_params.auth_source
//    if ( updated[:account_password].blank?) { updated.delete :account_password ;}

//    if ( this->auth_source.update_attributes updated) {
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to action: 'index'
//    else
//      render 'auth_sources/edit'
//    }
  }

   void test_connection() {
//    this->auth_method = AuthSource.find(params[:id])
//    begin
//      this->auth_method.test_connection
//      flash[:notice] = l(:notice_successful_connection)
//    rescue => text
//      flash[:error] = l(:error_unable_to_connect, text.message)
//    }
//    redirect_to action: 'index'
  }

   void destroy() {
//    this->auth_source = AuthSource.find(params[:id])
//    if ( this->auth_source.users.empty?) {
//      this->auth_source.destroy

//      flash[:notice] = t(:notice_successful_delete)
//    else
//      flash[:warning] = t(:notice_wont_delete_auth_source)
//    }
//    redirect_to action: 'index'
  }

  protected:

   void auth_source_class() {
//    AuthSource
  }

   void default_breadcrumb() {
//    if ( action_name == 'index') {
//      t(:label_auth_source_plural)
//    else
//      ActionController::Base.helpers.link_to(t(:label_auth_source_plural), ldap_auth_sources_path)
//    }
  }

   bool show_local_breadcrumb() {
    return true;
  }

   void block_if_password_login_disabled() {
//    if ( OpenProject::Configuration.disable_password_login?) { render_404 ;}
  }
};
}
