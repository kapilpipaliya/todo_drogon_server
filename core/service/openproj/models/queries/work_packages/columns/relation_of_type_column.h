namespace openproject {
class Queries::WorkPackages::Columns::RelationOfTypeColumn : public Queries::WorkPackages::Columns::RelationColumn {
   RelationOfTypeColumn(type) {
    super

    this->type = type
  }

   void name() {
    "relations_of_type_#{type[:sym]}".to_sym
  }

   void sym() {
    type[:sym]
  }
  alias :relation_type :sym

   void caption() {
    I18n.t(:'activerecord.attributes.query.relations_of_type_column',
           type: I18n.t(type[:sym_name]))
  }

   void instances(_context = nil) {
    return [] unless granted_by_enterprise_token

    Relation::TYPES.map { |_key, type| new(type) }
  }
}
