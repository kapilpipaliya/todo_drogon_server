#pragma once
#include "application_controller.h"
class WorkPackagesController : public ApplicationController {
public:
  // include QueriesHelper
  // include PaginationHelper
  // include OpenProject::ClientPreferenceExtractor
  // include Concerns::Layout

  // accept_key_auth :index, :show

  // before_action :authorize_on_work_package, only: :show
  // before_action :find_optional_project,
//                :protect_from_unauthorized_export, only: :index

  // before_action :load_and_validate_query, only: :index, unless: ->() { request.format.html? }
  // before_action :load_work_packages, only: :index, if: ->() { request.format.atom? }

  // before_action :set_gon_settings

   void show() {
//    respond_to { |format|
//      format.html {
//        render :show, locals: { work_package: work_package, menu_name: project_or_wp_query_menu }, layout: 'angular'
//      }

//      format.any(*WorkPackage::Exporter.single_formats) {
//        export_single(request.format.symbol)
//      }

//      format.atom {
//        atom_journals
//      }

//      format.all {
//        head :not_acceptable
//      }
//    }
  }

   void index() {
//    respond_to { |format|
//      format.html {
//        render :index, locals: { query: this->query, project: this->project, menu_name: project_or_wp_query_menu },
//                       // layout: 'angular'
//      }

//      format.any(*WorkPackage::Exporter.list_formats) {
//        export_list(request.format.symbol)
//      }

//      format.atom {
//        atom_list
//      }
//    }
  }

  protected:

   void set_gon_settings() {
//    gon.settings = client_preferences
//    gon.settings[:enabled_modules] = project ? project.enabled_modules.collect(&:name) : []
  }

   void export_list(std::string mime_type) {
//    exporter = WorkPackage::Exporter.for_list(mime_type)
//    exporter.list(this->query, params) { |export|
//      render_export_response export, fallback_path: index_redirect_path
//    }
  }

   void export_single(std::string mime_type) {
//    exporter = WorkPackage::Exporter.for_single(mime_type)
//    exporter.single(work_package, params) { |export|
//      render_export_response export, fallback_path: work_package_path(work_package)
//    }
  }

   void atom_journals() {
//    render template: 'journals/index',
//           // layout: false,
//           content_type: 'application/atom+xml',
//           locals: { title: "#{Setting.app_title} - #{work_package}",
//                     journals: journals }
  }

   void atom_list() {
//    render_feed(this->work_packages,
//                title: "#{this->project || Setting.app_title}: #{l(:label_work_package_plural)}")
  }

  private:

//   void render_export_response(export, fallback_path:) {
//    if ( export.error?) {
//      flash[:error] = export.message
//      redirect_back(fallback_location: fallback_path)
//    } else if ( export.content.is_a? File) {
//      // browsers should not try to guess the content-type
//      response.headers['X-Content-Type-Options'] = 'nosniff'

//      // TODO avoid reading the file in memory here again
//      // but currently the tempfile gets removed in between
//      send_data(export.content.read,
//                type: export.mime_type,
//                disposition: 'attachment',
//                filename: export.title)
//    else
//      send_data(export.content,
//                type: export.mime_type,
//                filename: export.title)
//    }
//  }

   void authorize_on_work_package() {
//    deny_access(not_found: true) unless work_package
  }

   void protect_from_unauthorized_export() {
//    if ( supported_export_formats.include?(params[:format]) &&) {
//      !User.current.allowed_to?(:export_work_packages, this->project, global: this->project.nil?)

//      deny_access
//      false
//    }
  }

   void supported_export_formats() {
//    %w[atom rss] + WorkPackage::Exporter.list_formats.map(&:to_s)
  }

   void load_and_validate_query() {
//    this->query ||= retrieve_query

//    unless this->query.valid?
//      // Ensure outputting a html response
//      request.format = 'html'
//      return render_400(message: this->query.errors.full_messages.join(". "))
    }

//  rescue ActiveRecord::RecordNotFound
//    render_404
//  }

   void per_page_param() {
//    case params[:format]
//    when 'atom'
//      Setting.feeds_limit.to_i
//    else
//      super
//    }
  }

   void project() {
//    this->project ||= work_package ? work_package.project : nil
  }

   void work_package() {
//    this->work_package ||= WorkPackage.visible(current_user).find_by(id: params[:id])
  }

   void journals() {
//    this->journals ||= begin
//      order =
//        if ( current_user.wants_comments_in_reverse_order?) {
//          Journal.arel_table['created_at'].desc
//        else
//          Journal.arel_table['created_at'].asc
//        }

//      work_package
//        .journals
//        .changing
//        .includes(:user)
//        .order(order).to_a
//    }
  }

   void index_redirect_path() {
//    if ( this->project) {
//      project_work_packages_path(this->project)
//    else
//      work_packages_path
//    }
  }

   void load_work_packages() {
//    this->results = this->query.results
//    this->work_packages = if ( this->query.valid?) {
//                       this->results
//                         .sorted_work_packages
//                         .page(page_param)
//                         .per_page(per_page_param)
//                     else
//                       []
//                     }
  }

   void login_back_url_params() {
//    params.permit(:query_id, :state, :query_props)
  }
};
