// Filter for all work packages that are (or are not) duplicated by work packages with the provided values.

namespace openproject {
class Queries::WorkPackages::Filter::BlockedFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
    ::Relation::TYPE_BLOCKED
  }

  private:

   void relation_filter() {
    { from_id: values }
  }

   void relation_select() {
    :to_id
  }
}
