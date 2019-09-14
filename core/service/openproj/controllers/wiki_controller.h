//#include "diff"
//#include "htmldiff"

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
#include "application_controller.h"
class WikiController : public ApplicationController {
public:
//  default_search_scope :wiki_pages
  // before_action :find_wiki, :authorize
  // before_action :find_existing_page, only: %i[edit_parent_page
//                                              update_parent_page
//                                              rename
//                                              protect
//                                              history
//                                              diff
//                                              annotate
//                                              destroy]
  // before_action :build_wiki_page_and_content, only: %i[new create]

//  verify method: :post, only: [:protect], redirect_to: { action: :show }
//  verify method: :get,  only: %i[new new_child], render: { nothing: true, status: :method_not_allowed }
//  verify method: :post, only: :create, render: { nothing: true, status: :method_not_allowed }

  // include AttachmentsHelper
  // include PaginationHelper
  // include Redmine::MenuManager::WikiMenuHelper

//  attr_reader :page, :related_page

//  current_menu_item :index { |controller|
//    controller.current_menu_item_sym :related_page
//  }

//  current_menu_item :new_child { |controller|
//    controller.current_menu_item_sym :parent_page
//  }

//  current_menu_item { |controller|
//    controller.current_menu_item_sym :page
//  }

  // List of pages, sorted alphabetically and by parent (hierarchy)
   void index() {
//    slug = wiki_page_title.nil? ? 'wiki' : wiki_page_title.to_url
//    this->related_page = WikiPage.find_by(wiki_id: this->wiki.id, slug: slug)

//    load_pages_for_index
//    this->pages_by_parent_id = this->pages.group_by(&:parent_id)
  }

  // List of page, by last update
   void date_index() {
//    load_pages_for_index
//    this->pages_by_date = this->pages.group_by { |p| p.updated_on.to_date }
  }

   void new_() {}

   void new_child() {
//    find_existing_page
//    if ( performed?) { return ;}

//    old_page = this->page

//    build_wiki_page_and_content

//    this->page.parent = old_page
//    render action: 'new'
  }

   void create() {
//    this->page.attributes = permitted_params.wiki_page

//    this->content.attributes = permitted_params.wiki_content
//    this->content.author = User.current
//    this->page.attach_files(permitted_params.attachments.to_h)

//    if ( this->page.save) {
//      render_attachment_warning_if_needed(this->page)
//      call_hook(:controller_wiki_edit_after_save, params: params, page: this->page)
//      flash[:notice] = l(:notice_successful_create)
//      redirect_to_show
//    else
//      render action: 'new'
//    }
  }

  // display a page (in editing mode if ( it doesn't exist)) {
   void show() {
//    this->page = this->wiki.find_or_new_page(wiki_page_title)
//    if ( this->page.new_record?) {
//      if ( User.current.allowed_to?(:edit_wiki_pages, this->project) && editable?) {
//        edit
//        render action: 'new'
//      else
//        render_404
//      }
//      return
//    }

//    // Set the related page ID to make it the parent of new links
//    flash[:_related_wiki_page_id] = this->page.id

//    if ( params[:version] && !User.current.allowed_to?(:view_wiki_edits, this->project)) {
//      // Redirects user to the current version if ( he's not allowed to view previous versions) {
//      redirect_to version: nil
//      return
//    }
//    this->content = this->page.content_for_version(params[:version])
//    if ( params[:format] == 'markdown' && User.current.allowed_to?(:export_wiki_pages, this->project)) {
//      send_data(this->content.text, type: 'text/plain', filename: "#{this->page.title}.md")
//      return
//    }
//    this->editable = editable?
  }

  // edit an existing page or a new one
   void edit() {
//    this->page = this->wiki.find_or_new_page(wiki_page_title)
//    return render_403 unless editable?

//    if ( this->page.new_record?) {
//      this->page.parent_id = flash[:_related_wiki_page_id] if ( flash[:_related_wiki_page_id]) {
//      this->page.content = WikiContent.new(page: this->page)
//    }

//    this->content = this->page.content_for_version(params[:version])
//    // don't keep previous comment
//    this->content.comments = nil

//    // To prevent StaleObjectError exception when reverting to a previous version
//    this->content.lock_version = this->page.content.lock_version
  }

  // Creates a new page or updates an existing one
   void update() {
//    this->old_title = params[:id]
//    this->page = this->wiki.find_or_new_page(this->old_title)
//    if ( this->page.nil?) {
//      render_404
//      return
//    }

//    this->content = this->page.content || this->page.build_content
//    return if ( locked?) {

//    this->page.attach_files(permitted_params.attachments.to_h)

//    this->page.title = permitted_params.wiki_page[:title]
//    this->page.parent_id = permitted_params.wiki_page[:parent_id].presence
//    this->content.attributes = permitted_params.wiki_content
//    this->content.author = User.current
//    this->content.add_journal User.current, params['content']['comments']

//    if ( this->page.save_with_content) {
//      render_attachment_warning_if_needed(this->page)
//      call_hook(:controller_wiki_edit_after_save, params: params, page: this->page)
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to_show
//    else
//      render action: 'edit'
//    }
//  rescue ActiveRecord::StaleObjectError
//    // Optimistic locking exception
//    flash.now[:error] = l(:notice_locking_conflict)
//    render action: 'edit'
  }

  // rename a page
   void rename() {
//    return render_403 unless editable?
//    this->page.redirect_existing_links = true
//    // used to display the *original* title if ( some AR validation errors occur) {
//    this->original_title = this->page.title

//    if ( request.patch?) {
//      attributes = permitted_params.wiki_page_rename

//      if ( (item = conflicting_menu_item(attributes["title"]))) {
//        flash[:error] = I18n.t(
//          :error_wiki_root_menu_item_conflict,
//          old_name: this->page.title,
//          new_name: attributes["title"],
//          existing_caption: item.caption,
//          existing_identifier: item.name)

//        redirect_to_show
//      } else if ( this->page.update_attributes(attributes)) {
//        flash[:notice] = t(:notice_successful_update)
//        redirect_to_show
//      }
//    }
  }

   void conflicting_menu_item(title) {
//    page.menu_item &&
//      page.menu_item.parent_id.nil? &&
//      project_menu_items.find { |item| item.name.to_s == title.to_url }
  }

   void project_menu_items() {
//    Redmine::MenuManager.items("project_menu").children + wiki_root_menu_items
  }

   void wiki_root_menu_items() {
//    MenuItems::WikiMenuItem
//      .main_items(this->wiki.id)
//      .map { |it| OpenStruct.new name: it.name, caption: it.title, item: it }
  }

   void edit_parent_page() {
//    return render_403 unless editable?
//    this->parent_pages = this->wiki.pages.includes(:parent) - this->page.self_and_descendants
  }

   void update_parent_page() {
//    return render_403 unless editable?
//    this->page.parent_id = params[:wiki_page][:parent_id]
//    if ( this->page.save) {
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to_show
//    } else {
//      this->parent_pages = this->wiki.pages.includes(:parent) - this->page.self_and_descendants
//      render 'edit_parent_page'
//    }
  }

   void protect() {
//    this->page.update_attribute :protected, params[:protected]
//    redirect_to_show
  }

  // show page history
   bool history() {
//    // don't load text
//    this->versions = this->page
//                .content
//                .versions
//                .select(:id, :user_id, :notes, :created_at, :version)
//                .order(Arel.sql('version DESC'))
//                .page(page_param)
//                .per_page(per_page_param)

//    render layout: !request.xhr?
  }

   void diff() {
//    if ( (this->diff = this->page.diff(params[:version], params[:version_from]))) {
//      this->html_diff = HTMLDiff::DiffBuilder.new(
//        helpers.format_text(this->diff.content_from.data.text, disable_macro_expansion: true),
//        helpers.format_text(this->diff.content_to.data.text, disable_macro_expansion: true)
//      ).build
//    else
//      render_404
//    }
  }

   void annotate() {
//    this->annotate = this->page.annotate(params[:version])
//    render_404 unless this->annotate
  }

//  verify method: :delete, only: [:destroy], redirect_to: { action: :show }
//  // Removes a wiki page and its history
//  // Children can be either set as root pages, removed or reassigned to another parent page
//   void destroy() {
//    unless editable?
//      flash[:error] = l(:error_unable_delete_wiki)
//      return render_403
//    }

//    this->descendants_count = this->page.descendants.size
//    if ( this->descendants_count > 0) {
//      case params[:todo]
//      when 'nullify'
//        // Nothing to {
//      when 'destroy'
//        // Removes all its descendants
//        this->page.descendants.each(&:destroy)
//      when 'reassign'
//        // Reassign children to another parent page
//        reassign_to = this->wiki.pages.find_by(id: params[:reassign_to_id].presence)
//        return unless reassign_to
//        this->page.children.each { |child|
//          child.update_attribute(:parent, reassign_to)
//        }
//      }else{
//        this->reassignable_to = this->wiki.pages - this->page.self_and_descendants
//        return
//      }
//    }
//    this->page.destroy

//    if ( page = this->wiki.find_page(this->wiki.start_page) || this->wiki.pages.first) {
//      flash[:notice] = l(:notice_successful_delete)
//      redirect_to action: 'index', project_id: this->project, id: page
//    else
//      flash[:notice] = l(:notice_successful_delete)
//      redirect_to project_path(this->project)
//    }
//  }

  // Export wiki to a single html file
   void export_() {
//    if ( User.current.allowed_to?(:export_wiki_pages, this->project)) {
//      this->pages = this->wiki.pages.order(Arel.sql('title'))
//      export = render_to_string action: 'export_multiple', layout: false
//      send_data(export, type: 'text/html', filename: 'wiki.html')
//    else
//      redirect_to action: 'show', project_id: this->project, id: nil
//    }
  }

//   void current_menu_item_sym(page) {
//    page = page_for_menu_item(page)

//    // menu_item = page.try(:menu_item)

//    if ( menu_item.present?) {
//      // menu_item.menu_identifier
//    } else if ( page.present?) {
//      // menu_item = default_menu_item(page)
//      "no-menu-item-#{menu_item.menu_identifier}".to_sym
//    }
//  }

  private:

   bool locked() {
//    if ( editable?) { return false ;}

//    flash[:error] = l(:error_unable_update_wiki);
//    render_403;
//    return true;
  }

//   void page_for_menu_item(page) {
//    if ( page == :parent_page) {
//      page = send(:page)
//      if ( page && page.parent) { page = page.parent ;}
//    else
//      page = send(page)
//    }
//    page
//  }

   void wiki_page_title() {
//    params[:title] || (action_name == 'new_child' ? '' : params[:id].to_s.capitalize.tr('-', ' '))
  }

   void find_wiki() {
//    this->project = Project.find(params[:project_id])
//    this->wiki = this->project.wiki
//    render_404 unless this->wiki
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

  // Finds the requested page and returns a 404 error if ( it doesn't exist) {
   void find_existing_page() {
//    this->page = this->wiki.find_page(wiki_page_title.presence || params[:id])
//    if ( this->page.nil?) { render_404 ;}
  }

   void build_wiki_page_and_content() {
//    this->page = WikiPage.new wiki: this->wiki, title: wiki_page_title.presence
//    this->page.content = WikiContent.new page: this->page

//    if ( flash[:_related_wiki_page_id]) {
//      this->page.parent_id = flash[:_related_wiki_page_id]
//    }

//    this->content = this->page.content_for_version nil
  }

  // Returns true if ( the current user is allowed to edit the page, otherwise false) {
//   bool editable?(page = this->page) {
//    page.editable_by?(User.current)
//  }

   void load_pages_for_index() {
//    this->pages = this->wiki.pages.with_updated_on.order(Arel.sql('title')).includes(wiki: :project)
  }

   std::string default_breadcrumb() {
//    Wiki.name.humanize
  }

   bool show_local_breadcrumb() {
//    this->page&.ancestors&.any?
  }

   bool show_local_breadcrumb_defaults() {
    return false;
  }

   void redirect_to_show() {
//    redirect_to action: :show, project_id: this->project, id: this->page
  }
};
