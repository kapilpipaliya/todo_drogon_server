namespace CustomFieldsHelper {
   void custom_fields_tabs() {
//    [
//      { name: 'WorkPackageCustomField', partial: 'custom_fields/tab', label: :label_work_package_plural },
//      { name: 'TimeEntryCustomField', partial: 'custom_fields/tab', label: :label_spent_time },
//      { name: 'ProjectCustomField', partial: 'custom_fields/tab', label: :label_project_plural },
//      { name: 'VersionCustomField', partial: 'custom_fields/tab', label: :label_version_plural },
//      { name: 'UserCustomField', partial: 'custom_fields/tab', label: :label_user_plural },
//      { name: 'GroupCustomField', partial: 'custom_fields/tab', label: :label_group_plural },
//      { name: 'TimeEntryActivityCustomField', partial: 'custom_fields/tab', label: TimeEntryActivity::OptionName },
//      { name: 'IssuePriorityCustomField', partial: 'custom_fields/tab', label: IssuePriority::OptionName }
//     ]
  }

  // Return custom field html tag corresponding to its format
//   void custom_field_tag(name, custom_value) {
//    custom_field = custom_value.custom_field
//    field_name = "#{name}[custom_field_values][#{custom_field.id}]"
//    field_id = "#{name}_custom_field_values_#{custom_field.id}"

//    field_format = OpenProject::CustomFieldFormat.find_by_name(custom_field.field_format)

//    tag = case field_format.try(:edit_as)
//          when 'date'
//            styled_text_field_tag(field_name, custom_value.value, id: field_id, class: '-augmented-datepicker', size: 10)
//          when 'text'
//            styled_text_area_tag(field_name, custom_value.value, id: field_id, rows: 3)
//          when 'bool'
//            hidden_tag = hidden_field_tag(field_name, '0')
//            checkbox_tag = styled_check_box_tag(field_name, '1', custom_value.typed_value, id: field_id)
//            hidden_tag + checkbox_tag
//          when 'list'
//            blank_option = if ( custom_field.is_required? && custom_field.default_value.blank?) {
//                             "<option value=\"\">--- #{l(:actionview_instancetag_blank_option)} ---</option>"
//                           } else if ( custom_field.is_required? && !custom_field.default_value.blank?) {
//                             ''
//                           else
//                             '<option></option>'
//                           }

//            options = blank_option.html_safe + options_for_select(custom_field.possible_values_options(custom_value.customized), custom_value.value)

//            styled_select_tag(field_name, options, id: field_id)
//          else
//            styled_text_field_tag(field_name, custom_value.value, id: field_id)
//    }

//    tag = content_tag :span, tag, lang: custom_field.name_locale

//    custom_value.errors.empty? ?
//      tag :
//      ActionView::Base.wrap_with_error_span(tag, custom_value, 'value')
//  }

  // Return custom field label tag
//   void custom_field_label_tag(name, custom_value) {
//    content_tag 'label', h(custom_value.custom_field.name) +
//      (custom_value.custom_field.is_required? ? content_tag('span', ' *', class: 'required') : ''),
//                for: "#{name}_custom_field_values_#{custom_value.custom_field.id}",
//                class: "form--label #{(custom_value.errors.empty? ? nil : 'error')}",
//                lang: custom_value.custom_field.name_locale
//  }

//   void hidden_custom_field_label_tag(name, custom_value) {
//    content_tag 'label', h(custom_value.custom_field.name) +
//      (custom_value.custom_field.is_required? ? content_tag('span', ' *', class: 'required') : ''),
//                for: "#{name}_custom_field_values_#{custom_value.custom_field.id}",
//                class: "hidden-for-sighted",
//                lang: custom_value.custom_field.name_locale
//  }

//   void blank_custom_field_label_tag(name, custom_field) {
//    content_tag 'label', h(custom_field.name) +
//      (custom_field.is_required? ? content_tag('span', ' *', class: 'required') : ''),
//                for: "#{name}_custom_field_values_#{custom_field.id}",
//                class: 'form--label'
//  }

  // Return custom field tag with its label tag
//   void custom_field_tag_with_label(name, custom_value) {
//    custom_field_label_tag(name, custom_value) + custom_field_tag(name, custom_value)
//  }

//   void custom_field_tag_for_bulk_edit(name, custom_field, project=nil) {
//    field_name = "#{name}[custom_field_values][#{custom_field.id}]"
//    field_id = "#{name}_custom_field_values_#{custom_field.id}"
//    field_format = OpenProject::CustomFieldFormat.find_by_name(custom_field.field_format)
//    case field_format.try(:edit_as)
//    when 'date'
//      styled_text_field_tag(field_name, '', id: field_id, size: 10, class: '-augmented-datepicker')
//    when 'text'
//      styled_text_area_tag(field_name, '', id: field_id, rows: 3, with_text_formatting: true)
//    when 'bool'
//      styled_select_tag(field_name, options_for_select([[l(:label_no_change_option), ''],
//                                                        [l(:general_text_yes), '1'],
//                                                        [l(:general_text_no), '0']]), id: field_id)
//    when 'list'
//      styled_select_tag(field_name, options_for_select([[l(:label_no_change_option), '']] + custom_field.possible_values_options(project)), id: field_id)
//    else
//      styled_text_field_tag(field_name, '', id: field_id)
//    }
//  }

  // Return a string used to display a custom value
//   void show_value(custom_value) {
//    return '' unless custom_value
//    custom_value.formatted_value
//  }

  // Return a string used to display a custom value
//   void format_value(value, custom_field) {
//    custom_value = CustomValue.new(custom_field: custom_field,
//                                   value: value)

//    custom_value.formatted_value
//  }

  // Return an array of custom field formats which can be used in select_tag
//   void custom_field_formats_for_select(custom_field) {
//    OpenProject::CustomFieldFormat
//      .all_for_field(custom_field)
//      .sort_by(&:order)
//      .map { |custom_field_format|
//        [label_for_custom_field_format(custom_field_format.name), custom_field_format.name]
//      }
//  }

//   void label_for_custom_field_format(format_string) {
//    format = OpenProject::CustomFieldFormat.find_by_name(format_string)

//    if ( format) {
//      format.label.is_a?(Proc) ? format.label.call : I18n.t(format.label)
//    }
//  }
}
