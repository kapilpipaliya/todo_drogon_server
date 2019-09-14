#pragma once
#include "application_controller.h"
namespace openproject {
class WikiMenuItemsController : public ApplicationController {
public:
//  attr_reader :wiki_menu_item

  // include Redmine::MenuManager::WikiMenuHelper

//  current_menu_item :edit { |controller|
//    if ( controller.wiki_menu_item.persisted?) { next controller.wiki_menu_item.menu_identifier ;}

//    project = controller.instance_variable_get(:this->project)
//    if ( (page = WikiPage.find_by(wiki_id: project.wiki.id, slug: controller.params[:id]))) {
//      default_menu_item(controller, page)
//    }
//  }

//  current_menu_item :select_main_menu_item { |controller|
//    if ( controller.wiki_menu_item.try(:persisted?)) { next controller.wiki_menu_item.menu_identifier ;}

//    if ( (page = WikiPage.find_by(id: controller.params[:id]))) {
//      default_menu_item(controller, page)
//    }
//  }

//   void default_menu_item(controller, page) {
    // menu_item = controller.default_menu_item(page)
//    "no-menu-item-#{menu_item.menu_identifier}".to_sym
//  }

  // before_action :find_project_by_project_id
  // before_action :authorize

   void edit() {
//    get_data_from_params(params)
  }

   void update() {
//    wiki_menu_setting = wiki_menu_item_params[:setting]
//    parent_wiki_menu_item = params[:parent_wiki_menu_item]

//    get_data_from_params(params)

//    if ( wiki_menu_setting == 'no_item') {
//      unless this->wiki_menu_item.nil?
//        if ( this->wiki_menu_item.is_only_main_item?) {
//          if ( this->page.only_wiki_page?) {
//            flash.now[:error] = t(:wiki_menu_item_delete_not_permitted)
//            render(:edit, id: this->page_title) and return
//          else
//            redirect_to(select_main_menu_item_project_wiki_path(this->project, this->page.id)) and return
//          }
//        else
//          this->wiki_menu_item.destroy
//        }
//      }
//    else {
//      this->wiki_menu_item.navigatable_id = this->page.wiki.id
//      this->wiki_menu_item.name = this->page.slug
//      this->wiki_menu_item.title = wiki_menu_item_params[:title] || this->page_title

//      if ( wiki_menu_setting == 'sub_item') {
//        this->wiki_menu_item.parent_id = parent_wiki_menu_item
//      } else if ( wiki_menu_setting == 'main_item') {
//        this->wiki_menu_item.parent_id = nil
//        assign_wiki_menu_item_params this->wiki_menu_item
//      }
//    }

//    if ( this->wiki_menu_item.destroyed? || this->wiki_menu_item.save) {
//      // we may have just destroyed a new record
//      // e.g. there was no menu_item before, and there is none now
//      if ( !this->wiki_menu_item.new_record? && (this->wiki_menu_item.changed? || this->wiki_menu_item.destroyed?)) {
//        flash[:notice] = t(:notice_successful_update)
//      }

//      redirect_back_or_default(action: 'edit', id: this->page)
//    else
//      respond_to { |format|
//        format.html {
//          render action: 'edit', id: this->page
//        }
//      }
//    }
  }

   void select_main_menu_item() {
//    this->page = WikiPage.find params[:id]
//    this->possible_wiki_pages = this->project
//                           .wiki
//                           .pages
//                           .includes(:parent)
//                           .reject { |page|
//                             page != this->page &&
//                               page.menu_item.present? &&
//                               page.menu_item.is_main_item?
//                           }
  }

   void replace_main_menu_item() {
//    current_page = WikiPage.find params[:id]

//    if ( (current_menu_item = current_page.menu_item) && (page = WikiPage.find_by(id: params[:wiki_page][:id])) && current_menu_item != page.menu_item) {
//      create_main_menu_item_for_wiki_page(page, current_menu_item.options)
//      current_menu_item.destroy
//    }

//    redirect_to action: :edit, id: current_page
  }

  private:

   void wiki_menu_item_params() {
//    this->wiki_menu_item_params ||= params.require(:menu_items_wiki_menu_item).permit(:name, :title, :navigatable_id, :parent_id, :setting, :new_wiki_page, :index_page)
  }

//   void get_data_from_params(params) {
//    wiki = this->project.wiki

//    this->page = wiki.find_page(params[:id])
//    this->page_title = this->page.title
//    this->wiki_menu_item = MenuItems::WikiMenuItem
//                      .where(navigatable_id: wiki.id, name: this->page.slug)
//                      .first_or_initialize(title: this->page_title)

//    possible_parent_menu_items = MenuItems::WikiMenuItem.main_items(wiki.id) - [this->wiki_menu_item]

//    this->parent_menu_item_options = possible_parent_menu_items.map { |item| [item.name, item.id] }

//    this->selected_parent_menu_item_id = if ( this->wiki_menu_item.parent) {
//                                      this->wiki_menu_item.parent.id
//                                    } else {
//                                      this->page.nearest_main_item.try :id
//                                    }
//  }

//   void assign_wiki_menu_item_params(menu_item) {
//    if ( wiki_menu_item_params[:new_wiki_page] == '1') {
//      // menu_item.new_wiki_page = true
//    } else if ( wiki_menu_item_params[:new_wiki_page] == '0') {
//      // menu_item.new_wiki_page = false
//    }

//    if ( wiki_menu_item_params[:index_page] == '1') {
//      // menu_item.index_page = true
//    } else if ( wiki_menu_item_params[:index_page] == '0') {
//      // menu_item.index_page = false
//    }
//  }

//   void create_main_menu_item_for_wiki_page(page, options = {}) {
//    wiki = page.wiki

//     menu_item = if ( item = page.menu_item) {
//                  item.tap { |item| item.parent_id = nil }
//                else
//                  wiki.wiki_menu_items.build(name: page.slug, title: page.title)
//    }

    // menu_item.options = options
    // menu_item.save
  // }
};
}
