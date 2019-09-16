#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class SearchController : public ApplicationController {
public:
  // include Concerns::Layout

  // before_action :find_optional_project,
//                :prepare_tokens,
//                :quick_wp_id_redirect

//  LIMIT = 10

   void index() {
//    if ( this->tokens.any?) {
//      this->results, this->results_count = search_results(this->tokens)

//      if ( search_params[:previous].nil?) {
//        limit_results_first_page
//      else
//        limit_results_subsequent_page
//      }
//    }

//    provision_gon

//    render layout: layout_non_or_no_menu
  }

  private:

   void prepare_tokens() {
//    this->question = search_params[:q] || ''
//    this->question.strip!
//    this->tokens = scan_query_tokens(this->question).uniq

//    unless this->tokens.any?
//      this->question = ''
//    }
  }

   void quick_wp_id_redirect() {
//    scan_work_package_reference this->question { |id|
//      if ( WorkPackage.visible.find_by(id: id)) { redirect_to work_package_path(id: id) ;}
//    }
  }

   void find_optional_project() {
//    return true unless params[:project_id]

//    this->project = Project.find(params[:project_id])
//    check_project_privacy
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void limit_results_first_page() {
//    this->pagination_previous_date = this->results[0].event_datetime if ( offset && this->results[0]) {

//    if ( this->results.size > LIMIT) {
//      this->pagination_next_date = this->results[LIMIT - 1].event_datetime
//      this->results = this->results[0, LIMIT]
//    }
  }

   void limit_results_subsequent_page() {
//    if ( offset && this->results[-1]) { this->pagination_next_date = this->results[-1].event_datetime ;}

//    if ( this->results.size > LIMIT) {
//      this->pagination_previous_date = this->results[-(LIMIT)].event_datetime
//      this->results = this->results[-(LIMIT), LIMIT]
//    }
  }

  // extract tokens from the question
  // eg. hello "bye bye" => ["hello", "bye bye"]
   void scan_query_tokens(std::string query) {
//    tokens = query.scan(%r{((\s|^)"[\s\w]+"(\s|$)|\S+)}).map { |m| m.first.gsub(%r{(^\s*"\s*|\s*"\s*$)}, '') }

//    // no more than 5 tokens to search for
//    if ( tokens.size > 5) { tokens.slice! 5..-1 ;}

//    tokens
  }

//   void scan_work_package_reference(query, &blk) {
//    query.match(/\A#?(\d+)\z/) && ((blk&.call($1.to_i)) || true)
//  }

   void search_params() {
//    this->search_params ||= permitted_params.search
  }

   void offset() {
//    if ( search_params[:offset]) { Time.at(Rational(search_params[:offset])) ;}
//  rescue TypeError
//    nil
  }

   void projects_to_search() {
//    case search_params[:scope]
//    when 'all'
//      nil
//    when 'current_project'
//      this->project
//    else
//      this->project ? this->project.self_and_descendants.active : nil
//    }
  }

//   void search_results(tokens) {
//    results = []
//    results_count = Hash.new(0)

//    search_classes.each { |scope, klass|
//      r, c = klass.search(tokens,
//                          projects_to_search,
//                          limit: (LIMIT + 1),
//                          offset: offset,
//                          before: search_params[:previous].nil?)

//      results += r
//      results_count[scope] += c
//    }

//    results = sort_by_event_datetime(results)

//    [results, results_count]
//  }

//   void sort_by_event_datetime(results) {
//    results.sort { |a, b| b.event_datetime <=> a.event_datetime }
//  }

   void search_types() {
//    types = Redmine::Search.available_search_types.dup

//    if ( projects_to_search.is_a? Project) {
//      // don't search projects
//      types.delete('projects')
//      // only show what the user is allowed to view
//      types = types.select { |o| User.current.allowed_to?("view_#{o}".to_sym, projects_to_search) }
//    }

//    types
  }

   void search_classes() {
//    scope = search_types & search_params.keys

//    scope = if ( scope.empty?) {
//              search_types
//            } else if ( scope & ['work_packages'] == scope) {
//              []
//            else
//              scope
//            }

//    scope.map { |s| [s, scope_class(s)] }.to_h
  }

//   void scope_class(scope) {
//    scope.singularize.camelcase.constantize
//  }

   void provision_gon() {
//    available_search_types = Redmine::Search.available_search_types.dup.push('all')

//    gon.global_search = {
//      search_term: this->question,
//      project_scope: search_params[:scope].to_s,
//      available_search_types: available_search_types.map { |search_type|
//        {
//          id: search_type,
//          name: OpenProject::GlobalSearch.tab_name(search_type)
//        }
//      },
//      current_tab: available_search_types.select { |search_type| search_params[search_type] }.first || 'all'
//    }
  }
};
}
}
