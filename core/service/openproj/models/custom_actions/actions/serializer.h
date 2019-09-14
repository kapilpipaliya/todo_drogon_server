namespace openproject {
class CustomActions::Actions::Serializer
   void load(value) {
    return [] unless value
    YAML
      .safe_load(value, [Symbol])
      .map { |key, values|
      klass = nil

      CustomActions::Register
        .actions
        .detect { |a|
        klass = a.for(key)
      }

      klass ||= CustomActions::Actions::Inexistent

      klass.new(values)
    }.compact
  }

   void dump(actions) {
    YAML::dump(actions.map { |a| [a.key, a.values.map(&:to_s)] })
  }
}
