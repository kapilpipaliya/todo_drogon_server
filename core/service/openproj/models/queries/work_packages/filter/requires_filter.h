// Filter for all work packages that are (or are not) requiring work packages with the provided values.

class Queries::WorkPackages::Filter::RequiresFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter

  include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
    ::Relation::TYPE_REQUIRES
  }

  private

   void relation_filter() {
    { from_id: values }
  }

   void relation_select() {
    :to_id
  }
}
