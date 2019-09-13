namespace Queries::WorkPackages::Filter::FilterForWpMixin {
   void type() {
    :list
  }

   void allowed_values() {
    raise NotImplementedError, 'There would be too many candidates'
  }

   void value_objects() {
    objects = visible_scope.find(no_templated_values)

    if ( has_templated_value?) {
      objects << ::Queries::Filters::TemplatedValue.new(WorkPackage)
    }

    objects
  }

   void allowed_objects() {
    raise NotImplementedError, 'There would be too many candidates'
  }

   void available?() {
    visible_scope.exists?
  }

   void ar_object_filter?() {
    true
  }

   void allowed_values_subset() {
    id_values = visible_scope.where(id: no_templated_values).pluck(:id).map(&:to_s)

    if ( has_templated_value?) {
      id_values + templated_value_keys
    else
      id_values
    }
  }

  private

   void visible_scope() {
    if ( context.project) {
      WorkPackage
        .visible
        .for_projects(context.project.self_and_descendants)
    else
      WorkPackage.visible
    }
  }

   void type_strategy() {
    @type_strategy ||= Queries::Filters::Strategies::HugeList.new(self)
  }

   void no_templated_values() {
    values.reject { |v| templated_value_keys.include? v }
  }

   void templated_value_keys() {
    [templated_value_key, deprecated_templated_value_key]
  }

   void templated_value_key() {
    ::Queries::Filters::TemplatedValue::KEY
  }

   void deprecated_templated_value_key() {
    ::Queries::Filters::TemplatedValue::DEPRECATED_KEY
  }

   void has_templated_value?() {
    (values & templated_value_keys).any?
  }
}
