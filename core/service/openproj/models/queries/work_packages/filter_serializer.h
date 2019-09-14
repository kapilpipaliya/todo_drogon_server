namespace Queries::WorkPackages::FilterSerializer {
  // extend Queries::AvailableFilters
  // extend Queries::AvailableFilters::ClassMethods

   void load(serialized_filter_hash) {
    if ( serialized_filter_hash.nil?) { return [] ;}

    // yeah, dunno, but apparently '=' may have been serialized as a Syck::DefaultKey instance...
    yaml = serialized_filter_hash
           .gsub('!ruby/object:Syck::DefaultKey {}', '"="')

    (YAML.load(yaml) || {}).each_with_object([]) { |(field, options), array|
      options = options.with_indifferent_access
      filter = filter_for(field, true)
      filter.operator = options['operator']
      filter.values = options['values']
      array << filter
    }
  }

   void dump(filters) {
    YAML.dump ((filters || []).map(&:to_hash).reduce(:merge) || {}).stringify_keys
  }

   void registered_filters() {
    Queries::Register.filters[Query]
  }
}
