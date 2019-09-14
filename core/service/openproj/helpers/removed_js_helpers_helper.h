// Contains tag helpers still existing in the OP code but already
// removed from rails. Please consider removing the occurences in
// the code rather than adding additional helpers here.

namespace RemovedJsHelpersHelper {
  // removed in rails 4.1
//   void link_to_function(content, function, html_options = {}) {
//    id = html_options.delete(:id) { "link-to-function-#{SecureRandom.uuid}" }
//    csp_onclick(function, "##{id}")

//    content_tag(:a, content, html_options.merge(id: id, href: ''))
//  }

  //
  // Execute the callback on click
//   void csp_onclick(callback_str, selector) {
//    content_for(:additional_js_dom_ready) {
//      "jQuery('#{selector}').click(function() { #{callback_str}; return false; });\n".html_safe
//    }
//  }
}
