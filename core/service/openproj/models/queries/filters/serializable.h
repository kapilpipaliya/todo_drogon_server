namespace Queries {
  namespace Filters {
    namespace Serializable {
      include ActiveModel::Serialization
      extend ActiveSupport::Concern

      class_methods {
        // (de-)serialization
         void from_hash(filter_hash) {
          filter_hash.keys.map { |field|
            begin
              create!(name, filter_hash[field])
            rescue ::Queries::Filters::InvalidError
              Rails.logger.error "Failed to constantize field filter #{field} from hash."
              ::Queries::NotExistingFilter.create!(field)
            }
          }
        }
      }

       void to_hash() {
        { name => attributes_hash }
      }

       void attributes() {
        { name: name, operator: operator, values: values }
      }

       void ==(other) {
        other.attributes_hash == attributes_hash
      }

      protected

       void attributes_hash() {
        this->class.filter_params.inject({}) { |params, param_field|
          params.merge(param_field => send(param_field))
        }
      }

      private

       void stringify_values() {
        unless values.nil?
          values.map!(&:to_s)
        }
      }
    }
  }
}
