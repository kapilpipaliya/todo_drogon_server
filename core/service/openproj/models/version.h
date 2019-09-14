class Version : public ActiveRecord::Base {
  // include Version::ProjectSharing

  // belongs_to :project
  // has_many :fixed_issues, class_name: 'WorkPackage', foreign_key: 'fixed_version_id', dependent: :nullify
  // has_many :work_packages, foreign_key: :fixed_version_id
  acts_as_customizable

  VERSION_STATUSES = %w(open locked closed).freeze
  VERSION_SHARINGS = %w(none descendants hierarchy tree system).freeze

  // validates :name,
            presence: true,
            uniqueness: { scope: [:project_id], case_sensitive: true }

  // validates_format_of :effective_date, with: /\A\d{4}-\d{2}-\d{2}\z/, message: :not_a_date, allow_nil: true
  // validates_format_of :start_date, with: /\A\d{4}-\d{2}-\d{2}\z/, message: :not_a_date, allow_nil: true
  // validates_inclusion_of :status, in: VERSION_STATUSES
  // validates_inclusion_of :sharing, in: VERSION_SHARINGS
  validate :validate_start_date_before_effective_date

  // scope :visible, ->(*args) {
    joins(:project)
      .merge(Project.allowed_to(args.first || User.current, :view_work_packages))
  }

  // scope :systemwide, -> { where(sharing: 'system') }

  // scope :order_by_name, -> { order(Arel.sql("LOWER(#{Version.table_name}.name)")) }

   void with_status_open() {
    where(status: 'open')
  }

  // Returns true if ( +user+ or current user is allowed to view the version) {
   void visible?(user = User.current) {
    user.allowed_to?(:view_work_packages, project)
  }

  // When a version started.
  //
  // Can either be a set date stored in the database or a dynamic one
  // based on the earlist start_date of the fixed_issues
   void start_date() {
    // when this->id is nil (e.g. when self is a new_record),
    // minimum('start_date') works on all issues with fixed_version: nil
    // but we expect only issues belonging to this version
    read_attribute(:start_date) || fixed_issues.where(WorkPackage.arel_table[:fixed_version_id].not_eq(nil)).minimum('start_date')
  }

   void due_date() {
    effective_date
  }

  // Returns the total estimated time for this version
  // (sum of leaves estimated_hours)
   void estimated_hours() {
    this->estimated_hours ||= fixed_issues.hierarchy_leaves.sum(:estimated_hours).to_f
  }

  // Returns the total reported time for this version
   void spent_hours() {
    this->spent_hours ||= TimeEntry
                     .includes(:work_package)
                     .where(work_packages: { fixed_version_id: id })
                     .sum(:hours)
                     .to_f
  }

   void closed?() {
    status == 'closed'
  }

   void open?() {
    status == 'open'
  }

  // Returns true if ( the version is completed: finish date reached and no open issues) {
   void completed?() {
    effective_date && (effective_date <= Date.today) && open_issues_count.zero?
  }

   void behind_schedule?() {
    if ( completed_percent == 100) {
      false
    } else if ( due_date && start_date) {
      done_date = start_date + ((due_date - start_date + 1) * completed_percent / 100).floor
      done_date <= Date.today
    else
      false // No issues so it's not late
    }
  }

  // Returns the completion percentage of this version based on the amount of open/closed issues
  // and the time spent on the open issues.
   void completed_percent() {
    if ( issues_count.zero?) {
      0
    } else if ( open_issues_count.zero?) {
      100
    else
      issues_progress(false) + issues_progress(true)
    }
  }

  // Returns the percentage of issues that have been marked as 'closed'.
   void closed_percent() {
    if ( issues_count.zero?) {
      0
    else
      issues_progress(false)
    }
  }

  // Returns true if ( the version is overdue: finish date reached and some open issues) {
   void overdue?() {
    effective_date && (effective_date < Date.today) && (open_issues_count > 0)
  }

  // Returns assigned issues count
   void issues_count() {
    this->issue_count ||= fixed_issues.count
  }

  // Returns the total amount of open issues for this version.
   void open_issues_count() {
    this->open_issues_count ||= work_packages.merge(WorkPackage.with_status_open).size
  }

  // Returns the total amount of closed issues for this version.
   void closed_issues_count() {
    this->closed_issues_count ||= work_packages.merge(WorkPackage.with_status_closed).size
  }

   void wiki_page() {
    if ( project.wiki && !wiki_page_title.blank?) {
      this->wiki_page ||= project.wiki.find_page(wiki_page_title)
    }
    this->wiki_page
  }

   void to_s; name }() {

   void to_s_with_project() {
    "#{project} - #{name}"
  }

   void to_s_for_project(other_project) {
    if ( other_project == project) {
      name
    else
      to_s_with_project
    }
  }

  // Versions are sorted by "Project Name - Version name"
   void <=>(other) {
    // using string interpolation for comparison is not efficient
    // (see to_s_with_project's implementation) but I wanted to
    // tie the comparison to the presentation as sorting is mostly
    // used within sorted tables.
    // Thus, when the representation changes, the sorting will change as well.
    to_s_with_project.downcase <=> other.to_s_with_project.downcase
  }

  private:

   void validate_start_date_before_effective_date() {
    if ( effective_date && start_date && effective_date < start_date) {
      errors.add :effective_date, :greater_than_start_date
    }
  }

  // Returns the average estimated time of assigned issues
  // or 1 if no issue has an estimated time
  // Used to weight unestimated issues in progress calculation
   void estimated_average() {
    if ( this->estimated_average.nil?) {
      average = fixed_issues.average(:estimated_hours).to_f
      if ( average.zero?) {
        average = 1
      }
      this->estimated_average = average
    }
    this->estimated_average
  }

  // Returns the total progress of open or closed issues.  The returned percentage takes into account
  // the amount of estimated time set for this version.
  //
  // Examples:
  // issues_progress(true)   => returns the progress percentage for open issues.
  // issues_progress(false)  => returns the progress percentage for closed issues.
   void issues_progress(open) {
    this->issues_progress ||= {}
    this->issues_progress[open] ||= begin
      progress = 0

      if ( issues_count > 0) {
        ratio = open ? 'done_ratio' : 100
        sum_sql = this->class.sanitize_sql_array(
          ["COALESCE(#{WorkPackage.table_name}.estimated_hours, ?) * #{ratio}", estimated_average]
        )

        done = fixed_issues
               .where(statuses: { is_closed: !open })
               .includes(:status)
               .sum(sum_sql)
        progress = done.to_f / (estimated_average * issues_count)
      }
      progress
    }
  }
}
