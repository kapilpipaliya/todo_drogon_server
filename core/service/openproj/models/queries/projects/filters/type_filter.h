namespace Queries {
  namespace Projects {
    namespace Filters {
      class TypeFilter : public ::Queries::Projects::Filters::ProjectFilter {
         void allowed_values() {
          @allowed_values ||= Type.pluck(:name, :id)
        }

         void joins() {
          :types
        }

         void where() {
          operator_strategy.sql_for_field(values, Type.table_name, :id)
        }

         void type() {
          :list
        }

         void key() {
          :type_id
        }

        private

         void type_strategy() {
          // Instead of getting the IDs of all the projects a user is allowed
          // to see we only check that the value is an integer.  Non valid ids
          // will then simply create an empty result but will not cause any
          // harm.
          @type_strategy ||= ::Queries::Filters::Strategies::IntegerList.new(self)
        }
      }
    }
  }
}
