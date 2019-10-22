#pragma once
namespace openproj {
namespace models {
namespace WorkPackageN::Parent {
//   void prepended(base) {
//    if (: :saved_change_to_parent_id?) { base.after_save :update_parent_relation, ;}
//    base.include Concerns::VirtualAttribute

//    base.virtual_attribute "parent_id", cast_type: :integer

//    base.define_attribute_method "parent"

//    base.scope :with_parent, ->(*args) {
//      opts = Hash(args.first)
//      // noinspection RubySimplifyBooleanInspection
//      neg = opts[:present] == false ? "NOT" : ""
//      rel = Relation.table_name
//      wp = WorkPackage.table_name

//      query = "#{neg} EXISTS (SELECT 1 FROM #{rel} WHERE #{rel}.to_id = #{wp}.id AND #{rel}.hierarchy > 0"

//      if ( opts[:in].respond_to? :arel) {
//        subset = opts[:in].arel //                            .select() (or project()) will only add columns
//        subset.projections = [WorkPackage.arel_table[:id]] // but we only need the ID, so we reset the projections

//        query += " AND relations.from_id IN (#{subset.to_sql})"
//      }

//      query += " LIMIT 1)"

//      where(query)
//    }

//    base.scope :without_parent, ->(*args) {
//      with_parent Hash(args.first).merge(present: false)
//    }

//    base.scope :with_children, ->(*args) {
//      opts = Hash(args.first)
//      // noinspection RubySimplifyBooleanInspection
//      neg = opts[:present] == false ? "NOT" : ""
//      rel = Relation.table_name
//      wp = WorkPackage.table_name

//      query = "#{neg} EXISTS (SELECT 1 FROM #{rel} WHERE #{rel}.from_id = #{wp}.id AND #{rel}.hierarchy > 0"

//      if ( opts[:in].respond_to? :arel) {
//        subset = opts[:in].arel //                            .select() (or project()) will only add columns
//        subset.projections = [WorkPackage.arel_table[:id]] // but we only need the ID, so we reset the projections

//        query += " AND relations.to_id IN (#{subset.to_sql})"
//      }

//      query += " LIMIT 1)"

//      where(query)
//    }

//    base.scope :without_children, ->(*args) {
//      with_children Hash(args.first).merge(present: false)
//    }
//  }

  // attr_accessor :parent_object,
//                :do_halt

//   void parent=(work_package) {
//    id = work_package && work_package.id

//    this->parent_id = id

//    this->parent_object = work_package
//  }

   void parent() {
//    if ( this->parent_id_set) {
//      this->parent_object || parent_from_id
//    else
//      this->parent_object || parent_from_relation || parent_from_id
//    }
  }

   bool has_parent() {
//    !parent_relation.nil?
  }

//   void reload(*args) {
//    this->parent_object = nil

//    super
//  }

//   void parent_id=(id) {
//    id = id.to_i > 0 ? id.to_i : nil

//    super(id)
//    if ( this->parent_object && this->parent_object.id != id) { this->parent_object = nil ;}

//    this->parent_id
//  }

   void parent_id() {
//    if ( this->parent_id_set) { return this->parent_id ;}

//    this->parent_id || parent && parent.id
  }

   void update_parent_relation() {
//    if ( parent_relation) {
//      parent_relation.destroy
//    }

//    if ( parent_object) {
//      create_parent_relation from: parent_object
//    } else if ( this->parent_id) {
//      create_parent_relation from_id: this->parent_id
//    }
  }

//  private:

   void parent_from_relation() {
//    if ( parent_relation && ((this->parent_id && parent_relation.from.id == this->parent_id) || !this->parent_id)) {
//      set_virtual_attribute_was("parent_id", parent_relation.from_id)
//      this->parent_object = parent_relation.from
//    }
  }

   void parent_from_id() {
//    if ( this->parent_id) {
//      set_virtual_attribute_was("parent_id", this->parent_id)
//      this->parent_object = WorkPackage.find(this->parent_id)
//    }
  }
}
}
}