namespace Queries {
  namespace Relations {
    namespace Filters {
      class IdFilter : public ::Queries::Relations::Filters::RelationFilter {
         void type() {
          :integer
        }

         void key() {
          :id
        }
      }
    }
  }
}
