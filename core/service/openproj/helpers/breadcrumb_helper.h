namespace BreadcrumbHelper {
   void full_breadcrumb() {
//    if ( show_defaults) {
//      breadcrumb_list(link_to(icon_wrapper('icon2 icon-home', I18n.t(:label_home)), home_path),
//                      link_to_project_ancestors(this->project),
//                      *breadcrumb_paths)
//    else
//      breadcrumb_list(*breadcrumb_paths)
//    }
  }

//   void breadcrumb(*args) {
//    elements = args.flatten
//    elements.any? ? content_tag('p', (args.join(' &#187; ') + ' &#187; ').html_safe, class: 'breadcrumb') : nil
//  }

//   void breadcrumb_list(*args) {
//    elements = args.flatten
//    breadcrumb_elements = [content_tag(:li,
//                                       elements.shift.to_s,
//                                       class: 'first-breadcrumb-element',
//                                       style: 'list-style-image:none;')]

//    breadcrumb_elements += elements.map { |element|
//      if ( element) {
//        css_class = if ( element.try(:include?, 'breadcrumb-project-title')) {
//                      'breadcrumb-project-element '
//                    }
//        content_tag(:li,
//                    h(element.to_s),
//                    class: "#{css_class} icon4 icon-small icon-arrow-right5")
//      }
//    }

//    content_tag(:ul, breadcrumb_elements.join.html_safe, class: 'breadcrumb')
//  }

//   void breadcrumb_paths(*args) {
//    if ( args.nil?) {
//      nil
//    } else if ( args.empty?) {
//      this->breadcrumb_paths ||= [default_breadcrumb]
//    else
//      this->breadcrumb_paths ||= []
//      this->breadcrumb_paths += args
//    }
//  }

   void show_breadcrumb() {
//    if ( !!(defined? show_local_breadcrumb)) {
//      show_local_breadcrumb
//    else
//      false
//    }
  }

   void show_defaults() {
//    if ( !!(defined? show_local_breadcrumb_defaults)) {
//      show_local_breadcrumb_defaults
//    else
//      false
//    }
  }

//  private:

//   void link_to_project_ancestors(project) {
//    if ( project && !project.new_record?) {
//      ancestors = (project.root? ? [] : project.ancestors.visible.to_a)
//      ancestors << project
//      ancestors.map { |p|
//        if ( p == project) {
//          link_to_project(p, { only_path: false }, title: p, class: 'breadcrumb-project-title nocut').html_safe
//        else
//          link_to_project(p, { jump: current_menu_item }, title: p, class: 'breadcrumb-project-title').html_safe
//        }
//      }
//    }
//  }
}
