namespace Queries {
  namespace Relations {
    namespace Filters {
      class FromFilter : public ::Queries::Relations::Filters::RelationFilter {
        // include ::Queries::Relations::Filters::VisibilityChecking

         void type() {
          :integer
        }

         void key() {
          :from_id
        }

        private:

         void visibility_checked_sql(operator, values, visible_sql) {
          ["from_id #{operator} (?) AND to_id IN (#{visible_sql})", values]
        }
      }
    }
  }
}
