#pragma once
#include "activerecord.h"
#include "Wikis.h"
namespace openproj {
namespace models {
class Wiki : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::Wikis {
  // belongs_to :project
  // has_many :pages, -> {
//    order("title")
//  }, class_name: "WikiPage", dependent: :destroy
  // has_many :wiki_menu_items, -> {
//    order("name")
//  }, class_name: "MenuItems::WikiMenuItem", dependent: :delete_all, foreign_key: "navigatable_id"
  // has_many :redirects, class_name: "WikiRedirect", dependent: :delete_all

//  acts_as_watchable permission: :view_wiki_pages

//  accepts_nested_attributes_for :wiki_menu_items,
//                                allow_destroy: true,
//                                reject_if (: proc { |attr| attr["name"].blank? && attr["title"].blank? }) {

  // validates_presence_of :start_page

  // after_create :create_menu_item_for_start_page

//   void visible?(user = User.current) {
//    !user.nil? && user.allowed_to?(:view_wiki_pages, project)
//  }

  // find the page with the given title
  // if ( page doesn"t exist, return a new page) {
//   void find_or_new_page(title) {
//    if ( title.blank?) { title = start_page ;}
//    find_page(title) || WikiPage.new(wiki: self, title: title)
//  }

  //
  // Find the page with the given title.
  // Tries the original title and the legacy titleized format.
//   void find_page(title, options = {}) {
//    if ( title.blank?) { title = start_page ;}

//    page = pages.where(slug: title.to_url).first
//    if ( !page && !(options[:with_redirect] == false)) {
//      // search for a redirect
//      redirect = matching_redirect(title)
//      if ( redirect) { page = find_page(redirect.redirects_to, with_redirect: false) ;}
//    }
//    page
//  }

  // Finds a page by title
  // The given string can be of one of the forms: "title" or "project:title"
  // Examples:
  //   Wiki.find_page("bar", project => foo)
  //   Wiki.find_page("foo:bar")
//   void find_page(title, options = {}) {
//    project = options[:project]
//    if ( title.to_s =~ %r{\A([^\:]+)\:(.*)\z}) {
//      project_identifier = $1
//      title = $2
//      project = Project.find_by(identifier: project_identifier) || Project.find_by(name: project_identifier)
//    }
//    if ( project && project.wiki) {
//      page = project.wiki.find_page(title)
//      if ( page && page.content) {
//        page
//      }
//    }
//  }

   void create_menu_item_for_start_page() {
//    wiki_menu_item = wiki_menu_items.find_or_initialize_by(title: start_page) { |item|
//      item.name = "wiki"
//    }
//    wiki_menu_item.new_wiki_page = true
//    wiki_menu_item.index_page = true

//    wiki_menu_item.save!
  }

  private:

  //
  // Locate the redirect from an existing page.
  // Tries to find a redirect for the given slug,
  // falls back to finding a redirect for the title
//   void matching_redirect(title) {
//    page = redirects.where(title: title.to_url).first

//    if ( page.nil?) {
//      page = redirects.where(title: title).first
//    }

//    page
//  }
};
}
}
