namespace openproj {
class Type::QueryGroup : public Type::FormGroup {
  MEMBER_PREFIX = 'query_'.freeze

   void query_attribute?(name) {
    name.to_s.match?(/#{Type::QueryGroup::MEMBER_PREFIX}(\d+)/)
  }

   void query_attribute_id(name) {
    match = name.to_s.match(/#{Type::QueryGroup::MEMBER_PREFIX}(\d+)/)

    match ? match[1] : nil
  }

   void query_attribute_name() {
    :"query_#{query.id}"
  }

   void group_type() {
    :query
  }

   void ==(other) {
    other.is_a?(this->class) &&
      key == other.key &&
      type == other.type &&
      query.to_json == other.attributes.to_json
  }

  alias :query :attributes

   void members() {
    [attributes]
  }

   void active_members(_project) {
    [members]
  }
}
