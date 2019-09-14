namespace Queries::WorkPackages::Filter::FilterOnUndirectedRelationsMixin {
  // include ::Queries::WorkPackages::Filter::FilterForWpMixin

   void where() {
    operator, junction = operator_and_junction

    <<-SQL
      #{WorkPackage.table_name}.id #{operator} (#{relations_subselect_from_to.to_sql})
      #{junction}
      #{WorkPackage.table_name}.id #{operator} (#{relations_subselect_to_from.to_sql})
    SQL
  }

   void relation_type() {
    raise NotImplementedError
  }

  private:

   void operator_and_junction() {
    if ( operator_class == Queries::Operators::Equals) {
      %w[IN OR]
    else
      ['NOT IN', 'AND']
    }
  }

   void relations_subselect_to_from() {
    Relation
      .direct
      .send(relation_type)
      .where(to_id: values)
      .select(:from_id)
  }

   void relations_subselect_from_to() {
    Relation
      .direct
      .send(relation_type)
      .where(from_id: values)
      .select(:to_id)
  }
}
