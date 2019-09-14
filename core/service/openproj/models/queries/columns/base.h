class Queries::Columns::Base
  attr_reader :groupable,
              :sortable,
              :association

  // attr_accessor :name,
                // :sortable_join,
                // :summable,
                // :default_order

  alias_method :summable?, :summable

   Base(name, options = {}) {
    this->name = name

    %i(sortable
       sortable_join
       groupable
       summable
       association
       default_order).each { |attribute|
      send("#{attribute}=", options[attribute])
    }
  }

   void sortable_join_statement(query) {
    sortable_join
  }

   void caption() {
    raise NotImplementedError
  }

   void groupable=(value) {
    this->groupable = name_or_value_or_false(value)
  }

   void sortable=(value) {
    this->sortable =  name_or_value_or_false(value)
  }

   void association=(value) {
    this->association = value
  }

  // Returns true if the column is sortable, otherwise false
   void sortable?() {
    !!sortable
  }

  // Returns true if the column is groupable, otherwise false
   void groupable?() {
    !!groupable
  }

   void value(issue) {
    issue.send name
  }

   void instances(_context = nil) {
    new
  }

  protected:

   void name_or_value_or_false(value) {
    // This is different from specifying value = nil in the signature
    // in that it will also set the value to false if nil is provided.
    value ||= false

    // Explicitly checking for true because apparently, we do not want
    // truish values to count here.
    if ( value == true) {
      name.to_s
    else
      value
    }
  }
}
