#pragma once
#include "enumeration.h"
namespace openproj {
namespace models {
class TimeEntryActivity : public Enumeration {
  // has_many :time_entries, foreign_key: "activity_id"

//  OptionName = :enumeration_activities

   void option_name() {
//    OptionName
  }

   void objects_count() {
//    time_entries.count
  }

//   void transfer_relations(to) {
//    time_entries.update_all("activity_id = #{to.id}")
//  }

   void activated_projects() {
//    scope = Project.all

//    scope = if ( active?) {
//              scope
//                .where.not(id: children.select(:project_id))
//            else
//              scope
//                .where("1=0")
//            }

//    scope.or(Project.where(id: children.where(active: true).select(:project_id)))
  }
};
}

}