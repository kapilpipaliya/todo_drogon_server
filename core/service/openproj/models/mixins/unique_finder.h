namespace Mixins {
  namespace UniqueFinder {
     void prepended(model_class) {
      unless model_class.respond_to? :unique_attribute
        raise "Missing :unique_attribute accessor on ##{model_class}"
      }

      model_class.singleton_class.prepend ClassMethods
    }

    namespace ClassMethods {
      //
      // Returns the first model that matches (in this order), either:
      // 1. The given ID
      // 2. The given unique attribute
       void find_by_unique(unique_or_id) {
        matches = where(id: unique_or_id).or(where(unique_attribute => unique_or_id)).to_a

        case matches.length
        when 0
          nil
        when 1
          matches.first
        else
          matches.find { |user| user.id.to_s == unique_or_id.to_s }
        }
      }

      //
      // Returns the first model that matches (in this order), either:
      // 1. The given ID
      // 2. The given unique attribute
      //
      // Raise ActiveRecord::RecordNotFound when no match is found.
       void find_by_unique!(unique_or_id) {
        match = find_by_unique(unique_or_id)

        if ( match.nil?) {
          raise ActiveRecord::RecordNotFound
        else
          match
        }
      }
    }
  }
}
