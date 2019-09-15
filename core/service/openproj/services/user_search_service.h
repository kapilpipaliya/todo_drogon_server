#pragma once
namespace openproject {
class UserSearchService{
public:
  // attr_accessor :params
//  attr_reader :users_only, :project

//  SEARCH_SCOPES = [
//    'project_id',
//    'ids',
//    'group_id',
//    'status',
//    'name'
//  ]

//   UserSearchService(params, users_only: false) {
//    this->params = params

//    this->users_only = users_only
//    if ( params[:project_id]) { this->project = Project.find(params[:project_id]) ;}
//  }

   void scope() {
//    if ( users_only) {
//      project.nil? ? User : project.users
//    else
//      project.nil? ? Principal : project.principals
//    }
  }

   void search() {
//    params[:ids].present? ? ids_search(scope) : query_search(scope)
  }

//   void ids_search(scope) {
//    ids = params[:ids].split(',')

//    scope.not_builtin.where(id: ids)
//  }

//   void query_search(scope) {
//    if ( params[:group_id].present?) { scope = scope.in_group(params[:group_id].to_i) ;}
//    c = ARCondition.new

//    if ( params[:status] == 'blocked') {
//      this->status = :blocked
//      scope = scope.blocked
//    } else if ( params[:status] == 'all') {
//      this->status = :all
//      scope = scope.not_builtin
//    else
//      this->status = params[:status] ? params[:status].to_i : User::STATUSES[:active]
//      if ( users_only && this->status == User::STATUSES[:active]) { scope = scope.not_blocked ;}
//      c << ['status = ?', this->status]
//    }

//    unless params[:name].blank?
//      name = "%#{params[:name].strip.downcase}%"
//      c << ['LOWER(login) LIKE ? OR LOWER(firstname) LIKE ? OR LOWER(lastname) LIKE ? OR LOWER(mail) LIKE ?', name, name, name, name]
//    }

//    scope.where(c.conditions)
    // currently, the sort/paging-helpers are highly dependent on being included in a controller
    // and having access to things like the session or the params: this makes it harder
    // to test outside a controller and especially hard to re-use this functionality
    // .page(page_param)
    // .per_page(per_page_param)
    // .order(sort_clause)
//  }
};
}
