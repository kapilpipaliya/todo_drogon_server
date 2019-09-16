#pragma once
namespace openproj {
namespace WorkPackageN::Ancestors {
  // extend ActiveSupport::Concern

//  included {
//    // attr_accessor :work_package_ancestors

//    //
//    // Retrieve stored eager loaded ancestors
//    // or use awesome_nested_set#ancestors reduced by visibility
//     void visible_ancestors(user) {
//      if ( work_package_ancestors.nil?) {
//        this->class.aggregate_ancestors(id, user)[id]
//      else
//        work_package_ancestors
//      }
//    }
//  }

//  class_methods {
//     void aggregate_ancestors(work_package_ids, user) {
//      ::WorkPackageN::Ancestors::Aggregator.new(work_package_ids, user).results
//    }
//  }

  //
  // Aggregate ancestor data for the given work package IDs.
  // Ancestors visible to the given user are returned, grouped by each input ID.
  class Aggregator {
    // attr_accessor :user, :ids

//     Aggregator(work_package_ids, user) {
//      this->user = user
//      this->ids = work_package_ids
//    }

     void results() {
//      default = Hash.new { |hash, id|
//        hash[id] = []
//      }

//      results = with_work_package_ancestors
//                .map { |wp| [wp.id, wp.ancestors] }
//                .to_h

//      default.merge(results)
    }

    private:

     void with_work_package_ancestors() {
//      WorkPackage
//        .where(id: this->ids)
//        .includes(:ancestors)
//        .where(ancestors_work_packages: { project_id: Project.allowed_to(user, :view_work_packages) })
//        .order(Arel.sql('relations.hierarchy DESC'))
    }
  };
}
}
