// Filter for all work packages that are (or are not) predecessor of the provided values

namespace openproj {
class Queries::WorkPackages::Filter::PrecedesFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
    ::Relation::TYPE_PRECEDES
  }

  private:

   void relation_filter() {
    { from_id: values }
  }

   void relation_select() {
    :to_id
  }
}
