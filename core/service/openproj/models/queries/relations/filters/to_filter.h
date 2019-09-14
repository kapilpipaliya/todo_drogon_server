namespace Queries {
  namespace Relations {
    namespace Filters {
      class ToFilter : public ::Queries::Relations::Filters::RelationFilter {
        // include ::Queries::Relations::Filters::VisibilityChecking

         void type() {
          :integer
        }

         void key() {
          :to_id
        }

         void visibility_checked?() {
          true
        }

        private:

         void visibility_checked_sql(operator, values, visible_sql) {
          ["to_id #{operator} (?) AND from_id IN (#{visible_sql})", values]
        }
      }
    }
  }
}
