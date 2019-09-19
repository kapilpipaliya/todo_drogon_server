#pragma once
#include "../../basic_data/workflow_seeder.h"
#include "type_seeder.h"
#include "status_seeder.h"
#include "models/Types.h"
namespace openproj {
namespace seeder {
namespace StandardSeeder {
  namespace BasicData {
    class WorkflowSeeder : public openproj::seeder::BasicData::WorkflowSeeder {
    public:
        std::vector<row> workflows() {
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

            auto clientPtr = drogon::app().getDbClient("sce");
            drogon::orm::Mapper<drogon_model::openproject4::Types> mapper_type(clientPtr);
            auto type_task             = mapper_type.findBy(  Criteria(drogon_model::openproject4::Types::Cols::_name, CompareOperator::EQ, "Task"));
            auto type_milestone             = mapper_type.findBy(  Criteria(drogon_model::openproject4::Types::Cols::_name, CompareOperator::EQ, "Milestone"));
            auto type_phase             = mapper_type.findBy(  Criteria(drogon_model::openproject4::Types::Cols::_name, CompareOperator::EQ, "Phase"));
            auto type_feature             = mapper_type.findBy(  Criteria(drogon_model::openproject4::Types::Cols::_name, CompareOperator::EQ, "Feature"));
            auto type_epic             = mapper_type.findBy(  Criteria(drogon_model::openproject4::Types::Cols::_name, CompareOperator::EQ, "Epic"));
            auto type_user_story             = mapper_type.findBy(  Criteria(drogon_model::openproject4::Types::Cols::_name, CompareOperator::EQ, "User story"));
            auto type_bug             = mapper_type.findBy(  Criteria(drogon_model::openproject4::Types::Cols::_name, CompareOperator::EQ, "Bug"));

            drogon::orm::Mapper<drogon_model::openproject4::Statuses> mapper(clientPtr);
            auto new__             = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "New"));
            auto in_specification_ = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "In specification"));
            auto specified_        = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "Specified"));
            auto confirmed_        = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "Confirmed"));
            auto to_be_scheduled_  = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "To be scheduled"));
            auto scheduled_        = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "Scheduled"));
            auto in_progress_      = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "In progress"));
            auto developed_        = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "Developed"));
            auto in_testing_       = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "In testing"));
            auto tested_           = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "Tested"));
            auto test_failed_      = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "Test failed"));
            auto closed_           = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "Closed"));
            auto on_hold_          = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "On hold"));
            auto rejected_         = mapper.findBy(  Criteria(drogon_model::openproject4::Statuses::Cols::_name, CompareOperator::EQ, "Rejected"));
            auto new_             = *new__.at(0).getId();
            auto in_specification = *in_specification_.at(0).getId();
            auto specified        = *specified_.at(0).getId();
            auto confirmed        = *confirmed_.at(0).getId();
            auto to_be_scheduled  = *to_be_scheduled_.at(0).getId();
            auto scheduled        = *scheduled_.at(0).getId();
            auto in_progress      = *in_progress_.at(0).getId();
            auto developed        = *developed_.at(0).getId();
            auto in_testing       = *in_testing_.at(0).getId();
            auto tested           = *tested_.at(0).getId();
            auto test_failed      = *test_failed_.at(0).getId();
            auto closed           = *closed_.at(0).getId();
            auto on_hold          = *on_hold_.at(0).getId();
            auto rejected         = *rejected_.at(0).getId();

            data_.insert(data_.end(), {
                             {*type_task.at(0).getId().get(), {new_, in_progress, on_hold, rejected, closed}},
                             {*type_milestone.at(0).getId().get(), {new_, to_be_scheduled, scheduled, in_progress, on_hold, rejected, closed}},
                             {*type_phase.at(0).getId().get(), {new_, to_be_scheduled, scheduled, in_progress, on_hold, rejected, closed}},
                             {*type_feature.at(0).getId().get(), {new_, in_specification, specified, in_progress, developed, in_testing, tested, test_failed, on_hold, rejected, closed}},
                             {*type_epic.at(0).getId().get(), {new_, in_specification, specified, in_progress, developed, in_testing, tested, test_failed, on_hold, rejected, closed}},
                             {*type_user_story.at(0).getId().get(), {new_, in_specification, specified, in_progress, developed, in_testing, tested, test_failed, on_hold, rejected, closed}},
                             {*type_bug.at(0).getId().get(), {new_, confirmed, in_progress, developed, in_testing, tested, test_failed, on_hold, rejected, closed}}
      });
}
//       void type_seeder_class() {
//        ::StandardSeeder::BasicData::TypeSeeder
//      }

//       void status_seeder_class() {
//        ::StandardSeeder::BasicData::StatusSeeder
//      }
       void type_seed(){
           openproj::seeder::StandardSeeder::BasicData::TypeSeeder t;
           t.seed();
       };
       void status_seed(){
           openproj::seeder::StandardSeeder::BasicData::StatusSeeder s;
           s.seed();
       } ;
    };
  }
}
}
}
