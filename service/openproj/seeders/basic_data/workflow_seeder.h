#pragma once
#include "../seeder.h"
#include <drogon/drogon.h>
#include "models/Colors.h"
#include "models/Roles.h"
#include "models/Workflows.h"
namespace openproj {
namespace seeder {
namespace BasicData {
  class WorkflowSeeder : public Seeder {
  public:
      struct row {
       int type_id;
        std::vector<int> status_ids;
      };
      std::vector<row> data_;

     void seed_data() {

//       auto clientPtr = drogon::app().getDbClient("sce");
//       drogon::orm::Mapper<drogon_model::openproject6::Colors> mapper(clientPtr);
//       auto colors = mapper.findAll();

//      colors = Color.all
//      colors = colors.map { |c| { c.name => c.id } }.reduce({}, :merge)

//      if ( WorkPackage.where(type_id: nil).any? || JournalN::WorkPackageJournal.where(type_id: nil).any?) {
//        // Fixes work packages that do not have a type yet. They receive the standard type.
//        //
//        // This can happen when an existing database, having timelines planning elements,
//        // gets migrated. During the migration, the existing planning elements are converted
//        // to work_packages. Because the existance of a standard type cannot be guaranteed
//        // during the migration, such work packages receive a type_id of nil.
//        //
//        // Because all work packages that do not have a type yet should always have had one
//        // (from todays standpoint). The assignment is done covertedly.

//        WorkPackage.transaction {
//          green_color = colors[I18n.t(:default_color_green_light)]
//          standard_type = Type.find_or_create_by(is_standard: true,
//                                                 name: "none",
//                                                 position: 0,
//                                                 color_id: green_color,
//                                                 is_default: true,
//                                                 is_in_roadmap: true,
//                                                 is_milestone: false)

//          [WorkPackage, JournalN::WorkPackageJournal].each { |klass|
//            klass.where(type_id: nil).update_all(type_id: standard_type.id)
//          }
//        }
//      }

//      if ( Type.where(is_standard: false).any? || Status.any? || Workflow.any?) {
//        puts "   *** Skipping types, statuses and workflows as there are already some configured"
//      } else if ( Role.where(name: I18n.t(:default_role_member)).empty? ||) {
//            Role.where(name: I18n.t(:default_role_project_admin)).empty?

//        puts "   *** Skipping types, statuses and workflows as the required roles do not exist"
//      else
//        member = Role.where(name: I18n.t(:default_role_member)).first
//        manager = Role.where(name: I18n.t(:default_role_project_admin)).first

//        puts "   ↳ Types"
//        type_seeder_class.new.seed!

//        puts "   ↳ Statuses"
//        status_seeder_class.new.seed!

//        // Workflow - Each type has its own workflow
//        workflows.each { |type_id, statuses_for_type|
//          statuses_for_type.each { |old_status|
//            statuses_for_type.each { |new_status|
//              [manager.id, member.id].each { |role_id|
//                Workflow.create type_id: type_id,
//                                role_id: role_id,
//                                old_status_id: old_status.id,
//                                new_status_id: new_status.id
//              }
//            }
//          }
//        }
//      }
       // as above function some part is not written as its not needed
       type_seed();
       status_seed();
       auto clientPtr = drogon::app().getDbClient("sce");
       drogon::orm::Mapper<drogon_model::openproject6::Roles> mapper(clientPtr);
       auto member = mapper.findBy(
           Criteria(drogon_model::openproject6::Roles::Cols::_name,
                    CompareOperator::EQ, "Member"));
       auto manager = mapper.findBy(
             Criteria(drogon_model::openproject6::Roles::Cols::_name,
                      CompareOperator::EQ, "Project admin"));

       auto d = workflows();
       for (auto it : d) {
           for (auto oldst : it.status_ids) {
               for (auto newst : it.status_ids) {
                   drogon::orm::Mapper<drogon_model::openproject6::Workflows> mapper_workflow(clientPtr);
                   drogon_model::openproject6::Workflows workflow;
                   workflow.setTypeId(it.type_id);
                   workflow.setRoleId(*manager.at(0).getId().get());
                   workflow.setOldStatusId(oldst);
                   workflow.setNewStatusId(newst);
                   workflow.setAssignee(false); // this is defaut value;
                   workflow.setAuthor(false); // this is default value;
                   mapper_workflow.insert(workflow);

                   drogon_model::openproject6::Workflows workflow2;
                   workflow2.setTypeId(it.type_id);
                   workflow2.setRoleId(*member.at(0).getId().get());
                   workflow2.setOldStatusId(oldst);
                   workflow2.setNewStatusId(newst);
                   workflow2.setAssignee(false); // this is defaut value;
                   workflow2.setAuthor(false); // this is default value;
                   mapper_workflow.insert(workflow2);

               }
           }
       }

    }

     virtual  std::vector<row> workflows()  = 0;

//     virtual void type_seeder_class()  = 0;

//     virtual void status_seeder_class()  = 0;

     virtual void type_seed() = 0;
     virtual void status_seed() = 0;
  };
}
}
}
