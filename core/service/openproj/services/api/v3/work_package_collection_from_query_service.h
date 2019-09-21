#pragma once
namespace openproj {
namespace service {
namespace API {
  namespace V3 {
    class WorkPackageCollectionFromQueryService{
    public:
      // include Utilities::PathHelper
      // include ::API::Utilities::PageSizeHelper

//       WorkPackageCollectionFromQueryService(query, user) {
//        this->query = query
//        this->current_user = user
//      }

//       void call(params = {}, valid_subset: false) {
//        update = UpdateQueryFromV3ParamsService
//                 .new(query, current_user)
//                 .call(params, valid_subset: valid_subset)

//        if ( update.success?) {
//          representer = results_to_representer(params)

//          ServiceResult.new(success: true, result: representer)
//        else
//          update
//        }
//      }

      private:

//       void results_to_representer(params) {
//        collection_representer(query.results.sorted_work_packages,
//                               params: params,
//                               project: query.project,
//                               groups: generate_groups,
//                               sums: generate_total_sums)
//      }

      // attr_accessor :query,
//                    :current_user

       void representer() {
//        ::API::V3::WorkPackages::WorkPackageCollectionRepresenter
      }

//       void calculate_resulting_params(provided_params) {
//        calculate_default_params.merge(provided_params.slice("offset", "pageSize").symbolize_keys).tap { |params|
//          if ( query.manually_sorted?) {
//            params[:offset] = 1
//            params[:pageSize] = Setting.forced_single_page_size
//          else
//            params[:offset] = to_i_or_nil(params[:offset])
//            params[:pageSize] = to_i_or_nil(params[:pageSize])
//          }
//        }
//      }

       void calculate_default_params() {
//        ::API::V3::Queries::QueryParamsRepresenter
//          .new(query)
//          .to_h
      }

       void generate_groups() {
//        return unless query.grouped?

//        results = query.results

//        results.work_package_count_by_group.map { |group, count|
//          sums = if ( query.display_sums?) {
//                   format_query_sums results.all_sums_for_group(group)
//                 }

//          ::API::Decorators::AggregationGroup.new(group, count, query: results.query, sums: sums, current_user: current_user)
//        }
      }

       void generate_total_sums() {
//        return unless query.display_sums?

//        format_query_sums query.results.all_total_sums
      }

//       void format_query_sums(sums) {
//        OpenStruct.new(format_column_keys(sums).merge(available_custom_fields: WorkPackageCustomField.summable.to_a))
//      }

//       void format_column_keys(hash_by_column) {
//        ::Hash[
//          hash_by_column.map { |column, value|
//            match = /cf_(\d+)/.match(column.name.to_s)

//            column_name = if ( match) {
//                            "custom_field_#{match[1]}"
//                          else
//                            column.name.to_s
//                          }

//            [column_name, value]
//          }
//        ]
//      }

//       void collection_representer(work_packages, params:, project:, groups:, sums:) {
//        resulting_params = calculate_resulting_params(params)

//        ::API::V3::WorkPackages::WorkPackageCollectionRepresenter.new(
//          work_packages,
//          self_link(project),
//          project: project,
//          query: resulting_params,
//          page: resulting_params[:offset],
//          per_page: resulting_params[:pageSize],
//          groups: groups,
//          total_sums: sums,
//          embed_schemas: true,
//          current_user: current_user
//        )
//      }

//       void to_i_or_nil(value) {
//        value ? value.to_i : nil
//      }

//       void self_link(project) {
//        if ( project) {
//          api_v3_paths.work_packages_by_project(project.id)
//        else
//          api_v3_paths.work_packages
//        }
//      }

//       void convert_to_v3(attribute) {
//        ::API::Utilities::PropertyNameConverter.from_ar_name(attribute).to_sym
//      }
    };
  }
}
}
}
