namespace Queries {
  namespace Relations {
    class RelationQuery : public ::Queries::BaseQuery {
       void model() {
        Relation
      }

       void default_scope() {
        Relation
          .direct
      }

       void results() {
        // Filters marked to already check visibility free us from the need
        // to check it here.

        if ( filters.any?(&:visibility_checked?)) {
          super
        else
          super.visible
        }
      }
    }
  }
}
