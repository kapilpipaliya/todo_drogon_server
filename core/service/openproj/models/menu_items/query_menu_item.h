#pragma once
#include "../menu_item.h"
namespace openproj {
namespace MenuItems {
class QueryMenuItem : public MenuItem {
  // belongs_to :query, foreign_key: 'navigatable_id'

   void unique_name() {
//    "#{name}-#{id}".to_sym
  }
};
}
}
