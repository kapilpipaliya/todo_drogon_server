namespace openproj {
namespace helper {
namespace WorkPackagesHelper {
  // include AccessibilityHelper
  // extend DeprecatedAlias

  // Displays a link to +work_package+ with its subject.
  // Examples:
  //
  //   link_to_work_package(package)                             // => Defect #6: This is the subject
  //   link_to_work_package(package, all_link: true)          // => Defect #6: This is the subject (everything within the link)
  //   link_to_work_package(package, truncate: 9)             // => Defect #6: This i...
  //   link_to_work_package(package, subject: false)          // => Defect #6
  //   link_to_work_package(package, type: false)             // => #6: This is the subject
  //   link_to_work_package(package, project: true)           // => Foo - Defect #6
  //   link_to_work_package(package, id_only: true)           // => #6
  //   link_to_work_package(package, subject_only: true)      // => This is the subject (as link)
  //   link_to_work_package(package, status: true)            // => #6 New (if #id => true)
//   void link_to_work_package(package, options = {}) {
//    only_path = options.fetch(:only_path) { true }
//    if ( options[:subject_only]) {
//      options.merge!(type: false,
//                     subject: true,
//                     id: false,
//                     all_link: true)
//    } else if ( options[:id_only]) {
//      options.merge!(type: false,
//                     subject: false,
//                     id: true,
//                     all_link: true)
//    else
//      options.reverse_merge!(type: true,
//                             subject: true,
//                             id: true)
//    }

//    parts = { prefix: [],
//              hidden_link: [],
//              link: [],
//              suffix: [],
//              title: [],
//              css_class: ["issue"] }

//    // Prefix part

//    if ( options[:project]) { parts[:prefix] << "#{package.project}" ;}

//    // Link part

//    if ( options[:before_text]) { parts[:link] << h(options[:before_text].to_s) ;}

//    if ( options[:type]) { parts[:link] << h(package.type.to_s) ;}

//    if ( options[:id]) { parts[:link] << "##{h(package.id)}" ;}

//    if ( options[:id] && options[:status] && package.status) { parts[:link] << "#{h(package.status)}" ;}

//    // Hidden link part

//    if ( package.closed?) {
//      parts[:hidden_link] << content_tag(:span,
//                                         I18n.t(:label_closed_work_packages),
//                                         class: "hidden-for-sighted")

//      parts[:css_class] << "closed"
//    }

//    // Suffix part

//    if ( options[:subject]) {
//      subject = if ( options[:subject]) {
//                  subject = package.subject
//                  if ( options[:truncate]) {
//                    subject = truncate(subject, length: options[:truncate])
//                  }

//                  subject
//                }

//      parts[:suffix] << h(subject)
//    }

//    // title part

//    parts[:title] << (options[:title].nil? ? package.subject : options[:title])

//    // combining

//    prefix = parts[:prefix].join(" ")
//    suffix = parts[:suffix].join(" ")
//    link = parts[:link].join(" ").strip
//    hidden_link = parts[:hidden_link].join("")
//    title = parts[:title].join(" ")
//    css_class = parts[:css_class].join(" ")
//    css_class << options[:class].to_s

//    // Determine path or url
//    work_package_link =
//      if ( only_path) {
//        work_package_path(package)
//      else
//        work_package_url(package)
//      }

//    text = if ( options[:all_link]) {
//             link_text = [prefix, link].reject(&:empty?).join(" - ")
//             link_text = [link_text, suffix].reject(&:empty?).join(": ")
//             link_text = [hidden_link, link_text].reject(&:empty?).join("")

//             link_to(link_text.html_safe,
//                     work_package_link,
//                     title: title,
//                     class: css_class)
//           else
//             link_text = [hidden_link, link].reject(&:empty?).join("")

//             html_link = link_to(link_text.html_safe,
//                                 work_package_link,
//                                 title: title,
//                                 class: css_class)

//             [[prefix, html_link].reject(&:empty?).join(" - "),
//              suffix].reject(&:empty?).join(": ")
//            }.html_safe
//  }

//   void work_package_list(work_packages, &_block) {
//    ancestors = []
//    work_packages.each { |work_package|
//      while (ancestors.any? && !work_package.is_descendant_of?(ancestors.last)){
//        ancestors.pop
//      }
//      yield work_package, ancestors.size
//      ancestors << work_package unless work_package.leaf?
//    }
//  }

   void send_notification_option(bool checked = false) {
//    content_tag(:label, for: "send_notification", class: "form--label-with-check-box") {
//      (content_tag "span", class: "form--check-box-container" {
//        boxes = hidden_field_tag("send_notification", "0", id: nil)

//        boxes += check_box_tag("send_notification",
//                               "1",
//                               checked,
//                               class: "form--check-box")
//        boxes
//      }) + l(:label_notify_member_plural)
//    }
  }

  // Returns a string of css classes that apply to the issue
//   void work_package_css_classes(work_package) {
//    // TODO: remove issue once css is cleaned of it
//    s = "issue work_package preview-trigger".html_safe
//    if ( work_package.status) { s << " status-#{work_package.status.position}" ;}
//    if ( work_package.priority) { s << " priority-#{work_package.priority.position}" ;}
//    if ( work_package.closed?) { s << " closed" ;}
//    if ( work_package.overdue?) { s << " overdue" ;}
//    if ( work_package.child?) { s << " child" ;}
//    s << " parent" unless work_package.leaf?
//    if ( User.current.logged? && work_package.author_id == User.current.id) { s << " created-by-me" ;}
//    if ( User.current.logged? && work_package.assigned_to_id == User.current.id) { s << " assigned-to-me" ;}
//    s
//  }

//   void work_package_associations_to_address(associated) {
//    ret = "".html_safe

//    ret += content_tag(:p, l(:text_destroy_with_associated), class: "bold")

//    ret += content_tag(:ul) {
//      associated.inject("".html_safe) { |list, associated_class|
//        list += content_tag(:li, associated_class.model_name.human, class: "decorated")

//        list
//      }
//    }

//    ret
//  }

//  private:

//   void truncated_work_package_description(work_package, lines = 3) {
//    description_lines = work_package.description.to_s.lines.to_a[0, lines]

//    if ( description_lines[lines - 1] && work_package.description.to_s.lines.to_a.size > lines) {
//      description_lines[lines - 1].strip!

//      while (!description_lines[lines - 1].end_with?("...")){
//        description_lines[lines - 1] = description_lines[lines - 1] + "."
//      }
//    }

//    if ( work_package.description.blank?) {
//      empty_element_tag
//    else
//      ::OpenProject::TextFormatting::Renderer.format_text(
//        description_lines.join(""),
//        object: work_package,
//        attribute: :description,
//        no_nesting: true
//      )
//    }
//  }

//   void info_user_attributes(work_package) {
//    responsible = if ( work_package.responsible_id.present?) {
//                    "<span class="label">#{WorkPackage.human_attribute_name(:responsible)}:</span> " +
//                    "#{h(work_package.responsible.name)}"
//                  }

//    assignee = if ( work_package.assigned_to_id.present?) {
//                 "<span class="label">#{WorkPackage.human_attribute_name(:assigned_to)}:</span> " +
//                 "#{h(work_package.assigned_to.name)}"
//               }

//    [responsible, assignee].compact.join("<br>").html_safe
//  }
}
}
}
