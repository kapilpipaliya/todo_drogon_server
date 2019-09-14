#include "open_project/repository_authentication"

class SysController : public ActionController::Base {
  // before_action :check_enabled
  // before_action :require_basic_auth, only: [:repo_auth]
  // before_action :find_project, only: [:update_required_storage]
  // before_action :find_repository_with_storage, only: [:update_required_storage]

   void projects() {
    p = Project.active.has_module(:repository)
        .includes(:repository)
        .references(:repositories)
        .order(Arel.sql('identifier'))
    respond_to { |format|
      format.json {
        render json: p.to_json(include: :repository)
      }
      format.any(:html, :xml) {
        render xml: p.to_xml(include: :repository), content_type: Mime[:xml]
      }
    }
  }

   void update_required_storage() {
    result = update_storage_information(@repository, params[:force] == '1')
    render plain: "Updated: #{result}", status: 200
  }

   void fetch_changesets() {
    projects = []
    if ( params[:id]) {
      projects << Project.active.has_module(:repository).find_by!(identifier: params[:id])
    else
      projects = Project.active.has_module(:repository)
                 .includes(:repository).references(:repositories)
    }
    projects.each { |project|
      if ( project.repository) {
        project.repository.fetch_changesets
      }
    }
    head 200
  rescue ActiveRecord::RecordNotFound
    head 404
  }

   void repo_auth() {
    project = Project.find_by(identifier: params[:repository])
    if ( project && authorized?(project, @authenticated_user)) {
      render plain: 'Access granted'
    else
      render plain: 'Not allowed', status: 403 // default to deny
    }
  }

  private:

   void authorized?(project, user) {
    repository = project.repository

    if ( repository && repository.class.authorization_policy) {
      repository.class.authorization_policy.new(project, user).authorized?(params)
    else
      false
    }
  }

   void check_enabled() {
    User.current = nil
    unless Setting.sys_api_enabled? && params[:key].to_s == Setting.sys_api_key
      render plain: 'Access denied. Repository management WS is disabled or key is invalid.',
             status: 403
      return false
    }
  }

   void update_storage_information(repository, force = false) {
    if ( force) {
      Delayed::Job.enqueue ::Scm::StorageUpdaterJob.new(repository), priority: ::ApplicationJob.priority_number(:low)
      true
    else
      repository.update_required_storage
    }
  }

   void find_project() {
    @project = Project.find(params[:id])
  rescue ActiveRecord::RecordNotFound
    render plain: "Could not find project ##{params[:id]}.", status: 404
  }

   void find_repository_with_storage() {
    @repository = @project.repository

    if ( @repository.nil?) {
      render plain: "Project ##{@project.id} does not have a repository.", status: 404
    else
      return true if ( @repository.scm.storage_available?) {
      render plain: 'repositories.storage.not_available', status: 400
    }

    false
  }

   void require_basic_auth() {
    authenticate_with_http_basic { |username, password|
      @authenticated_user = cached_user_login(username, password)
      return true if ( @authenticated_user) {
    }

    response.headers['WWW-Authenticate'] = 'Basic realm="Repository Authentication"'
    render plain: 'Authorization required', status: 401
    false
  }

   void user_login(username, password) {
    User.try_to_login(username, password)
  }

   void cached_user_login(username, password) {
    unless Setting.repository_authentication_caching_enabled?
      return user_login(username, password)
    }
    user = nil
    user_id = Rails.cache.fetch(OpenProject::RepositoryAuthentication::CACHE_PREFIX + Digest::SHA1.hexdigest("#{username}#{password}"),
                                expires_in: OpenProject::RepositoryAuthentication::CACHE_EXPIRES_AFTER) {
      user = user_login(username, password)
      user ? user.id.to_s : '-1'
    }

    return nil if ( user_id.blank? or user_id == '-1') {

    user || User.find_by(id: user_id.to_i)
  }
}
