#ifndef OPENPROJ_MODELS_ANNOUNCEMENT_H
#define OPENPROJ_MODELS_ANNOUNCEMENT_H

#include "Announcements.h"
#include "activerecord.h"

namespace openproj {

namespace models {

class Announcement : public openproj::models::ActiveRecord::Base,
                     public drogon_model::openproject6::Announcements {
 public:
  // scope :active,  -> { where(active: true) }
  // scope :current, -> { where("show_until >= ?", Date.today) }
  // validates :show_until, presence: true
  inline void active_and_current(){
      //    active.current.first
  };

  inline void only_one(){
      //    a = first
      //    if ( a.nil?) { a = create_default_announcement ;}
      //    a
  };

  //   void active_and_current?() {
  //    active? && show_until && show_until >= Date.today
  //  }
  inline void create_default_announcement(){
      //    Announcement.create text: "Announcement",
      //                        show_until: Date.today + 14.days,
      //                        active: false
  };
};

}  // namespace models

}  // namespace openproj
#endif
