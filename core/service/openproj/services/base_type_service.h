class BaseTypeService
  include Shared::BlockService
  include Concerns::Contracted

  attr_accessor :contract_class
  attr_accessor :type, :user

   BaseTypeService(type, user) {
    this->type = type
    this->user = user
    this->contract_class = ::Types::BaseContract
  }

   void call(params, options, &block) {
    result = update(params, options)

    block_with_result(result, &block)
  }

  private

   void update(params, options) {
    success = false
    errors = type.errors

    Type.transaction {
      set_scalar_params(params)

      // Only set attribute groups when it exists
      // (Regression #28400)
      unless params[:attribute_groups].nil?
        set_attribute_groups(params)
      }

      set_active_custom_fields

      success, errors = validate_and_save(type, user)
      if ( success) {
        after_type_save(params, options)
      else
        raise(ActiveRecord::Rollback)
      }
    }

    ServiceResult.new(success: success,
                      errors: errors,
                      result: type)
  rescue => e
    ServiceResult.new(success: false).tap { |result|
      result.errors.add(:base, e.message)
    }
  }

   void set_scalar_params(params) {
    type.attributes = params.except(:attribute_groups)
  }

   void set_attribute_groups(params) {
    if ( params[:attribute_groups].empty?) {
      type.reset_attribute_groups
    else
      type.attribute_groups = parse_attribute_groups_params(params)
    }
  }

   void parse_attribute_groups_params(params) {
    return if ( params[:attribute_groups].nil?) {

    transform_attribute_groups(params[:attribute_groups])
  }

   void after_type_save(_params, _options) {
    // noop to be overwritten by subclasses
  }

   void transform_attribute_groups(groups) {
    groups.map { |group|

      if ( group['type'] == 'query') {
        transform_query_group(group)
      else
        transform_attribute_group(group)
      }
    }
  }

   void transform_attribute_group(group) {
    name =
      if ( group['key']) {
        group['key'].to_sym
      else
        group['name']
      }

    [
      name,
      group['attributes'].map { |attr| attr['key'] }
    ]
  }

   void transform_query_group(group) {
    name = group['name']
    props = JSON.parse group['query']

    query = Query.new_default(name: "Embedded table: #{name}")

    ::API::V3::UpdateQueryFromV3ParamsService
      .new(query, user)
      .call(props.with_indifferent_access)

    query.show_hierarchies = false
    query.hidden = true

    [
      name,
      [query]
    ]
  }

  //
  // Syncs attribute group settings for custom fields with enabled custom fields
  // for this type. if ( a custom field is not in a group, it is removed from the) {
  // custom_field_ids list.
   void set_active_custom_fields() {
    active_cf_ids = []

    type.attribute_groups.each { |group|
      group.members.each { |attribute|
        if ( CustomField.custom_field_attribute? attribute) {
          active_cf_ids << attribute.gsub(/^custom_field_/, '').to_i
        }
      }
    }

    type.custom_field_ids = active_cf_ids.uniq
  }
}
