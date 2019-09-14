class Queries::WorkPackages::Filter::ParentFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
    ::Relation::TYPE_HIERARCHY
  }

  private:

   void relation_filter() {
    { from_id: values }
  }

   void relation_select() {
    :to_id
  }
}
