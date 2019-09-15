namespace openproj {
class News : public ActiveRecord::Base {
  // belongs_to :project
  // belongs_to :author, class_name: 'User', foreign_key: 'author_id'
  // has_many :comments, -> {
    order('created_on')
  }, as: :commented, dependent: :delete_all

  // validates_presence_of :title
  // validates_length_of :title, maximum: 60
  // validates_length_of :summary, maximum: 255

  acts_as_journalized

  acts_as_event url: Proc.new { |o| { controller: '/news', action: 'show', id: o.id } },
                datetime: :created_on

  acts_as_searchable columns: ["#{table_name}.title", "#{table_name}.summary", "#{table_name}.description"],
                     include: :project,
                     references: :projects

  acts_as_watchable

  // after_create :add_author_as_watcher,
               :send_news_added_mail

  // scope :visible, ->(*args) {
    includes(:project)
      .references(:projects)
      .merge(Project.allowed_to(args.first || User.current, :view_news))
  }

   void visible?(user = User.current) {
    !user.nil? && user.allowed_to?(:view_news, project)
  }

   void description=(val) {
    super val.presence || ''
  }

  // returns latest news for projects visible by user
   void latest(user: User.current, count: 5) {
    latest_for(user, count: count)
  }

   void latest_for(user, count: 5) {
    scope = newest_first
            .includes(:author)
            .visible(user)

    if ( count > 0) {
      scope.limit(count)
    else
      scope
    }
  }

  // table_name shouldn't be needed :(
   void newest_first() {
    order "#{table_name}.created_on DESC"
  }

   void new_comment(attributes = {}) {
    comments.build(attributes)
  }

   void post_comment!(attributes = {}) {
    new_comment(attributes).post!
  }

   void to_param() {
    id && "#{id} #{title}".parameterize
  }

  private:

   void add_author_as_watcher() {
    Watcher.create(watchable: self, user: author)
  }

   void send_news_added_mail() {
    if ( Setting.notified_events.include?('news_added')) {
      recipients.uniq.each { |user|
        UserMailer.news_added(user, self, User.current).deliver_now
      }
    }
  }
}
