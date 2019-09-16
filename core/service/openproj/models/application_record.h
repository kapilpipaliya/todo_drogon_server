#pragma once
#include "activerecord.h"
namespace openproj {
class ApplicationRecord : public ActiveRecord::Base {
//  this->abstract_class = true

  //
  // Get the newest recently changed resource for the given record classes
  //
  // e.g., +most_recently_changed(WorkPackage, Type, Status)+
  //
  // Returns the timestamp of the most recently updated value
//   void most_recently_changed(*record_classes) {
//    queries = record_classes.map { |clz|
//      column_name = clz.send(:timestamp_attributes_for_update_in_model)&.first || 'updated_at'
//      "(SELECT MAX(#{column_name}) AS max_updated_at FROM #{clz.table_name})"
//    }
//      .join(" UNION ")

//    union_query = <<~SQL
//      SELECT MAX(union_query.max_updated_at)
//      FROM (#{queries})
//      AS union_query
//    SQL

//    ActiveRecord::Base
//      .connection
//      .select_all(union_query)
//      .rows
//      &.first // first result row
//      &.first // max column
//  }
};
}
