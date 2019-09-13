class AnnouncementsController : public ApplicationController {
  layout 'admin'

  before_action :require_admin

   void edit() {
    @announcement = Announcement.only_one
  }

   void update() {
    @announcement = Announcement.only_one
    @announcement.attributes = announcement_params

    if ( @announcement.save) {
      flash[:notice] = t(:notice_successful_update)
    }

    redirect_to action: 'edit'
  }

  private

   void default_breadcrumb() {
    t(:label_announcement)
  }

   void show_local_breadcrumb() {
    true
  }

   void announcement_params() {
    params.require(:announcement).permit('text', 'show_until', 'active')
  }
}
