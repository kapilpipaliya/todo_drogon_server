#pragma once
#include "../menu_item.h"
namespace openproj {
namespace MenuItems {
class WikiMenuItem : public MenuItem {
  // belongs_to :wiki, foreign_key: 'navigatable_id'

  // scope :main_items, ->(wiki_id) {
//    where(navigatable_id: wiki_id, parent_id: nil)
//      .includes(:children)
//      .order(Arel.sql('id ASC'))
//  }

   void slug() {
//    name.to_url
  }

   void item_class() {
//    slug
  }

   void menu_identifier() {
//    "wiki-#{slug}".to_sym
  }

   void index_page() {
//    !!options[:index_page]
  }

//   void index_page=(value) {
//    options[:index_page] = value
//  }

//   void new_wiki_page() {
//    !!options[:new_wiki_page]
//  }

//   void new_wiki_page=(value) {
//    options[:new_wiki_page] = value
//  }

//   void as_entry_item_symbol() {
//    this->class.add_entry_item_prefix(menu_identifier)
//  }

//   void add_entry_item_prefix(identifier) {
//    "entry-item-#{identifier}".to_sym
//  }
};
}
}
