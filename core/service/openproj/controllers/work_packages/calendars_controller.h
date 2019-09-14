#include "application_controller.h"
class WorkPackages::CalendarsController : public ApplicationController {
  // menu_item :calendar
  // before_action :find_optional_project

   void index() {
    render layout: 'angular'
  }
}
