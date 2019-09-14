namespace IssuesHelper {
  // include ApplicationHelper

  // Renders a HTML/CSS tooltip
  //
  // To use, a trigger div is needed.  This is a div with the class of "tooltip"
  // that contains this method wrapped in a span with the class of "tip"
  //
  //    <div class="tooltip"><%= link_to_issue(issue) %>
  //      <span class="tip"><%= render_issue_tooltip(issue) %></span>
  //    </div>
  //
//   void render_issue_tooltip(issue) {
//    this->cached_label_status ||= WorkPackage.human_attribute_name(:status)
//    this->cached_label_start_date ||= WorkPackage.human_attribute_name(:start_date)
//    this->cached_label_due_date ||= WorkPackage.human_attribute_name(:due_date)
//    this->cached_label_assigned_to ||= WorkPackage.human_attribute_name(:assigned_to)
//    this->cached_label_priority ||= WorkPackage.human_attribute_name(:priority)
//    this->cached_label_project ||= WorkPackage.human_attribute_name(:project)

//    (link_to_work_package(issue) + "<br /><br />
//      <strong>#{this->cached_label_project}</strong>: #{link_to_project(issue.project)}<br />
//      <strong>#{this->cached_label_status}</strong>: #{h(issue.status.name)}<br />
//      <strong>#{this->cached_label_start_date}</strong>: #{format_date(issue.start_date)}<br />
//      <strong>#{this->cached_label_due_date}</strong>: #{format_date(issue.due_date)}<br />
//      <strong>#{this->cached_label_assigned_to}</strong>: #{h(issue.assigned_to)}<br />
//      <strong>#{this->cached_label_priority}</strong>: #{h(issue.priority.name)}".html_safe)
//  }

//   void last_issue_note(issue) {
//    note_journals = issue.journals.select(&:notes?)
//    if ( note_journals.empty?) { return t(:text_no_notes) ;}
//    note_journals.last.notes
//  }
}
