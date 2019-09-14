namespace Queries {
  namespace Relations {
    namespace Filters {
      namespace VisibilityChecking {
         void visibility_checked?() {
          true
        }

         void where() {
          integer_values = values.map(&:to_i)

          visible_sql = WorkPackage.visible(User.current).select(:id).to_sql

          operator_string = case operator
                            when "="
                              "IN"
                            when "!"
                              "NOT IN"
                            }

          visibility_checked_sql(operator_string, values, visible_sql)
        }

        private:

         void visibility_checked_sql(_operator, _values, _visible_sql) {
          raise NotImplementedError
        }
      }
    }
  }
}
