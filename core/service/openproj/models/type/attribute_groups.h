#pragma once
namespace openproj {
namespace TypeN::AttributeGroups {
  // extend ActiveSupport::Concern

//  included {
//    before_save :write_attribute_groups_objects
//    // after_save :unset_attribute_groups_objects
//    after_destroy :remove_attribute_groups_queries

//    serialize :attribute_groups, Array
//    // attr_accessor :attribute_groups_objects

//    // Mapping from AR attribute name to a default group
//    // May be extended by plugins
//    mattr_accessor :default_group_map {
//      {
//        author: :people,
//        assignee: :people,
//        responsible: :people,
//        estimated_time: :estimates_and_time,
//        spent_time: :estimates_and_time,
//        priority: :details
//      }
//    }

//    // All known default
//    mattr_accessor :default_groups {
//      {
//        people: :label_people,
//        estimates_and_time: :label_estimates_and_time,
//        details: :label_details,
//        other: :label_other,
//        children: :'activerecord.attributes.work_package.children'
//      }
//    }
//  }

//  class_methods {
//    //
//    // Add a new default group name
//     void add_default_group(name, label_key) {
//      default_groups[name.to_sym] = label_key
//    }

//    //
//    // Add a mapping from attribute key to an existing default group
//     void add_default_mapping(group, *keys) {
//      unless default_groups.include? group
//        raise ArgumentError, "Can't add mapping for '#{keys.inspect}'. Unknown default group '#{group}'."
//      }

//      keys.each { |key|
//        default_group_map[key.to_sym] = group
//      }
//    }
//  }

  //
  // Read the serialized attribute groups, if customized.
  // Otherwise, return +default_attribute_groups+
   void attribute_groups() {
//    this->attribute_groups_objects ||= begin
//      groups = custom_attribute_groups || default_attribute_groups

//      to_attribute_group_class(groups)
//    }

//    attribute_groups_objects
  }

  //
  // Resets the default attribute groups
   void reset_attribute_groups() {
//    // Remove all active custom fields
//    this->custom_field_ids = []

//    this->attribute_groups_objects = to_attribute_group_class(default_attribute_groups)
  }

  //
  // Update the attribute groups object.
//   void attribute_groups=(groups) {
//    attribute_groups_will_change!
//    this->attribute_groups_objects = to_attribute_group_class(groups)
//  }

  //
  // Returns the default +attribute_groups+ put together by
  // the default group map.
   void default_attribute_groups() {
//    values = work_package_attributes_by_default_group_key

//    groups = default_groups.keys.each_with_object([]) { |groupkey, array|
//      members = values[groupkey]
//      if ( members.present?) { array << [groupkey, members] ;}
//    }

//    groups
  }

//   void reload(*args) {
//    unset_attribute_groups_objects
//    super
//  }

   void unset_attribute_groups_objects() {
//    this->attribute_groups_objects = nil
  }


//  private:

   void write_attribute_groups_objects() {
//    if ( attribute_groups_objects.nil?) { return ;}

//    groups = if ( attribute_groups_objects == to_attribute_group_class(default_attribute_groups)) {
//               nil
//             else
//               to_attribute_group_array(attribute_groups_objects)
//             }

//    write_attribute(:attribute_groups, groups)

//    cleanup_query_groups_queries
  }

   void custom_attribute_groups() {
//    read_attribute(:attribute_groups).presence
  }

//   void default_group_key(key) {
//    if ( CustomField.custom_field_attribute?(key)) {
//      :other
//    else
//      default_group_map.fetch(key.to_sym, :details)
//    }
//  }

  //
  // Get the default attribute groups for this type.
  // if ( it has activated custom fields through +custom_field_ids=+,) {
  // it will put them into the other group.
   void work_package_attributes_by_default_group_key() {
//    active_cfs = active_custom_field_attributes
//    work_package_attributes
//      .keys
//      .select { |key| default_attribute?(active_cfs, key) }
//      .group_by { |key| default_group_key(key.to_sym) }
  }

  //
  // Custom fields should not get included into the default form configuration.
  // This method might get patched by modules.
//   void default_attribute?(active_cfs, key) {
//    !(CustomField.custom_field_attribute?(key) && !active_cfs.include?(key))
//  }

//   void to_attribute_group_class(groups) {
//    groups.map { |group|
//      attributes = group[1]
//      first_attribute = attributes[0]
//      key = group[0]

//      if ( first_attribute.is_a?(Query)) {
//        new_query_group(key, first_attribute)
//      } else if ( first_attribute.is_a?(Symbol) && TypeN::QueryGroup.query_attribute?(first_attribute)) {
//        query = Query.find_by(id: TypeN::QueryGroup.query_attribute_id(first_attribute))
//        new_query_group(key, query)
//      else
//        new_attribute_group(key, attributes)
//      }
//    }
//  }

//   void to_attribute_group_array(groups) {
//    groups.map { |group|
//      attributes = if ( group.is_a?(TypeN::QueryGroup)) {
//                     query = group.query

//                     query.save

//                     [group.query_attribute_name]
//                   else
//                     group.attributes
//                   }
//      [group.key, attributes]
//    }
//  }

//   void new_attribute_group(key, attributes) {
//    TypeN::AttributeGroup.new(self, key, attributes)
//  }

//   void new_query_group(key, query) {
//    TypeN::QueryGroup.new(self, key, query)
//  }

//   void cleanup_query_groups_queries() {
//    return unless attribute_groups_changed?

//    new_groups = read_attribute(:attribute_groups)
//    old_groups = attribute_groups_was

//    ids = (old_groups.map(&:last).flatten - new_groups.map(&:last).flatten)
//          .map { |k| ::TypeN::QueryGroup.query_attribute_id(k) }
//          .compact

//    Query.destroy(ids)
//  }

//   void remove_attribute_groups_queries() {
//    attribute_groups
//      .select { |g| g.is_a?(TypeN::QueryGroup) }
//      .map(&:query)
//      .each(&:destroy)
//  }
};
}

