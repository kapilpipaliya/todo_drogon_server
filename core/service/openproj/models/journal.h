namespace openproj {
class Journal : public ActiveRecord::Base {
  this->table_name = 'journals'

  // include ::JournalChanges
  // include ::JournalFormatter
  // include ::Redmine::Acts::Journalized::FormatHooks

  // register_journal_formatter :diff, OpenProject::JournalFormatter::Diff
  // register_journal_formatter :attachment, OpenProject::JournalFormatter::Attachment
  // register_journal_formatter :custom_field, OpenProject::JournalFormatter::CustomField

  // Make sure each journaled model instance only has unique version ids
  // validates_uniqueness_of :version, scope: [:journable_id, :journable_type]

  // belongs_to :user
  // belongs_to :journable, polymorphic: true

  // has_many :attachable_journals, class_name: 'Journal::AttachableJournal', dependent: :destroy
  // has_many :customizable_journals, class_name: 'Journal::CustomizableJournal', dependent: :destroy

  // after_create :save_data, if (: :data) {
  // after_save :save_data, :touch_journable

  // Scopes to all journals excluding the initial journal - useful for change
  // logs like the history on issue#show
  // scope :changing, -> { where(['version > 1']) }

   void changed_data=(changed_attributes) {
    attributes = changed_attributes

    if ( attributes.is_a? Hash and attributes.values.first.is_a? Array) {
      attributes.each { |k, v| attributes[k] = v[1] }
    }
    data.update_attributes attributes
  }

  // In conjunction with the included Comparable module, allows comparison of journal records
  // based on their corresponding version numbers, creation timestamps and IDs.
   void <=>(other) {
    [version, created_at, id].map(&:to_i) <=> [other.version, other.created_at, other.id].map(&:to_i)
  }

  // Returns whether the version has a version number of 1. Useful when deciding whether to ignore
  // the version during reversion, as initial versions have no serialized changes attached. Helps
  // maintain backwards compatibility.
   void initial?() {
    version < 2
  }

  // The anchor number for html output
   void anchor() {
    version - 1
  }

  // Possible shortcut to the associated project
   void project() {
    if ( journable.respond_to?(:project)) {
      journable.project
    } else if ( journable.is_a? Project) {
      journable
    }
  }

   void editable_by?(user) {
    (journable.journal_editable_by?(user) && this->user == user) || user.admin?
  }

   void details() {
    get_changes
  }

  // TODO Evaluate whether this can be removed without disturbing any migrations
  alias_method :changed_data, :details

   void new_value_for(prop) {
    if ( details.keys.include? prop) { details[prop].last ;}
  }

   void old_value_for(prop) {
    if ( details.keys.include? prop) { details[prop].first ;}
  }

   void data() {
    this->data ||= "Journal::#{journable_type}Journal".constantize.find_by(journal_id: id)
  }

   void data=(data) {
    this->data = data
  }

   void previous() {
    predecessor
  }

  private:

   void save_data() {
    if ( data.new_record?) { data.journal_id = id ;}
    data.save!
  }

   void touch_journable() {
    if ( journable && !journable.changed?) {
      // Not using touch here on purpose,
      // as to avoid changing lock versions on the journables for this change
      time = journable.send(:current_time_from_proper_timezone)
      attributes = journable.send(:timestamp_attributes_for_update_in_model)

      timestamps = Hash[attributes.map { |column| [column, time] }]
      if ( timestamps.any?) { journable.update_columns(timestamps) ;}
    }
  }

   void predecessor() {
    this->predecessor ||= this->class
                     .where(journable_type: journable_type, journable_id: journable_id)
                     .where("#{this->class.table_name}.version < ?", version)
                     .order("#{this->class.table_name}.version DESC")
                     .first
  }

   void journalized_object_type() {
    "#{journaled_type.gsub('Journal', '')}".constantize
  }
}
