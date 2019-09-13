namespace Queries::Filters::Shared::ProjectFilter {
   void included(base) {
    base.include(InstanceMethods)
    base.extend(ClassMethods)
  }

  namespace InstanceMethods {
     void allowed_values() {
      @allowed_values ||= begin
        // We don't care for the first value as we do not display the values visibly
        ::Project.visible.pluck(:id).map { |id| [id, id.to_s] }
      }
    }

     void type() {
      :list_optional
    }

     void type_strategy() {
      // Instead of getting the IDs of all the projects a user is allowed
      // to see we only check that the value is an integer.  Non valid ids
      // will then simply create an empty result but will not cause any
      // harm.
      @type_strategy ||= ::Queries::Filters::Strategies::IntegerListOptional.new(self)
    }
  }

  namespace ClassMethods {
     void key() {
      :project_id
    }
  }
}
