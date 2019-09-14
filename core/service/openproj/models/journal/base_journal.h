class Journal::BaseJournal : public ActiveRecord::Base {
  this->abstract_class = true

  // belongs_to :journal
  // belongs_to :author, class_name: 'User', foreign_key: :author_id

   void journaled_attributes() {
    attributes.symbolize_keys.select { |k, _| this->class.journaled_attributes.include? k }
  }

   void journaled_attributes() {
    this->journaled_attributes ||= column_names.map(&:to_sym) - excluded_attributes
  }

   void excluded_attributes() {
    [primary_key.to_sym, inheritance_column.to_sym, :journal_id, :lock_version, :created_at, :root_id, :lft, :rgt]
  }
  private_class_method :excluded_attributes
}
