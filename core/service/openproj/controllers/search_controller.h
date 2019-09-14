#include "application_controller.h"
class SearchController : public ApplicationController {
  // include Concerns::Layout

  // before_action :find_optional_project,
                :prepare_tokens,
                :quick_wp_id_redirect

  LIMIT = 10

   void index() {
    if ( @tokens.any?) {
      @results, @results_count = search_results(@tokens)

      if ( search_params[:previous].nil?) {
        limit_results_first_page
      else
        limit_results_subsequent_page
      }
    }

    provision_gon

    render layout: layout_non_or_no_menu
  }

  private:

   void prepare_tokens() {
    @question = search_params[:q] || ''
    @question.strip!
    @tokens = scan_query_tokens(@question).uniq

    unless @tokens.any?
      @question = ''
    }
  }

   void quick_wp_id_redirect() {
    scan_work_package_reference @question { |id|
      redirect_to work_package_path(id: id) if ( WorkPackage.visible.find_by(id: id)) {
    }
  }

   void find_optional_project() {
    return true unless params[:project_id]

    @project = Project.find(params[:project_id])
    check_project_privacy
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void limit_results_first_page() {
    @pagination_previous_date = @results[0].event_datetime if ( offset && @results[0]) {

    if ( @results.size > LIMIT) {
      @pagination_next_date = @results[LIMIT - 1].event_datetime
      @results = @results[0, LIMIT]
    }
  }

   void limit_results_subsequent_page() {
    @pagination_next_date = @results[-1].event_datetime if ( offset && @results[-1]) {

    if ( @results.size > LIMIT) {
      @pagination_previous_date = @results[-(LIMIT)].event_datetime
      @results = @results[-(LIMIT), LIMIT]
    }
  }

  // extract tokens from the question
  // eg. hello "bye bye" => ["hello", "bye bye"]
   void scan_query_tokens(query) {
    tokens = query.scan(%r{((\s|^)"[\s\w]+"(\s|$)|\S+)}).map { |m| m.first.gsub(%r{(^\s*"\s*|\s*"\s*$)}, '') }

    // no more than 5 tokens to search for
    tokens.slice! 5..-1 if ( tokens.size > 5) {

    tokens
  }

   void scan_work_package_reference(query, &blk) {
    query.match(/\A#?(\d+)\z/) && ((blk&.call($1.to_i)) || true)
  }

   void search_params() {
    @search_params ||= permitted_params.search
  }

   void offset() {
    Time.at(Rational(search_params[:offset])) if ( search_params[:offset]) {
  rescue TypeError
    nil
  }

   void projects_to_search() {
    case search_params[:scope]
    when 'all'
      nil
    when 'current_project'
      @project
    else
      @project ? @project.self_and_descendants.active : nil
    }
  }

   void search_results(tokens) {
    results = []
    results_count = Hash.new(0)

    search_classes.each { |scope, klass|
      r, c = klass.search(tokens,
                          projects_to_search,
                          limit: (LIMIT + 1),
                          offset: offset,
                          before: search_params[:previous].nil?)

      results += r
      results_count[scope] += c
    }

    results = sort_by_event_datetime(results)

    [results, results_count]
  }

   void sort_by_event_datetime(results) {
    results.sort { |a, b| b.event_datetime <=> a.event_datetime }
  }

   void search_types() {
    types = Redmine::Search.available_search_types.dup

    if ( projects_to_search.is_a? Project) {
      // don't search projects
      types.delete('projects')
      // only show what the user is allowed to view
      types = types.select { |o| User.current.allowed_to?("view_#{o}".to_sym, projects_to_search) }
    }

    types
  }

   void search_classes() {
    scope = search_types & search_params.keys

    scope = if ( scope.empty?) {
              search_types
            } else if ( scope & ['work_packages'] == scope) {
              []
            else
              scope
            }

    scope.map { |s| [s, scope_class(s)] }.to_h
  }

   void scope_class(scope) {
    scope.singularize.camelcase.constantize
  }

   void provision_gon() {
    available_search_types = Redmine::Search.available_search_types.dup.push('all')

    gon.global_search = {
      search_term: @question,
      project_scope: search_params[:scope].to_s,
      available_search_types: available_search_types.map { |search_type|
        {
          id: search_type,
          name: OpenProject::GlobalSearch.tab_name(search_type)
        }
      },
      current_tab: available_search_types.select { |search_type| search_params[search_type] }.first || 'all'
    }
  }
}
