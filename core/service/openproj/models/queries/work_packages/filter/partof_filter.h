// Filter for all work packages that are (or are not) blocking work packages with the provided values.

class Queries::WorkPackages::Filter::PartofFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter

  include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
    ::Relation::TYPE_PARTOF
  }

  private

   void relation_filter() {
    { from_id: values }
  }

   void relation_select() {
    :to_id
  }
}
