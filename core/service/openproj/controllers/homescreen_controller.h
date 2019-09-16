#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class HomescreenController : public ApplicationController {
public:
  // skip_before_action :check_if_login_required, only: [:robots]

  // layout 'no_menu'

   void index() {
//    this->newest_projects = Project.visible.newest.take(3)
//    this->newest_users = User.active.newest.take(3)
//    this->news = News.latest(count: 3)
//    this->announcement = Announcement.active_and_current

//    this->homescreen = OpenProject::Static::Homescreen
  }

   void robots() {
//    this->projects = Project.active.public_projects
  }
};
}
}
