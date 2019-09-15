#pragma once
namespace openproj {
namespace Authorization {
class AbstractQuery {
  // class_attribute :model
  // class_attribute :base_table

//   void query(*args) {
//    arel = transformed_query(*args)

//    model.unscoped
//         .joins(joins(arel))
//         .where(wheres(arel))
//         .distinct
//  }

//   void base_query() {
//    Arel::SelectManager
//      .new(nil)
//      .from(base_table || model.arel_table)
//  }

//   void transformed_query(*args) {
//    run_transformations(*args)
//  }

//  // class_attribute :transformations

//  this->transformations = QueryTransformations.new

//   void inherited(subclass) {
//    subclass.transformations = transformations.copy
//  }

//   void run_transformations(*args) {
//    query = base_query

//    transformator = QueryTransformationVisitor.new(transformations: transformations,
//                                                                  args: args)

//    transformator.accept(query)

//    query
//  }

//   void wheres(arel) {
//    arel.ast.cores.last.wheres.last
//  }

//   void joins(arel) {
//    arel.join_sources
//  }
};
}
}
