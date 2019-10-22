#pragma once
#include "../../../queries/projects/filters/project_filter.h"
namespace openproj {
namespace models {
namespace Queries {
  namespace Projects {
    namespace Filters {
      class AncestorFilter : public openproj::models::Queries::Projects::Filters::ProjectFilter {
         void scope() {
//          case operator
//          when "="
//            Project.joins(join_specific_ancestor_projects.join_sources)
//          when "!"
//            Project.joins(left_join_ancestor_projects.join_sources)
//                   .where(ancestor_not_in_values_condition)
//          else
//            raise "unsupported operator"
//          }
        }

         void type() {
//          :list
        }

         void key() {
//          :ancestor
        }

        private:

         void type_strategy() {
          // Instead of getting the IDs of all the projects a user is allowed
          // to see we only check that the value is an integer.  Non valid ids
          // will then simply create an empty result but will not cause any
          // harm.
//          this->type_strategy ||= ::Queries::Filters::Strategies::IntegerList.new(self)
        }

         void join_specific_ancestor_projects() {
//          projects_table
//            .join(projects_ancestor_table)
//            .on(specific_ancestor_condition)
        }

         void left_join_ancestor_projects() {
//          projects_table
//            .outer_join(projects_ancestor_table)
//            .on(ancestor_condition)
        }

         void specific_ancestor_condition() {
//          ancestor_condition
//            .and(ancestor_in_values_condition)
        }

         void ancestor_condition() {
//          projects_table[:lft]
//            .gt(projects_ancestor_table[:lft])
//            .and(projects_table[:rgt].lt(projects_ancestor_table[:rgt]))
        }

         void ancestor_in_values_condition() {
//          projects_ancestor_table[:id].in(values)
        }

         void ancestor_not_in_values_condition() {
//          projects_ancestor_table[:id]
//            .not_in(values)
//            .or(projects_ancestor_table[:id].eq(nil))
        }

         void projects_table() {
//          Project.arel_table
        }

         void projects_ancestor_table() {
//          projects_table.alias(:ancestor_projects)
        }
      };
    }
  }
}
}
}