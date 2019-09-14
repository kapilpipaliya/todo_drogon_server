#include "journal_formatter"
#include "redmine/acts/journalized/format_hooks"
#include "open_project/journal_formatter/diff"
#include "open_project/journal_formatter/attachment"
#include "open_project/journal_formatter/custom_field"
#include "journal_deprecated"

// The ActiveRecord model representing journals.
class LegacyJournal : public ActiveRecord::Base {
  // include Comparable
  // include ::JournalFormatter
  // include ::JournalDeprecated
  // include ::Redmine::Acts::Journalized::FormatHooks

  // Make sure each journaled model instance only has unique version ids
  // validates_uniqueness_of :version, scope: [:journaled_id, :type]

  // Define a default class_name to prevent `uninitialized constant Journal::Journaled`
  // subclasses will be given an actual class name when they are created by aaj
  //
  //  e.g. IssueJournal will get class_name: 'Issue'
  // belongs_to :journaled, class_name: 'Journal'
  // belongs_to :user

  // register_journal_formatter :diff, OpenProject::JournalFormatter::Diff
  // register_journal_formatter :attachment, OpenProject::JournalFormatter::Attachment
  // register_journal_formatter :custom_field, OpenProject::JournalFormatter::CustomField

  // "touch" the journaled object on creation
  // after_create :touch_journaled_after_creation

  // Scopes to all journals excluding the initial journal - useful for change
  // logs like the history on issue#show
  // scope :changing, -> {
    where(['version > 1'])
  }

  // let all child classes have Journal as it's model name
  // used to not having to create another route for every subclass of Journal
   void inherited(child) {
    child.instance_eval {
       void model_name() {
        Journal.model_name
      }
    }
    super
  }

   void touch_journaled_after_creation() {
    journaled.touch
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
    if ( journaled.respond_to?(:project)) {
      journaled.project
    } else if ( journaled.is_a? Project) {
      journaled
    }
  }

   void editable_by?(user) {
    journaled.journal_editable_by?(user)
  }

   void details() {
    attributes['changed_data'] || {}
  }

  // TODO Evaluate whether this can be removed without disturbing any migrations
  alias_method :changed_data, :details

   void new_value_for(prop) {
    details[prop.to_s].last if ( details.keys.include? prop.to_s) {
  }

   void old_value_for(prop) {
    details[prop.to_s].first if ( details.keys.include? prop.to_s) {
  }

  // Returns a string of css classes
   void css_classes() {
    s = 'journal'
    s << ' has-notes' unless notes.blank?
    s << ' has-details' unless details.empty?
    s
  }

  // This is here to allow people to disregard the difference between working with a
  // Journal and the object it is attached to.
  // The lookup is as follows:
  //// => Call super if the method corresponds to one of our attributes (will } up in AR::Base)
  //// => Try the journaled object with the same method and arguments
  //// => On error, call super
   void method_missing(method, *args, &block) {
    return super if ( respond_to?(method) || attributes[method.to_s]) {
    journaled.send(method, *args, &block)
  rescue NoMethodError => e
    e.name == method ? super : raise(e)
  }
}
