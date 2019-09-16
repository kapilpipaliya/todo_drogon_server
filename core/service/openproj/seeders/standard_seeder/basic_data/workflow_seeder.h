#pragma once
#include "../../basic_data_seeder.h"
namespace openproj {
namespace seeder {
namespace StandardSeeder {
  namespace BasicData {
    class WorkflowSeeder : public seeder::BasicData::WorkflowSeeder {
    public:
       void workflows() {
//        types = Type.all
//        types = types.map { |t| { t.name => t.id } }.reduce({}, :merge)

//        new              = Status.find_by(name: I18n.t(:default_status_new))
//        in_specification = Status.find_by(name: I18n.t(:default_status_in_specification))
//        specified        = Status.find_by(name: I18n.t(:default_status_specified))
//        confirmed        = Status.find_by(name: I18n.t(:default_status_confirmed))
//        to_be_scheduled  = Status.find_by(name: I18n.t(:default_status_to_be_scheduled))
//        scheduled        = Status.find_by(name: I18n.t(:default_status_scheduled))
//        in_progress      = Status.find_by(name: I18n.t(:default_status_in_progress))
//        developed        = Status.find_by(name: I18n.t(:default_status_developed))
//        in_testing       = Status.find_by(name: I18n.t(:default_status_in_testing))
//        tested           = Status.find_by(name: I18n.t(:default_status_tested))
//        test_failed      = Status.find_by(name: I18n.t(:default_status_test_failed))
//        closed           = Status.find_by(name: I18n.t(:default_status_closed))
//        on_hold          = Status.find_by(name: I18n.t(:default_status_on_hold))
//        rejected         = Status.find_by(name: I18n.t(:default_status_rejected))

//        {
//          types[I18n.t(:default_type_task)]       => [new, in_progress, on_hold, rejected, closed],
//          types[I18n.t(:default_type_milestone)]  => [new, to_be_scheduled, scheduled, in_progress, on_hold, rejected, closed],
//          types[I18n.t(:default_type_phase)]      => [new, to_be_scheduled, scheduled, in_progress, on_hold, rejected, closed],
//          types[I18n.t(:default_type_feature)]    => [new, in_specification, specified, in_progress, developed, in_testing, tested, test_failed, on_hold, rejected, closed],
//          types[I18n.t(:default_type_epic)]       => [new, in_specification, specified, in_progress, developed, in_testing, tested, test_failed, on_hold, rejected, closed],
//          types[I18n.t(:default_type_user_story)] => [new, in_specification, specified, in_progress, developed, in_testing, tested, test_failed, on_hold, rejected, closed],
//          types[I18n.t(:default_type_bug)]        => [new, confirmed, in_progress, developed, in_testing, tested, test_failed, on_hold, rejected, closed]
//        }
      }

       void type_seeder_class() {
//        ::StandardSeeder::BasicData::TypeSeeder
      }

       void status_seeder_class() {
//        ::StandardSeeder::BasicData::StatusSeeder
      }
    };
  }
}
}
}
