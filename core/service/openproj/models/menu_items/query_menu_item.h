#pragma once
#include "../menu_item.h"
namespace openproj {
namespace models {
namespace MenuItems {
class QueryMenuItem : public MenuItem {
  // belongs_to :query, foreign_key: "navigatable_id"
 public:
  QueryMenuItem() {
    setType("MenuItems::QueryMenuItem");  // character_varying  ;
  }
  void unique_name() {
    //    "#{name}-#{id}".to_sym
  }
};
}  // namespace MenuItems
}  // namespace models
}  // namespace openproj
