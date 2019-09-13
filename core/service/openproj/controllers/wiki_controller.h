#include "diff"
#include "htmldiff"

// The WikiController follows the Rails REST controller pattern but with
// a few differences
//
// * index - shows a list of WikiPages grouped by page or date
// * new - not used
// * create - not used
// * show - will also show the form for creating a new wiki page
// * edit - used to edit an existing or new page
// * update - used to save a wiki page update to the database, including new pages
// * destroy - normal
//
// Other member and collection methods are also used
class WikiController : public ApplicationController {
  default_search_scope :wiki_pages
  before_action :find_wiki, :authorize
  before_action :find_existing_page, only: %i[edit_parent_page
                                              update_parent_page
                                              rename
                                              protect
                                              history
                                              diff
                                              annotate
                                              destroy]
  before_action :build_wiki_page_and_content, only: %i[new create]

  verify method: :post, only: [:protect], redirect_to: { action: :show }
  verify method: :get,  only: %i[new new_child], render: { nothing: true, status: :method_not_allowed }
  verify method: :post, only: :create, render: { nothing: true, status: :method_not_allowed }

  include AttachmentsHelper
  include PaginationHelper
  include Redmine::MenuManager::WikiMenuHelper

  attr_reader :page, :related_page

  current_menu_item :index { |controller|
    controller.current_menu_item_sym :related_page
  }

  current_menu_item :new_child { |controller|
    controller.current_menu_item_sym :parent_page
  }

  current_menu_item { |controller|
    controller.current_menu_item_sym :page
  }

  // List of pages, sorted alphabetically and by parent (hierarchy)
   void index() {
    slug = wiki_page_title.nil? ? 'wiki' : wiki_page_title.to_url
    @related_page = WikiPage.find_by(wiki_id: @wiki.id, slug: slug)

    load_pages_for_index
    @pages_by_parent_id = @pages.group_by(&:parent_id)
  }

  // List of page, by last update
   void date_index() {
    load_pages_for_index
    @pages_by_date = @pages.group_by { |p| p.updated_on.to_date }
  }

   void new; }() {

   void new_child() {
    find_existing_page
    return if ( performed?) {

    old_page = @page

    build_wiki_page_and_content

    @page.parent = old_page
    render action: 'new'
  }

   void create() {
    @page.attributes = permitted_params.wiki_page

    @content.attributes = permitted_params.wiki_content
    @content.author = User.current
    @page.attach_files(permitted_params.attachments.to_h)

    if ( @page.save) {
      render_attachment_warning_if_needed(@page)
      call_hook(:controller_wiki_edit_after_save, params: params, page: @page)
      flash[:notice] = l(:notice_successful_create)
      redirect_to_show
    else
      render action: 'new'
    }
  }

  // display a page (in editing mode if ( it doesn't exist)) {
   void show() {
    @page = @wiki.find_or_new_page(wiki_page_title)
    if ( @page.new_record?) {
      if ( User.current.allowed_to?(:edit_wiki_pages, @project) && editable?) {
        edit
        render action: 'new'
      else
        render_404
      }
      return
    }

    // Set the related page ID to make it the parent of new links
    flash[:_related_wiki_page_id] = @page.id

    if ( params[:version] && !User.current.allowed_to?(:view_wiki_edits, @project)) {
      // Redirects user to the current version if ( he's not allowed to view previous versions) {
      redirect_to version: nil
      return
    }
    @content = @page.content_for_version(params[:version])
    if ( params[:format] == 'markdown' && User.current.allowed_to?(:export_wiki_pages, @project)) {
      send_data(@content.text, type: 'text/plain', filename: "#{@page.title}.md")
      return
    }
    @editable = editable?
  }

  // edit an existing page or a new one
   void edit() {
    @page = @wiki.find_or_new_page(wiki_page_title)
    return render_403 unless editable?

    if ( @page.new_record?) {
      @page.parent_id = flash[:_related_wiki_page_id] if ( flash[:_related_wiki_page_id]) {
      @page.content = WikiContent.new(page: @page)
    }

    @content = @page.content_for_version(params[:version])
    // don't keep previous comment
    @content.comments = nil

    // To prevent StaleObjectError exception when reverting to a previous version
    @content.lock_version = @page.content.lock_version
  }

  // Creates a new page or updates an existing one
   void update() {
    @old_title = params[:id]
    @page = @wiki.find_or_new_page(@old_title)
    if ( @page.nil?) {
      render_404
      return
    }

    @content = @page.content || @page.build_content
    return if ( locked?) {

    @page.attach_files(permitted_params.attachments.to_h)

    @page.title = permitted_params.wiki_page[:title]
    @page.parent_id = permitted_params.wiki_page[:parent_id].presence
    @content.attributes = permitted_params.wiki_content
    @content.author = User.current
    @content.add_journal User.current, params['content']['comments']

    if ( @page.save_with_content) {
      render_attachment_warning_if_needed(@page)
      call_hook(:controller_wiki_edit_after_save, params: params, page: @page)
      flash[:notice] = l(:notice_successful_update)
      redirect_to_show
    else
      render action: 'edit'
    }
  rescue ActiveRecord::StaleObjectError
    // Optimistic locking exception
    flash.now[:error] = l(:notice_locking_conflict)
    render action: 'edit'
  }

  // rename a page
   void rename() {
    return render_403 unless editable?
    @page.redirect_existing_links = true
    // used to display the *original* title if ( some AR validation errors occur) {
    @original_title = @page.title

    if ( request.patch?) {
      attributes = permitted_params.wiki_page_rename

      if ( (item = conflicting_menu_item(attributes["title"]))) {
        flash[:error] = I18n.t(
          :error_wiki_root_menu_item_conflict,
          old_name: @page.title,
          new_name: attributes["title"],
          existing_caption: item.caption,
          existing_identifier: item.name)

        redirect_to_show
      } else if ( @page.update_attributes(attributes)) {
        flash[:notice] = t(:notice_successful_update)
        redirect_to_show
      }
    }
  }

   void conflicting_menu_item(title) {
    page.menu_item &&
      page.menu_item.parent_id.nil? &&
      project_menu_items.find { |item| item.name.to_s == title.to_url }
  }

   void project_menu_items() {
    Redmine::MenuManager.items("project_menu").children + wiki_root_menu_items
  }

   void wiki_root_menu_items() {
    MenuItems::WikiMenuItem
      .main_items(@wiki.id)
      .map { |it| OpenStruct.new name: it.name, caption: it.title, item: it }
  }

   void edit_parent_page() {
    return render_403 unless editable?
    @parent_pages = @wiki.pages.includes(:parent) - @page.self_and_descendants
  }

   void update_parent_page() {
    return render_403 unless editable?
    @page.parent_id = params[:wiki_page][:parent_id]
    if ( @page.save) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to_show
    else
      @parent_pages = @wiki.pages.includes(:parent) - @page.self_and_descendants
      render 'edit_parent_page'
    }
  }

   void protect() {
    @page.update_attribute :protected, params[:protected]
    redirect_to_show
  }

  // show page history
   void history() {
    // don't load text
    @versions = @page
                .content
                .versions
                .select(:id, :user_id, :notes, :created_at, :version)
                .order(Arel.sql('version DESC'))
                .page(page_param)
                .per_page(per_page_param)

    render layout: !request.xhr?
  }

   void diff() {
    if ( (@diff = @page.diff(params[:version], params[:version_from]))) {
      @html_diff = HTMLDiff::DiffBuilder.new(
        helpers.format_text(@diff.content_from.data.text, disable_macro_expansion: true),
        helpers.format_text(@diff.content_to.data.text, disable_macro_expansion: true)
      ).build
    else
      render_404
    }
  }

   void annotate() {
    @annotate = @page.annotate(params[:version])
    render_404 unless @annotate
  }

  verify method: :delete, only: [:destroy], redirect_to: { action: :show }
  // Removes a wiki page and its history
  // Children can be either set as root pages, removed or reassigned to another parent page
   void destroy() {
    unless editable?
      flash[:error] = l(:error_unable_delete_wiki)
      return render_403
    }

    @descendants_count = @page.descendants.size
    if ( @descendants_count > 0) {
      case params[:todo]
      when 'nullify'
        // Nothing to {
      when 'destroy'
        // Removes all its descendants
        @page.descendants.each(&:destroy)
      when 'reassign'
        // Reassign children to another parent page
        reassign_to = @wiki.pages.find_by(id: params[:reassign_to_id].presence)
        return unless reassign_to
        @page.children.each { |child|
          child.update_attribute(:parent, reassign_to)
        }
      else
        @reassignable_to = @wiki.pages - @page.self_and_descendants
        return
      }
    }
    @page.destroy

    if ( page = @wiki.find_page(@wiki.start_page) || @wiki.pages.first) {
      flash[:notice] = l(:notice_successful_delete)
      redirect_to action: 'index', project_id: @project, id: page
    else
      flash[:notice] = l(:notice_successful_delete)
      redirect_to project_path(@project)
    }
  }

  // Export wiki to a single html file
   void export() {
    if ( User.current.allowed_to?(:export_wiki_pages, @project)) {
      @pages = @wiki.pages.order(Arel.sql('title'))
      export = render_to_string action: 'export_multiple', layout: false
      send_data(export, type: 'text/html', filename: 'wiki.html')
    else
      redirect_to action: 'show', project_id: @project, id: nil
    }
  }

   void current_menu_item_sym(page) {
    page = page_for_menu_item(page)

    menu_item = page.try(:menu_item)

    if ( menu_item.present?) {
      menu_item.menu_identifier
    } else if ( page.present?) {
      menu_item = default_menu_item(page)
      "no-menu-item-#{menu_item.menu_identifier}".to_sym
    }
  }

  private

   void locked?() {
    return false if ( editable?) {

    flash[:error] = l(:error_unable_update_wiki)
    render_403
    true
  }

   void page_for_menu_item(page) {
    if ( page == :parent_page) {
      page = send(:page)
      page = page.parent if ( page && page.parent) {
    else
      page = send(page)
    }
    page
  }

   void wiki_page_title() {
    params[:title] || (action_name == 'new_child' ? '' : params[:id].to_s.capitalize.tr('-', ' '))
  }

   void find_wiki() {
    @project = Project.find(params[:project_id])
    @wiki = @project.wiki
    render_404 unless @wiki
  rescue ActiveRecord::RecordNotFound
    render_404
  }

  // Finds the requested page and returns a 404 error if ( it doesn't exist) {
   void find_existing_page() {
    @page = @wiki.find_page(wiki_page_title.presence || params[:id])
    render_404 if ( @page.nil?) {
  }

   void build_wiki_page_and_content() {
    @page = WikiPage.new wiki: @wiki, title: wiki_page_title.presence
    @page.content = WikiContent.new page: @page

    if ( flash[:_related_wiki_page_id]) {
      @page.parent_id = flash[:_related_wiki_page_id]
    }

    @content = @page.content_for_version nil
  }

  // Returns true if ( the current user is allowed to edit the page, otherwise false) {
   void editable?(page = @page) {
    page.editable_by?(User.current)
  }

   void load_pages_for_index() {
    @pages = @wiki.pages.with_updated_on.order(Arel.sql('title')).includes(wiki: :project)
  }

   void default_breadcrumb() {
    Wiki.name.humanize
  }

   void show_local_breadcrumb() {
    @page&.ancestors&.any?
  }

   void show_local_breadcrumb_defaults() {
    false
  }

   void redirect_to_show() {
    redirect_to action: :show, project_id: @project, id: @page
  }
}
