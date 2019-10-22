namespace openproj {
namespace helper {
namespace IconsHelper {
  //
  // Create an <i> tag with the given icon class names
  // and make it aria-hidden since screenreaders otherwise
  // output the css `content` of the icon.
//   void op_icon(classnames, title: nil) {
//    title = "title=\"#{h(title)}\"" unless title.nil?
//    %(<i class="#{classnames}" #{title} aria-hidden="true"></i>).html_safe
//  }

  //
  // Icon wrapper with an invisible label
//   void icon_wrapper(icon_class, label) {
//    content = op_icon(icon_class)
//    content << content_tag(:span, label, class: "hidden-for-sighted")
//    content
//  }
}
}
}
