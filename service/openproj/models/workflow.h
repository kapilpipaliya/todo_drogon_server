#ifndef OPENPROJ_MODELS_WORKFLOW_H
#define OPENPROJ_MODELS_WORKFLOW_H

#include "Workflows.h"
#include "activerecord.h"

namespace openproj {

namespace models {

class Workflow : public openproj::models::ActiveRecord::Base,
                 public drogon_model::openproject6::Workflows {
 public:
  // belongs_to :role
  // belongs_to :old_status, class_name: "Status", foreign_key: "old_status_id"
  // belongs_to :new_status, class_name: "Status", foreign_key: "new_status_id"
  // belongs_to :type, inverse_of: "workflows"
  // validates_presence_of :role, :old_status, :new_status
  // Returns workflow transitions count by type and role
  inline void count_by_type_and_role(){
      //    counts = connection
      //             .select_all("SELECT role_id, type_id, count(id) AS c FROM
      //             #{Workflow.table_name} GROUP BY role_id, type_id")
      //    roles = Role.order(Arel.sql("builtin, position"))
      //    types = ::Type.order(Arel.sql("position"))

      //    result = []
      //    types.each { |type|
      //      t = []
      //      roles.each { |role|
      //        row = counts.detect { |c| c["role_id"].to_s == role.id.to_s &&
      //        c["type_id"].to_s == type.id.to_s }
      //        t << [role, (row.nil? ? 0 : row["c"].to_i)]
      //      }
      //      result << [type, t]
      //    }

      //    result
  };
};

}  // namespace models

}  // namespace openproj
#endif
