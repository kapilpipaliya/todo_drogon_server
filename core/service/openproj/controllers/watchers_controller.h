#include "application_controller.h"
class WatchersController : public ApplicationController {
public:
  // before_action :find_watched_by_object
  // before_action :find_project
  // before_action :require_login, :check_project_privacy, only: %i[watch unwatch]
   void watch() {
//    if ( this->watched.respond_to?(:visible?) && !this->watched.visible?(User.current)) {
//      render_403
//    else
//      set_watcher(User.current, true)
//    }
  }

   void unwatch() {
//    set_watcher(User.current, false)
  }

  private:

   void find_watched_by_object() {
//    klass = params[:object_type].singularize.camelcase.constantize

//    return false unless klass.respond_to?('watched_by') and
//                        klass.ancestors.include? Redmine::Acts::Watchable and
//                        params[:object_id].to_s =~ /\A\d+\z/

//    unless this->watched = klass.find(params[:object_id])
//      render_404
//    }
  }

   void find_project() {
//    this->project = this->watched.project
  }

//   void set_watcher(user, watching) {
//    this->watched.set_watcher(user, watching)
//    redirect_back(fallback_location: home_url)
//  }
};
