#pragma once
#include "enumeration.h"
namespace openproj {
namespace models {
class IssuePriority : public Enumeration {
  // has_many :work_packages, foreign_key: 'priority_id'
  // belongs_to :color

//  OptionName = :enumeration_work_package_priorities

//   void colored?() {
//    true
//  }

   void color_label() {
//    I18n.t('prioritiies.edit.priority_color_text')
  }

   void option_name() {
//    OptionName
  }

   void objects_count() {
//    work_packages.count
  }

//   void transfer_relations(to) {
//    work_packages.update_all(priority_id: to.id)
//  }
};
}

}