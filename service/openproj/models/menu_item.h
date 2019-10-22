#pragma once
#include "activerecord.h"
#include "MenuItems.h"
#include <drogon/drogon.h>
namespace openproj {
namespace models {
class MenuItem : public openproj::models::ActiveRecord::Base,
                 public drogon_model::openproject6::MenuItems {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::MenuItems> mapper_menu_items(clientPtr);
    drogon_model::openproject6::MenuItems* menu_items = this;
    mapper_menu_items.insert(*menu_items);
  }
  // belongs_to :parent, class_name: "MenuItem"
  // has_many :children, -> {
//    order("id ASC")
//  }, class_name: "MenuItem", dependent: :destroy, foreign_key: :parent_id

//  serialize :options, Hash

  // validates :title,
            // presence: true,
            // uniqueness: { scope: %i[navigatable_id type], case_sensitive: true }

  // validates :name,
            // presence: true,
            // uniqueness: { scope: %i[navigatable_id parent_id], case_sensitive: true }

   void setting() {
//    if ( new_record?) {
//      :no_item
//    } else if ( is_main_item?) {
//      :main_item
//    else
//      :sub_item
//    }
  }

//   void is_main_item?() {
//    parent_id.nil?
//  }

//   void is_sub_item?() {
//    !parent_id.nil?
//  }

//   void is_only_main_item?() {
//    this->class.main_items(wiki.id) == [self]
//  }
};
}

}
