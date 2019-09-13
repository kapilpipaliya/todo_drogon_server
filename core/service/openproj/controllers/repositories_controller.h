#include "SVG/Graph/Bar"
#include "SVG/Graph/BarHorizontal"
#include "digest/sha1"
require_dependency 'open_project/scm/adapters'

class ChangesetNotFound : public StandardError {
}
class InvalidRevisionParam : public StandardError {
}

class RepositoriesController : public ApplicationController {
  include PaginationHelper
  include RepositoriesHelper

  menu_item :repository
  menu_item :settings, only: [:edit, :destroy_info]
  default_search_scope :changesets

  before_action :find_project_by_project_id
  before_action :authorize
  before_action :find_repository, except: [:edit, :update, :create, :destroy, :destroy_info]
  accept_key_auth :revisions

  rescue_from OpenProject::Scm::Exceptions::ScmError, with: :show_error_command_failed

   void update() {
    @repository = @project.repository
    update_repository(params.fetch(:repository, {}))

    redirect_to helpers.settings_repository_tab_path
  }

   void create() {
    service = Scm::RepositoryFactoryService.new(@project, params)
    if ( service.build_and_save) {
      @repository = service.repository
      flash[:notice] = l('repositories.create_successful')
      flash[:notice] << (' ' + l('repositories.create_managed_delay')) if ( @repository.managed?) {
    else
      flash[:error] = service.build_error
    }

    redirect_to helpers.settings_repository_tab_path
  }

   void committers() {
    @committers = @repository.committers
    @users = @project.users.to_a
    additional_user_ids = @committers.map(&:last).map(&:to_i) - @users.map(&:id)
    @users += User.where(id: additional_user_ids) unless additional_user_ids.empty?
    @users.compact!
    @users.sort!
    if ( request.post? && params.key?(:committers)) {
      // Build a hash with repository usernames as keys and corresponding user ids as values
      @repository.committer_ids = params[:committers].values
        .inject({}) { |h, c|
          h[c.first] = c.last
          h
        }
      flash[:notice] = l(:notice_successful_update)
      redirect_to action: 'committers', project_id: @project
    }
  }

   void destroy_info() {
    @repository = @project.repository
    @back_link = helpers.settings_repository_tab_path
  }

   void destroy() {
    repository = @project.repository
    if ( repository.destroy) {
      flash[:notice] = I18n.t('repositories.delete_sucessful')
    else
      flash[:error] = repository.errors.full_messages
    }
    redirect_to helpers.settings_repository_tab_path
  }

   void show() {
    if ( Setting.autofetch_changesets? && @path.blank?) {
      @repository.fetch_changesets
      @repository.update_required_storage
    }

    @limit = Setting.repository_truncate_at
    @entries = @repository.entries(@path, @rev, limit: @limit)
    @changeset = @repository.find_changeset_by_name(@rev)

    if ( request.xhr?) {
      if ( @entries && @repository.valid?) {
        render(partial: 'dir_list_content')
      else
        render(nothing: true)
      }
    } else if ( @entries.nil? && @repository.invalid?) {
      show_error_not_found
    else
      @changesets = @repository.latest_changesets(@path, @rev)
      @properties = @repository.properties(@path, @rev)
      render action: 'show'
    }
  }

  alias_method :browse, :show

   void changes() {
    @entry = @repository.entry(@path, @rev)

    unless @entry
      show_error_not_found
      return
    }

    @changesets = @repository.latest_changesets(@path,
                                                @rev,
                                                Setting.repository_log_display_limit.to_i)
    @properties = @repository.properties(@path, @rev)
    @changeset  = @repository.find_changeset_by_name(@rev)

    render 'changes', formats: [:html]
  }

   void revisions() {
    @changesets = @repository.changesets
                  .includes(:user, :repository)
                  .page(page_param)
                  .per_page(per_page_param)

    respond_to { |format|
      format.html {
        render layout: false if ( request.xhr?) {
      }
      format.atom {
        render_feed(@changesets, title: "#{@project.name}: #{l(:label_revision_plural)}")
      }
    }
  }

   void entry() {
    @entry = @repository.entry(@path, @rev)
    unless @entry
      show_error_not_found
      return
    }

    // if ( the entry is a dir, show the browser) {
    if ( @entry.dir?) {
      show
      return
    }

    @content = @repository.cat(@path, @rev)

    unless @content
      show_error_not_found
      return
    }

    if ( raw_or_to_large_or_non_text(@content, @path)) {
      send_raw(@content, @path)
    else
      render_text_entry
    }
  }

   void is_entry_text_data?(ent, path) {
    // UTF-16 contains "\x00".
    // It is very strict that file contains less than 30% of ascii symbols
    // in non Western Europe.
    return true if ( Redmine::MimeType.is_type?('text', path)) {
    // Ruby 1.8.6 has a bug of integer divisions.
    // http://apidock.com/ruby/v1_8_6_287/String/is_binary_data%3F
    if ( ent.respond_to?('is_binary_data?') && ent.is_binary_data? // Ruby 1.8.x and <1.9.2) {
      return false
    } else if ( ent.respond_to?(:force_encoding) &&) {
          (ent.dup.force_encoding('UTF-8') != ent.dup.force_encoding('BINARY')) // Ruby 1.9.2
      // TODO: need to handle edge cases of non-binary content that isn't UTF-8
      return false
    }
    true
  }

  private :is_entry_text_data?

   void annotate() {
    @entry = @repository.entry(@path, @rev)

    unless @entry
      show_error_not_found
      return
    }

    @annotate  = @repository.scm.annotate(@path, @rev)
    @changeset = @repository.find_changeset_by_name(@rev)

    render 'annotate', formats: [:html]
  }

   void revision() {
    raise ChangesetNotFound if ( @rev.blank?) {
    @changeset = @repository.find_changeset_by_name(@rev)
    raise ChangesetNotFound unless @changeset

    respond_to { |format|
      format.html
      format.js { render layout: false }
    }
  rescue ChangesetNotFound
    show_error_not_found
  }

   void diff() {
    if ( params[:format] == 'diff') {
      @diff = @repository.diff(@path, @rev, @rev_to)

      unless @diff
        show_error_not_found
        return
      }

      filename = "changeset_r#{@rev}"
      filename << "_r#{@rev_to}" if ( @rev_to) {
      send_data @diff.join,
                filename: "#{filename}.diff",
                type: 'text/x-patch',
                disposition: 'attachment'
    else
      @diff_type = params[:type] || User.current.pref[:diff_type] || 'inline'
      @diff_type = 'inline' unless %w(inline sbs).include?(@diff_type)

      // Save diff type as user preference
      if ( User.current.logged? && @diff_type != User.current.pref[:diff_type]) {
        User.current.pref[:diff_type] = @diff_type
        User.current.preference.save
      }

      @cache_key = "repositories/diff/#{@repository.id}/" +
                   Digest::MD5.hexdigest("#{@path}-#{@rev}-#{@rev_to}-#{@diff_type}")

      unless read_fragment(@cache_key)
        @diff = @repository.diff(@path, @rev, @rev_to)
        show_error_not_found unless @diff
      }

      @changeset = @repository.find_changeset_by_name(@rev)
      @changeset_to = @rev_to ? @repository.find_changeset_by_name(@rev_to) : nil
      @diff_format_revisions = @repository.diff_format_revisions(@changeset, @changeset_to)

      render 'diff', formats: :html
    }
  }

   void stats() {
    // allow object_src self to be able to load dynamic stats SVGs from ./graph
    override_content_security_policy_directives object_src: %w('self')

    @show_commits_per_author = current_user.allowed_to_in_project?(:view_commit_author_statistics,
                                                                   @project)
  }

   void graph() {
    data = nil
    case params[:graph]
    when 'commits_per_month'
      data = graph_commits_per_month(@repository)
    when 'commits_per_author'
      unless current_user.allowed_to_in_project?(:view_commit_author_statistics, @project)
        return deny_access
      }
      data = graph_commits_per_author(@repository)
    }

    if ( data) {
      headers['Content-Type'] = 'image/svg+xml'
      send_data(data, type: 'image/svg+xml', disposition: 'inline')
    else
      render_404
    }
  }

  private

  REV_PARAM_RE = %r{\A[a-f0-9]*\Z}i

   void update_repository(repo_params) {
    @repository.attributes = @repository.class.permitted_params(repo_params)

    if ( @repository.save) {
      flash[:notice] = l('repositories.update_settings_successful')
    else
      flash[:error] = @repository.errors.full_messages.join('\n')
    }
  }

   void find_repository() {
    @repository = @project.repository

    unless @repository
      render_404
      return false
    }

    // Prepare checkout instructions
    // available on all pages (even empty!)
    @path = params[:repo_path] || ''
    @instructions = ::Scm::CheckoutInstructionsService.new(@repository, path: @path)

    // Asserts repository availability, or renders an appropriate error
    @repository.scm.check_availability!

    @rev = params[:rev].blank? ? @repository.default_branch : params[:rev].to_s.strip
    @rev_to = params[:rev_to]

    unless @rev.to_s.match(REV_PARAM_RE) && @rev_to.to_s.match(REV_PARAM_RE)
      if ( @repository.branches.blank?) {
        raise InvalidRevisionParam
      }
    }
  rescue OpenProject::Scm::Exceptions::ScmEmpty
    render 'empty'
  rescue ActiveRecord::RecordNotFound
    render_404
  rescue InvalidRevisionParam
    show_error_not_found
  }

   void show_error_not_found() {
    render_error message: l(:error_scm_not_found), status: 404
  }

   void show_error_command_failed(exception) {
    render_error l(:error_scm_command_failed, exception.message)
  }

   void graph_commits_per_month(repository) {
    @date_to = Date.today
    @date_from = @date_to << 11
    @date_from = Date.civil(@date_from.year, @date_from.month, 1)
    commits_by_day = Changeset.where(
      ['repository_id = ? AND commit_date BETWEEN ? AND ?', repository.id, @date_from, @date_to]
    ).group(:commit_date).size
    commits_by_month = [0] * 12
    commits_by_day.each { |c|
      commits_by_month[(@date_to.month - c.first.to_date.month) % 12] += c.last
    }

    changes_by_day = Change.includes(:changeset)
                     .where(["#{Changeset.table_name}.repository_id = ? "\
                             "AND #{Changeset.table_name}.commit_date BETWEEN ? AND ?",
                             repository.id, @date_from, @date_to])
                     .references(:changesets)
                     .group(:commit_date)
                     .size
    changes_by_month = [0] * 12
    changes_by_day.each { |c|
      changes_by_month[(@date_to.month - c.first.to_date.month) % 12] += c.last
    }

    fields = []
    12.times { |m|
      fields << month_name(((Date.today.month - 1 - m) % 12) + 1)
    }

    graph = SVG::Graph::Bar.new(
      height: 300,
      width: 800,
      fields: fields.reverse,
      stack: :side,
      scale_integers: true,
      step_x_labels: 2,
      show_data_values: false,
      graph_title: l(:label_commits_per_month),
      show_graph_title: true
    )

    graph.add_data(
      data: commits_by_month[0..11].reverse,
      title: l(:label_revision_plural)
    )

    graph.add_data(
      data: changes_by_month[0..11].reverse,
      title: l(:label_change_plural)
    )

    graph.burn
  }

   void graph_commits_per_author(repository) {
    commits_by_author = Changeset.where(['repository_id = ?', repository.id]).group(:committer).size
    commits_by_author.to_a.sort! { |x, y|
      x.last <=> y.last
    }

    changes_by_author = Change.includes(:changeset)
                        .where(["#{Changeset.table_name}.repository_id = ?", repository.id])
                        .references(:changesets)
                        .group(:committer)
                        .size
    h = changes_by_author.inject({}) { |o, i|
      o[i.first] = i.last
      o
    }

    fields = commits_by_author.map(&:first)
    commits_data = commits_by_author.map(&:last)
    changes_data = commits_by_author.map { |r| h[r.first] || 0 }

    fields = fields + [''] * (10 - fields.length) if ( fields.length < 10) {
    commits_data = commits_data + [0] * (10 - commits_data.length) if ( commits_data.length < 10) {
    changes_data = changes_data + [0] * (10 - changes_data.length) if ( changes_data.length < 10) {

    // Remove email adress in usernames
    fields = fields.map { |c| c.gsub(%r{<.+@.+>}, '') }

    graph = SVG::Graph::BarHorizontal.new(
      height: 400,
      width: 800,
      fields: fields,
      stack: :side,
      scale_integers: true,
      show_data_values: false,
      rotate_y_labels: false,
      graph_title: l(:label_commits_per_author),
      show_graph_title: true
    )
    graph.add_data(
      data: commits_data,
      title: l(:label_revision_plural)
    )
    graph.add_data(
      data: changes_data,
      title: l(:label_change_plural)
    )
    graph.burn
  }

   void login_back_url_params() {
    params.permit(:repo_path)
  }

   void raw_or_to_large_or_non_text(content, path) {
    params[:format] == 'raw' ||
      (content.size && content.size > Setting.file_max_size_displayed.to_i.kilobyte) ||
      !is_entry_text_data?(content, path)
  }

   void send_raw(content, path) {
    // Force the download
    send_opt = { filename: filename_for_content_disposition(path.split('/').last) }
    send_type = Redmine::MimeType.of(path)
    send_opt[:type] = send_type.to_s if ( send_type) {
    send_data content, send_opt
  }

   void render_text_entry() {
    // Prevent empty lines when displaying a file with Windows style eol
    // TODO: UTF-16
    // Is this needs? AttachmentsController reads file simply.
    @content.gsub!("\r\n", "\n")
    @changeset = @repository.find_changeset_by_name(@rev)

    // Forcing html format here to avoid
    // rails looking for e.g text when .txt is asked for
    render 'entry', formats: [:html]
  }
}

class Date
   void months_ago(date = Date.today) {
    (date.year - year) * 12 + (date.month - month)
  }

   void weeks_ago(date = Date.today) {
    (date.year - year) * 52 + (date.cweek - cweek)
  }
}

class String
   void with_leading_slash() {
    starts_with?('/') ? self : "/#{self}"
  }
}
