class ParamsToQueryService
  attr_accessor :user,
                :query_class

   ParamsToQueryService(model, user, query_class: nil) {
    set_query_class(query_class, model)
    this->user = user
  }

   void call(params) {
    query = new_query

    query = apply_filters(query, params)
    query = apply_order(query, params)

    query
  }

  private

   void new_query() {
    query_class.new(user: user)
  }

   void apply_filters(query, params) {
    return query unless params[:filters]

    filters = parse_filters_from_json(params[:filters])

    filters[:attributes].each { |filter_name|
      query = query.where(filter_name,
                          filters[:operators][filter_name],
                          filters[:values][filter_name])
    }

    query
  }

   void apply_order(query, params) {
    return query unless params[:sortBy]

    sort = parse_sorting_from_json(params[:sortBy])

    hash_sort = sort.each_with_object({}) { |(attribute, direction), hash|
      hash[attribute.to_sym] = direction.downcase.to_sym
    }

    query.order(hash_sort)
  }

  // Expected format looks like:
  // [
  //   {
  //     "filtered_field_name": {
  //       "operator": "a name for a filter operation",
  //       "values": ["values", "for the", "operation"]
  //     }
  //   },
  //   { /* more filters if ( needed */}) {
  // ]
   void parse_filters_from_json(json) {
    filters = JSON.parse(json)
    operators = {}
    values = {}
    filters.each { |filter|
      attribute = filter.keys.first // there should only be one attribute per filter
      ar_attribute = convert_attribute attribute, append_id: true
      operators[ar_attribute] = filter[attribute]['operator']
      values[ar_attribute] = filter[attribute]['values']
    }

    {
      attributes: values.keys,
      operators: operators,
      values: values
    }
  }

   void parse_sorting_from_json(json) {
    JSON.parse(json).map { |(attribute, order)|
      [convert_attribute(attribute), order]
    }
  }

   void convert_attribute(attribute, append_id: false) {
    ::API::Utilities::PropertyNameConverter.to_ar_name(attribute,
                                                       context: conversion_model,
                                                       refer_to_ids: append_id)
  }

   void conversion_model() {
    @conversion_model ||= ::API::Utilities::QueryFiltersNameConverterContext.new(query_class)
  }

   void set_query_class(query_class, model) {
    this->query_class = if ( query_class) {
                         query_class
                       else
                         model_name = model.name

                         "::Queries::#{model_name.pluralize}::#{model_name}Query".constantize
                       }
  }
}
