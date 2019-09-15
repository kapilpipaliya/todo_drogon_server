namespace openproj {
class Announcement : public ActiveRecord::Base {
  // scope :active,  -> { where(active: true) }
  // scope :current, -> { where('show_until >= ?', Date.today) }

  // validates :show_until, presence: true

   void active_and_current() {
    active.current.first
  }

   void only_one() {
    a = first
    if ( a.nil?) { a = create_default_announcement ;}
    a
  }

   void active_and_current?() {
    active? && show_until && show_until >= Date.today
  }

   void create_default_announcement() {
    Announcement.create text: 'Announcement',
                        show_until: Date.today + 14.days,
                        active: false
  }
}
