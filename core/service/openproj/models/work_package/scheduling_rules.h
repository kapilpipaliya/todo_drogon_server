#pragma once
namespace openproj {
namespace WorkPackageN::SchedulingRules {
  // extend ActiveSupport::Concern

//   void reschedule_after(date) {
//    WorkPackages::RescheduleService
//      .new(user: User.current,
//           work_package: self)
//      .call(date)
//  }

  // Calculates the minimum date that
  // will not violate the precedes relations (max(finish date, start date) + delay)
  // of this work package or its ancestors
  // e.g.
  // AP(due_date: 2017/07/24, delay: 1)-precedes-A
  //                                             |
  //                                           parent
  //                                             |
  // BP(due_date: 2017/07/22, delay: 2)-precedes-B
  //                                             |
  //                                           parent
  //                                             |
  // CP(due_date: 2017/07/25, delay: 2)-precedes-C
  //
  // Then soonest_start for:
  //   C is 2017/07/27
  //   B is 2017/07/25
  //   A is 2017/07/25
   void soonest_start() {
//    // Using a hand crafted union here instead of the alternative
//    // Relation.from_work_package_or_ancestors(self).follows
//    // as the performance of the above would be several orders of magnitude worse on MySql
//    sql = Relation.connection.unprepared_statement {
//      "((#{ancestors_follows_relations.to_sql}) UNION (#{own_follows_relations.to_sql})) AS relations"
//    }

//    this->soonest_start ||=
//      Relation.from(sql)
//              .map(&:successor_soonest_start)
//              .compact
//              .max
  }

  // Returns the time scheduled for this work package.
  //
  // Example:
  //   Start Date: 2/26/09, Finish Date: 3/04/09,  duration => 7
  //   Start Date: 2/26/09, Finish Date: 2/26/09,  duration => 1
  //   Start Date: 2/26/09, Finish Date: -      ,  duration => 1
  //   Start Date: -      , Finish Date: 2/26/09,  duration => 1
   void duration() {
//    if ( start_date && due_date) {
//      due_date - start_date + 1
//    else
//      1
//    }
  }

//  private:

   void ancestors_follows_relations() {
//    Relation.where(from_id: this->ancestors_relations.select(:from_id)).follows
  }

   void own_follows_relations() {
//    Relation.where(from_id: this->id).follows
  }
}
}
