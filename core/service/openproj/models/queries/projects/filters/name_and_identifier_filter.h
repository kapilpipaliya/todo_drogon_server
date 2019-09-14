class Queries::Projects::Filters::NameAndIdentifierFilter : public Queries::Projects::Filters::ProjectFilter {
   void type() {
    :string
  }

   void where() {
    case operator
    when '='
      where_equal
    when '!'
      where_not_equal
    when '~'
      where_contains
    when '!~'
      where_not_contains
    }
  }

   void human_name() {
    I18n.t('query_fields.name_or_identifier')
  }

   void key() {
    :name_and_identifier
  }

  private:

   void concatenate_with_values(condition, concatenation) {
    conditions = []
    assignments = []
    values.each { |value|
      conditions << condition
      assignments += [yield(value), yield(value)]
    }

    [conditions.join(" #{concatenation} "), *assignments]
  }

   void where_equal() {
    concatenate_with_values('LOWER(projects.identifier) = ? OR LOWER(projects.name) = ?', 'OR', &:downcase)
  }

   void where_not_equal() {
    where_not(where_equal)
  }

   void where_contains() {
    concatenate_with_values('LOWER(projects.identifier) LIKE ? OR LOWER(projects.name) LIKE ?', 'OR') { |value|
      "%#{value.downcase}%"
    }
  }

   void where_not_contains() {
    where_not(where_contains)
  }

   void where_not(condition) {
    conditions = condition
    conditions[0] = "NOT(#{conditions[0]})"
    conditions
  }
}
