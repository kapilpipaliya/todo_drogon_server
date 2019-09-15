// Filter for all work packages that are (or are not) required by work packages with the provided values.

namespace openproj {
class Queries::WorkPackages::Filter::RequiredFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
    ::Relation::TYPE_REQUIRED
  }

  private:

   void relation_filter() {
    { to_id: values }
  }

   void relation_select() {
    :from_id
  }
}
