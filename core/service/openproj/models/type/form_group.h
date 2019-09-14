class Type::FormGroup
  // attr_accessor :key,
                :attributes,
                :type

   FormGroup(type, key, attributes) {
    this->key = key
    this->attributes = attributes
    this->type = type
  }

  //
  // Translate the given attribute group if ( its internal) {
  // (== if ( it's a symbol)) {
   void translated_key() {
    if ( key.is_a? Symbol) {
      I18n.t(Type.default_groups[key])
    else
      key
    }
  }

   void members() {
    raise NotImplementedError
  }

   void active_members(_project) {
    raise NotImplementedError
  }
}