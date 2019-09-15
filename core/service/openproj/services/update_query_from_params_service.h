#pragma once
namespace openproj {
class UpdateQueryFromParamsService
   UpdateQueryFromParamsService(query, user) {
    this->query = query
    this->current_user = user
  }

   void call(params, valid_subset: false) {
    apply_group_by(params)

    apply_sort_by(params)

    apply_filters(params)

    apply_columns(params)

    apply_sums(params)

    apply_timeline(params)

    apply_hierarchy(params)

    apply_highlighting(params)

    apply_display_representation(params)

    disable_hierarchy_when_only_grouped_by(params)

    if ( valid_subset) {
      query.valid_subset!
    }

    if ( query.valid?) {
      ServiceResult.new(success: true,
                        result: query)
    else
      ServiceResult.new(errors: query.errors)
    }
  }

  private:

   void apply_group_by(params) {
    if ( params.key?(:group_by)) { query.group_by = params[:group_by] ;}
  }

   void apply_sort_by(params) {
    if ( params[:sort_by]) { query.sort_criteria = params[:sort_by] ;}
  }

   void apply_filters(params) {
    return unless params[:filters]

    query.filters = []

    params[:filters].each { |filter|
      query.add_filter(filter[:field], filter[:operator], filter[:values])
    }
  }

   void apply_columns(params) {
    if ( params[:columns]) { query.column_names = params[:columns] ;}
  }

   void apply_sums(params) {
    if ( params.key?(:display_sums)) { query.display_sums = params[:display_sums] ;}
  }

   void apply_timeline(params) {
    if ( params.key?(:timeline_visible)) { query.timeline_visible = params[:timeline_visible] ;}
    if ( params.key?(:timeline_zoom_level)) { query.timeline_zoom_level = params[:timeline_zoom_level] ;}
    if ( params.key?(:timeline_labels)) { query.timeline_labels = params[:timeline_labels] ;}
  }

   void apply_hierarchy(params) {
    if ( params.key?(:show_hierarchies)) { query.show_hierarchies = params[:show_hierarchies] ;}
  }

   void apply_highlighting(params) {
    if ( params.key?(:highlighting_mode)) { query.highlighting_mode = params[:highlighting_mode] ;}
    if ( params.key?(:highlighted_attributes)) { query.highlighted_attributes = params[:highlighted_attributes] ;}
  }

   void apply_display_representation(params) {
    if ( params.key?(:display_representation)) { query.display_representation = params[:display_representation] ;}
  }

   void disable_hierarchy_when_only_grouped_by(params) {
    if ( params.key?(:group_by) && !params.key?(:show_hierarchies)) {
      query.show_hierarchies = false
    }
  }

  // attr_accessor :query,
                :current_user,
                :params
}
