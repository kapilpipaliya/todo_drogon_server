#pragma once
#include "activerecord.h"
//#include "diff"

namespace openproj {
namespace models {
class WikiPage : public ActiveRecord::Base {
  // belongs_to :wiki, touch: true
  // has_one :project, through: :wiki
  // has_one :content, class_name: 'WikiContent', foreign_key: 'page_id', dependent: :destroy
//  acts_as_attachable delete_permission: :delete_wiki_pages_attachments
//  acts_as_tree dependent: :nullify, order: 'title'

//  // Generate slug of the title
//  acts_as_url :title,
//              url_attribute: :slug,
//              scope: :wiki_id, // Unique slugs per WIKI
//              sync_url: true // Keep slug updated on #rename

//  acts_as_watchable
//  acts_as_event title: Proc.new { |o| "#{Wiki.model_name.human}: #{o.title}" },
//                description: :text,
//                datetime: :created_on,
//                url: Proc.new { |o| { controller: '/wiki', action: 'show', project_id: o.wiki.project, id: o.title } }

//  acts_as_searchable columns: ["#{WikiPage.table_name}.title", "#{WikiContent.table_name}.text"],
//                     include: [{ wiki: :project }, :content],
//                     references: [:wikis, :wiki_contents],
//                     project_key: "#{Wiki.table_name}.project_id"

//  // attr_accessor :redirect_existing_links

//  // validates_presence_of :title
//  // validates_associated :content

//  validate :validate_consistency_of_parent_title
//  validate :validate_non_circular_dependency
//  validate :validate_same_project

//  before_save :update_redirects
//  before_destroy :remove_redirects

//  // eager load information about last updates, without loading text
//  // scope :with_updated_on, -> {
//    select("#{WikiPage.table_name}.*, #{WikiContent.table_name}.updated_on")
//      .joins("LEFT JOIN #{WikiContent.table_name} ON #{WikiContent.table_name}.page_id = #{WikiPage.table_name}.id")
//  }

//  // scope :main_pages, ->(wiki_id) {
//    where(wiki_id: wiki_id, parent_id: nil)
//  }

  // scope :visible, ->(user = User.current) {
//    includes(:project)
//      .references(:project)
//      .merge(Project.allowed_to(user, :view_wiki_pages))
//  }

//  after_destroy :delete_wiki_menu_item

//   void slug() {
//    read_attribute(:slug).presence || title.try(:to_url)
//  }

//   void delete_wiki_menu_item() {
//    // menu_item.destroy if ( menu_item) {
//    // ensure there is a menu item for the wiki
//    if ( MenuItems::WikiMenuItem.main_items(wiki).empty?) { wiki.create_menu_item_for_start_page ;}
//  }

//   void visible?(user = User.current) {
//    !user.nil? && user.allowed_to?(:view_wiki_pages, project)
//  }

//   void title=(value) {
//    if ( this->previous_title.blank?) { this->previous_title = read_attribute(:title) ;}
//    write_attribute(:title, value)
//  }

//   void update_redirects() {
//    // Manage redirects if ( the title has changed) {
//    if ( !this->previous_title.blank? && (this->previous_title != title) && !new_record?) {
//      // Update redirects that point to the old title
//      previous_slug = this->previous_title.to_url
//      wiki.redirects.where(redirects_to: previous_slug).each { |r|
//        r.redirects_to = title
//        r.title == r.redirects_to ? r.destroy : r.save
//      }
//      // Remove redirects for the new title
//      wiki.redirects.where(title: slug).each(&:destroy)
//      // Create a redirect to the new title
//      wiki.redirects << WikiRedirect.new(title: previous_slug, redirects_to: slug) unless redirect_existing_links == '0'

//      // Change title of dependent wiki menu item
//      dependent_item = MenuItems::WikiMenuItem.find_by(navigatable_id: wiki.id, name: previous_slug)
//      if ( dependent_item) {
//        dependent_item.name = slug
//        dependent_item.title = title
//        dependent_item.save!
//      }

//      this->previous_title = nil
//    }
//  }

  // Remove redirects to this page
//   void remove_redirects() {
//    wiki.redirects.where(redirects_to: slug).each(&:destroy)
//  }

//   void content_for_version(version = nil) {
//    if ( version) { journal = content.versions.find_by(version: version.to_i) ;}

//    unless journal.nil? || content.version == journal.version
//      content_version = WikiContent.new journal.data.attributes.except('id', 'journal_id')
//      content_version.updated_on = journal.created_at
//      content_version.journals = content.journals.select { |j| j.version <= version.to_i }

//      content_version
//    else
//      content
//    }
//  }

//   void diff(version_to = nil, version_from = nil) {
//    version_to = version_to ? version_to.to_i : content.version
//    version_from = version_from ? version_from.to_i : version_to - 1
//    version_to, version_from = version_from, version_to unless version_from < version_to

//    content_to = content.versions.find_by(version: version_to)
//    content_from = content.versions.find_by(version: version_from)

//    (content_to && content_from) ? WikiDiff.new(content_to, content_from) : nil
//  }

//   void annotate(version = nil) {
//    version = version ? version.to_i : content.version
//    c = content.versions.find_by(version: version)
//    c ? WikiAnnotate.new(c) : nil
//  }

//   void text() {
//    if ( content) { content.text ;}
//  }

//   void updated_on() {
//    unless this->updated_on
//      if ( time = read_attribute(:updated_on)) {
//        // content updated_on was eager loaded with the page
//        unless time.is_a? Time
//          time = Time.zone.parse(time) rescue nil
//        }
//        this->updated_on = time
//      else
//        this->updated_on = content && content.updated_on
//      }
//    }
//    this->updated_on
//  }

  // Returns true if ( usr is allowed to edit the page, otherwise false) {
//   void editable_by?(usr) {
//    !protected? || usr.allowed_to?(:protect_wiki_pages, wiki.project)
//  }

//   void attachments_deletable?(usr = User.current) {
//    editable_by?(usr) && super(usr)
//  }

//   void parent_title() {
//    this->parent_title || (parent && parent.title)
//  }

//   void parent_title=(t) {
//    this->parent_title = t
//    parent_page = t.blank? ? nil : wiki.find_page(t)
//    this->parent = parent_page
//  }

//   void menu_item() {
//    MenuItems::WikiMenuItem.find_by(name: slug, navigatable_id: wiki_id)
//  }

  // Returns the wiki menu item of nearest ancestor page that has a wiki menu item which is a main item.
//   void nearest_main_item() {
//    return nil unless parent

//    if ( (parent_menu_item = parent.menu_item) && parent_menu_item.is_main_item?) {
//      parent_menu_item
//    else
//      parent.nearest_main_item
//    }
//  }

//   void breadcrumb_title() {
//    if ( item = menu_item) {
//      item.title
//    else
//      title
//    }
//  }

//   void to_param() {
//    slug || title.to_url
//  }

//   void save_with_content() {
//    if ( valid? && content.valid?) {
//      ActiveRecord::Base.transaction {
//        save!
//        content.save!
//      }
//      true
//    }
//  }

//   void only_wiki_page?() {
//    wiki.pages == [self]
//  }

  protected:

   void validate_consistency_of_parent_title() {
//    if ( this->parent_title.present? && parent.nil?) { errors.add(:parent_title, :invalid) ;}
  }

   void validate_non_circular_dependency() {
//    if ( parent && (parent == self || parent.ancestors.include?(self))) { errors.add(:parent_title, :circular_dependency) ;}
  }

   void validate_same_project() {
//    if ( parent && (parent.wiki_id != wiki_id)) { errors.add(:parent_title, :not_same_project) ;}
  }
};
}
}

//namespace openproj {
//namespace models {
//class WikiDiff : public Redmine::Helpers::Diff {
//  attr_reader :content_to, :content_from

//   WikiDiff(content_to, content_from) {
//    this->content_to = content_to
//    this->content_from = content_from
//    super(content_to.data.text, content_from.data.text)
//  }
//};
//}

//namespace openproj {
//namespace models {
//class WikiAnnotate {
//  attr_reader :lines, :content

//   WikiAnnotate(content) {
//    this->content = content
//    current = content
//    current_lines = current.data.text.split(/\r?\n/)
//    this->lines = current_lines.map { |t| [nil, nil, t] }
//    positions = []
//    current_lines.size.times { |i| positions << i }
//    while (current.previous){
//      d = current.previous.data.text.split(/\r?\n/).diff(current.data.text.split(/\r?\n/)).diffs.flatten
//      d.each_slice(3) { |s|
//        sign = s[0]
//        line = s[1]
//        if ( sign == '+' && positions[line] && positions[line] != -1) {
//          if ( this->lines[positions[line]][0].nil?) {
//            this->lines[positions[line]][0] = current.version
//            this->lines[positions[line]][1] = current.data.author
//          }
//        }
//      }
//      d.each_slice(3) { |s|
//        sign = s[0]
//        line = s[1]
//        if ( sign == '-') {
//          positions.insert(line, -1)
//        else
//          positions[line] = nil
//        }
//      }
//      positions.compact!
//      // Stop if ( every line is annotated) {
//      break unless this->lines.detect { |line| line[0].nil? }
//      current = current.previous
//    }
//    this->lines.each { |line| line[0] ||= current.version }
//  }
//};
//}
