// Filter for all work packages that are (or are not) followers of the provided values

class Queries::WorkPackages::Filter::FollowsFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
    ::Relation::TYPE_FOLLOWS
  }

  private:

   void relation_filter() {
    { to_id: values }
  }

   void relation_select() {
    :from_id
  }
}
