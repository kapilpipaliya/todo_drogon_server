#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class AnnouncementsController : public ApplicationController {
public:
  // layout 'admin'

  // before_action :require_admin

   void edit() {
//    this->announcement = Announcement.only_one
  }

   void update() {
//    this->announcement = Announcement.only_one
//    this->announcement.attributes = announcement_params

//    if ( this->announcement.save) {
//      flash[:notice] = t(:notice_successful_update)
//    }

//    redirect_to action: 'edit'
  }

  private:

   void default_breadcrumb() {
//    t(:label_announcement)
  }

   bool show_local_breadcrumb() {
    return true;
  }

   void announcement_params() {
//    params.require(:announcement).permit('text', 'show_until', 'active')
  }
};
}
}
