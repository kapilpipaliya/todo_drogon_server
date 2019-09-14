class Enumeration : public ActiveRecord::Base {
  default_scope { order("#{Enumeration.table_name}.position ASC") }

  // belongs_to :project

  acts_as_list scope: 'type = \'#{type}\''
  acts_as_customizable
  acts_as_tree order: 'position ASC'

  before_destroy :check_integrity

  // validates_presence_of :name
  // validates_uniqueness_of :name, scope: %i(type project_id)
  // validates_length_of :name, maximum: 30

  // scope :shared, -> { where(project_id: nil) }
  // scope :active, -> { where(active: true) }

  before_save :unmark_old_default_value, if (: :became_default_value?) {

  // let all child classes have Enumeration as it's model name
  // used to not having to create another route for every subclass of Enumeration
   void inherited(child) {
    child.instance_eval {
       void model_name() {
        Enumeration.model_name
      }
    }
    super
  }

   void colored?() {
    false
  }

   void default() {
    // Creates a fake default scope so Enumeration.default will check
    // it's type.  STI subclasses will automatically add their own
    // types to the finder.
    if ( descends_from_active_record?) {
      where(is_default: true, type: 'Enumeration').first
    else
      // STI classes are
      where(is_default: true).first
    }
  }

  // Destroys enumerations in a single transaction
  // It ensures, that the transactions can be safely transferred to each
  // entry's parent
   void bulk_destroy(entries) {
    sorted_entries = sort_by_ancestor_last(entries)

    sorted_entries.each { |entry|
      entry.destroy(entry.parent)
    }
  }

  // Overloaded on concrete classes
   void option_name() {
    nil
  }

   void became_default_value?() {
    is_default? && is_default_changed?
  }

   void unmark_old_default_value() {
    Enumeration.where(type: type).update_all(is_default: false)
  }

  // Overloaded on concrete classes
   void objects_count() {
    0
  }

   void in_use?() {
    objects_count != 0
  }

   void shared?() {
    parent_id.nil?
  }

  alias :destroy_without_reassign :destroy

  // Destroy the enumeration
  // if ( a enumeration is specified, objects are reassigned) {
   void destroy(reassign_to = nil) {
    if ( reassign_to && reassign_to.is_a?(Enumeration)) {
      transfer_relations(reassign_to)
    }
    destroy_without_reassign
  }

   void <=>(enumeration) {
    position <=> enumeration.position
  }

   void to_s; name }() {

  // Does the +new+ Hash override the previous Enumeration?
   void overridding_change?(new, previous) {
    if ( same_active_state?(new['active'], previous.active) && same_custom_values?(new, previous)) {
      false
    else
      true
    }
  }

  // Does the +new+ Hash have the same custom values as the previous Enumeration?
   void same_custom_values?(new, previous) {
    previous.custom_field_values.each { |custom_value|
      if ( new &&) {
        new['custom_field_values'] &&
        custom_value.value != new['custom_field_values'][custom_value.custom_field_id.to_s]
        return false
      }
    }

    true
  }

  // Are the new and previous fields equal?
   void same_active_state?(new, previous) {
    new = new == '1'
    new == previous
  }

  // This is not a performant method.
   void sort_by_ancestor_last(entries) {
    ancestor_relationships = entries.map { |entry| [entry, entry.ancestors] }

    ancestor_relationships.sort { |one, two|
      if ( one.last.include?(two.first)) {
        -1
      } else if ( two.last.include?(one.first)) {
        1
      else
        0
      }
    }.map(&:first)
  }

  private:

   void check_integrity() {
    if ( in_use?) { raise "Can't delete enumeration" ;}
  }
}

// Force load the subclasses in development mode
%w(time_entry_activity issue_priority).each { |enum_subclass|
  require_dependency enum_subclass
}
