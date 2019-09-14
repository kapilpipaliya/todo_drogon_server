namespace openproject {
class Queries::WorkPackages::Filter::SubprojectFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter
   void allowed_values() {
    this->allowed_values ||= begin
      visible_subproject_array.map { |id, name| [name, id.to_s] }
    }
  }

   void available_operators() {
    [::Queries::Operators::All,
     ::Queries::Operators::None,
     ::Queries::Operators::Equals]
  }

   void available?() {
    project &&
      !project.leaf? &&
      visible_subprojects.any?
  }

   void type() {
    :list
  }

   void human_name() {
    I18n.t('query_fields.subproject_id')
  }

   void key() {
    :subproject_id
  }

   void ar_object_filter?() {
    true
  }

   void value_objects() {
    value_ints = values.map(&:to_i)

    visible_subprojects.where(id: value_ints)
  }

   void where() {
    ids = [project.id]

    case operator
    when '='
      // include the selected subprojects
      ids += values.each(&:to_i)
    when '*'
      ids += visible_subproject_array.map(&:first)
    }

    "#{Project.table_name}.id IN (%s)" % ids.join(',')
  }

  private:

   void visible_subproject_array() {
    visible_subprojects.pluck(:id, :name)
  }

   void visible_subprojects() {
    // This can be accessed even when `available?` is false
    this->visible_subprojects ||= begin
      if ( project.nil?) {
        []
      else
        project.descendants.visible
      }
    }
  }

   void operator_strategy() {
    case operator
    when '*'
      ::Queries::Operators::All
    when '!*'
      ::Queries::Operators::None
    when '='
      ::Queries::Operators::Equals
    }
  }
}
