// Filter for all work packages that are (or are not) predecessor of the provided values

class Queries::WorkPackages::Filter::RelatesFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter
  include ::Queries::WorkPackages::Filter::FilterOnUndirectedRelationsMixin

   void relation_type() {
    ::Relation::TYPE_RELATES
  }
}
