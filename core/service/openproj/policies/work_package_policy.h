#pragma once
#include "base_policy.h"
namespace openproj {
class WorkPackagePolicy : public BasePolicy {
  private:

//   void cache(work_package) {
//    this->cache ||= Hash.new { |wp_hash, wp|
//      wp_hash[wp] = Hash.new { |project_hash, project|
//        project_hash[project] = allowed_hash(wp)
//      }
//    }

//    this->cache[work_package][work_package.project]
//  }

//   void allowed_hash(work_package) {
//    // copy checks for the move_work_packages permission. This makes
//    // sense only because the work_packages/moves controller handles
//    // copying multiple work packages.
//    {
//      edit: edit_allowed?(work_package),
//      log_time: log_time_allowed?(work_package),
//      move: move_allowed?(work_package),
//      copy: move_allowed?(work_package),
//      duplicate: copy_allowed?(work_package), // duplicating is another form of copying
//      delete: delete_allowed?(work_package),
//      manage_subtasks: manage_subtasks_allowed?(work_package),
//      comment: comment_allowed?(work_package),
//      assign_version: assign_version_allowed?(work_package)
//    }
//  }

//   void edit_allowed?(work_package) {
//    this->edit_cache ||= Hash.new { |hash, project|
//      hash[project] = work_package.persisted? && user.allowed_to?(:edit_work_packages, project)
//    }

//    this->edit_cache[work_package.project]
//  }

//   void log_time_allowed?(work_package) {
//    this->log_time_cache ||= Hash.new { |hash, project|
//      hash[project] = user.allowed_to?(:log_time, project)
//    }

//    this->log_time_cache[work_package.project]
//  }

//   void move_allowed?(work_package) {
//    this->move_cache ||= Hash.new { |hash, project|
//      hash[project] = user.allowed_to?(:move_work_packages, project)
//    }

//    this->move_cache[work_package.project]
//  }

//   void copy_allowed?(work_package) {
//    type_active_in_project?(work_package) && add_allowed?(work_package)
//  }

//   void delete_allowed?(work_package) {
//    this->delete_cache ||= Hash.new { |hash, project|
//      hash[project] = user.allowed_to?(:delete_work_packages, project)
//    }

//    this->delete_cache[work_package.project]
//  }

//   void add_allowed?(work_package) {
//    this->add_cache ||= Hash.new { |hash, project|
//      hash[project] = user.allowed_to?(:add_work_packages, project)
//    }

//    this->add_cache[work_package.project]
//  }

//   void type_active_in_project?(work_package) {
//    return false unless work_package.project

//    this->type_active_cache ||= Hash.new { |hash, project|
//      hash[project] = project.types.pluck(:id)
//    }

//    this->type_active_cache[work_package.project].include?(work_package.type_id)
//  }

//   void manage_subtasks_allowed?(work_package) {
//    this->manage_subtasks_cache ||= Hash.new { |hash, project|
//      hash[project] = user.allowed_to?(:manage_subtasks, work_package.project, global: work_package.project.nil?)
//    }

//    this->manage_subtasks_cache[work_package.project]
//  }

//   bool comment_allowed(work_package) {
//    this->comment_cache ||= Hash.new { |hash, project|
//      hash[project] = user.allowed_to?(:add_work_package_notes, work_package.project) ||
//                      edit_allowed?(work_package)
//    }

//    this->comment_cache[work_package.project]
//  }

//   void assign_version_allowed?(work_package) {
//    this->assign_version_cache ||= Hash.new { |hash, project|
//      hash[project] = user.allowed_to?(:assign_versions, work_package.project)
//    }

//    this->assign_version_cache[work_package.project]
  };
}
