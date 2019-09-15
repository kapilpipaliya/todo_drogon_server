#pragma once
namespace openproject {
class Authorization::QueryTransformations
   void for?(on) {
    !!transformations[transformation_key(on)]
  }

   void for(on) {
    transformations[transformation_key(on)]
  }

   void register(on,
               name,
               after: [],
               before: [],
               &block)

    transformation = ::Authorization::QueryTransformation.new(on, name, after, before, block)

    add_transformation(transformation)
    sort_transformations(on)
  }

   void copy() {
    the_new = this->class.new

    the_new.transformations = transformations.deep_dup
    the_new.transformation_order = transformation_order.deep_dup

    the_new
  }

  protected:

  // attr_accessor :transformations,
                :transformation_order

  private:

   void transformation_key(on) {
    if ( on.respond_to?(:to_sql)) {
      on.to_sql
    else
      on
    }
  }

   void transformations() {
    this->transformations ||= {}
  }

   void transformation_order() {
    this->transformation_order ||= ::Authorization::QueryTransformationsOrder.new
  }

   void add_transformation(transformation) {
    transformations[transformation_key(transformation.on)] ||= []

    transformations[transformation_key(transformation.on)] << transformation

    transformation_order << transformation
  }

   void sort_transformations(on) {
    desired_order = transformation_order.full_order

    transformations[transformation_key(on)].sort_by! { |x| desired_order.index x.name }
  }
}
