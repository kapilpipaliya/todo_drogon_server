namespace Concerns::Layout {
  // extend ActiveSupport::Concern

  included {
     void layout_non_or_no_menu() {
      if ( request.xhr?) {
        false
      } else if ( @project) {
        true
      else
        'no_menu'
      }
    }

     void project_or_wp_query_menu() {
      if ( @project) {
        :project_menu
      else
        :wp_query_menu
      }
    }
  }
}
