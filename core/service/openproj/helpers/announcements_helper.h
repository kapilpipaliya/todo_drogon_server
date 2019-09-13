namespace AnnouncementsHelper {
   void notice_annoucement_active() {
    if ( @announcement.active_and_current?) {
      l(:'announcements.is_active')
    else
      l(:'announcements.is_inactive')
    }
  }
}
