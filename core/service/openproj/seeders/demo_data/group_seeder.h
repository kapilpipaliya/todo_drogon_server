#pragma once
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace DemoData {
class GroupSeeder : public Seeder {
 public:
  // attr_accessor :user
  // include ::DemoData::References

  GroupSeeder() {
    //      this->user = User.admin.first
  }

  void seed_data() {
    //      LOG_DEBUG << "    ↳ Creating groups"

    seed_groups();

    //      puts
  }

  void add_projects_to_groups() {
    // because demo_data_for("groups") = nil
    return;
    //      groups = demo_data_for("groups")
    //      if ( groups.present?) {
    //        groups.each { |group_attr|
    //          if ( group_attr[:projects].present?) {
    //            group = Group.find_by(lastname: group_attr[:name])
    //            group_attr[:projects].each { |project_attr|
    //              project = Project.find(project_attr[:name])
    //              role = Role.find_by(name: project_attr[:role])

    //              Member.create!(
    //                project: project,
    //                principal: group,
    //                roles: [role]
    //              )
    //            }
    //          }
    //        }
    //      }
  }

 private:
  void seed_groups() {
    //      groups = demo_data_for("groups")
    //      if ( groups.present?) {
    //        groups.each { |group_attr|
    //          LOG_DEBUG << "."
    //          create_group group_attr[:name]
    //        }
    //      }
  }

  //     void create_group(name) {
  //      Group.create lastname: name
  //    }
};
}  // namespace DemoData
}  // namespace seeder
}  // namespace openproj
