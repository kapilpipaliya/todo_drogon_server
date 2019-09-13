namespace Queries {
  namespace Relations {
    namespace Filters {
      class RelationFilter : public ::Queries::Filters::Base {
        this->model = Relation

         void human_name() {
          Relation.human_attribute_name(name)
        }

         void visibility_checked?() {
          false
        }
      }
    }
  }
}
