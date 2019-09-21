#pragma once
namespace openproj {
namespace service {
namespace API {
  namespace V3 {
    class ParseQueryParamsService {
    public:
//       void call(params) {
//        parsed_params = {}
//        skip_empty = []

//        parsed_params[:group_by] = group_by_from_params(params, skip_empty)

//        error_result = with_service_error_on_json_parse_error {
//          parsed_params[:filters] = filters_from_params(params)

//          parsed_params[:sort_by] = sort_by_from_params(params)

//          parsed_params[:timeline_labels] = timeline_labels_from_params(params)
//        }
//        if ( error_result) { return error_result ;}

//        parsed_params[:columns] = columns_from_params(params)

//        parsed_params[:display_sums] = boolearize(params[:showSums])

//        parsed_params[:timeline_visible] = boolearize(params[:timelineVisible])

//        parsed_params[:timeline_zoom_level] = params[:timelineZoomLevel]

//        parsed_params[:highlighting_mode] = params[:highlightingMode]

//        parsed_params[:highlighted_attributes] = highlighted_attributes_from_params(params)

//        parsed_params[:display_representation] = params[:displayRepresentation]

//        parsed_params[:show_hierarchies] = boolearize(params[:showHierarchies])

//        allow_empty = params.keys + skip_empty
//        ServiceResult.new(success: true, result: without_empty(parsed_params, allow_empty))
//      }

//       void group_by_from_params(params, skip_empty) {
//        return nil unless params_exist?(params, %i(group_by groupBy g))

//        attribute = params[:group_by] || params[:groupBy] || params[:g]
//        if ( attribute.present?) {
//          convert_attribute attribute
//        else
//          // Group by explicitly set to empty
//          skip_empty << :group_by
//          nil
//        }
//      }

//       void sort_by_from_params(params) {
//        return unless params[:sortBy]

//        parse_sorting_from_json(params[:sortBy])
//      }

//       void timeline_labels_from_params(params) {
//        return unless params[:timelineLabels]

//        JSON.parse(params[:timelineLabels])
//      }

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
//       void filters_from_params(params) {
//        return unless params[:filters]

//        filters = params[:filters]
//        if ( filters.is_a? String) { filters = JSON.parse filters ;}

//        filters.each_with_object([]) { |filter, array|
//          attribute = filter.keys.first // there should only be one attribute per filter
//          operator =  filter[attribute]["operator"]
//          values = filter[attribute]["values"]
//          ar_attribute = convert_filter_attribute attribute, append_id: true

//          internal_representation = { field: ar_attribute,
//                                      operator: operator,
//                                      values: values }
//          array << internal_representation
//        }
//      }

//       void columns_from_params(params) {
//        columns = params[:columns] || params[:c] || params[:column_names] || params[:"columns[]"]

//        return unless columns

//        columns.map { |column|
//          convert_attribute(column)
//        }
//      }

//       void highlighted_attributes_from_params(params) {
//        highlighted_attributes = Array(params[:highlightedAttributes].presence)

//        return unless highlighted_attributes.present?

//        highlighted_attributes.map { |href|
//          attr = href.split("/").last
//          convert_attribute(attr)
//        }
//      }

//       void boolearize(value) {
//        if ( value == "true") {
//          true
//        } else if ( value == "false") {
//          false
//        }
//      }

      //
      // Maps given field names coming from the frontend to the actual names
      // as expected by the query. This works slightly different to what happens
      // in #column_names_from_params. For instance while they column name is
      // :type the expected field name is :type_id.
      //
      // Examples:
      //   * status => status_id
      //   * progresssDone => done_ratio
      //   * assigned => assigned_to
      //   * customField1 => cf_1
      //
      // @param query [Query] Query for which to get the correct field names.
      // @param field_names [Array] Field names as read from the params.
      // @return [Array] Returns a list of fixed field names. The list may contain nil values
      //                 for fields which could not be found.
//       void fix_field_array(field_names) {
//        if ( field_names.nil?) { return [] ;}

//        field_names
//          .map { |name| convert_attribute name, append_id: true }
//      }

//       void parse_sorting_from_json(json) {
//        JSON.parse(json).map { |order|
//          attribute, direction = if ( order.is_a?(Array)) {
//                                   [order.first, order.last]
//                                 } else if ( order.is_a?(String)) {
//                                   order.split(":")
//                                 }

//          [convert_attribute(attribute), direction]
//        }
//      }

//       void convert_attribute(attribute, append_id: false) {
//        ::API::Utilities::WpPropertyNameConverter.to_ar_name(attribute,
//                                                             refer_to_ids: append_id)
//      }

//       void convert_filter_attribute(attribute, append_id: false) {
//        ::API::Utilities::QueryFiltersNameConverter.to_ar_name(attribute,
//                                                               refer_to_ids: append_id)
//      }

//       void with_service_error_on_json_parse_error() {
//        yield

//        nil
//      rescue ::JSON::ParserError => error
//        result = ServiceResult.new
//        result.errors.add(:base, error.message)
//        return result
//      }

//       void params_exist?(params, symbols) {
//        unsafe_params(params).detect { |k, _| symbols.include? k.to_sym }
//      }

      //
      // Access the parameters as a hash, which has been deprecated
//       void unsafe_params(params) {
//        if ( params.is_a? ActionController::Parameters) {
//          params.to_unsafe_h
//        else
//          params
//        }
//      }

//       void without_empty(hash, exceptions) {
//        exceptions = exceptions.map(&:to_sym)
//        hash.select { |k, v| v.present? || v == false || exceptions.include?(k) }
//      }
    };
  }
}
}
}
