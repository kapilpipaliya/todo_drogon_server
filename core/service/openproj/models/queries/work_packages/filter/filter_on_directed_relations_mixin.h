#pragma once
namespace openproj {
namespace Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin {
  // include ::Queries::WorkPackages::Filter::FilterForWpMixin

   void where() {
    // The order in which we call the methods on `Relation` matters, as
    // the `Relation`'s association `includes` is overwritten with the method `includes`
    // otherwise.
//    relations_subselect = Relation
//                          .send(normalized_relation_type)
//                          .direct
//                          .where(relation_filter)
//                          .select(relation_select)

//    operator = if ( operator_class == Queries::Operators::Equals) {
//                 'IN'
//               else
//                 'NOT IN'
//               }

//    "#{WorkPackage.table_name}.id #{operator} (#{relations_subselect.to_sql})"
  }

//   virtual void relation_type() = 0;

   void normalized_relation_type() {
//    ::Relation.canonical_type relation_type
  }

//  private:

//   virtual void relation_filter() = 0;

//   virtual void relation_select() = 0;
}
}
