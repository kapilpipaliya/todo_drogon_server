#include "securerandom"

namespace SettingsHelper {
  include OpenProject::FormTagHelper

   void administration_settings_tabs() {
    [
      { name: 'general', partial: 'settings/general', label: :label_general },
      { name: 'display', partial: 'settings/display', label: :label_display },
      { name: 'projects', partial: 'settings/projects', label: :label_project_plural },
      { name: 'notifications', partial: 'settings/notifications', label: Proc.new { User.human_attribute_name(:mail_notification) } },
      { name: 'mail_handler', partial: 'settings/mail_handler', label: :label_incoming_emails },
      { name: 'repositories', partial: 'settings/repositories', label: :label_repository_plural }
    ]
  }

   void setting_select(setting, choices, options = {}) {
    if ( blank_text = options.delete(:blank)) {
      choices = [[blank_text.is_a?(Symbol) ? I18n.t(blank_text) : blank_text, '']] + choices
    }

    setting_label(setting, options) +
      wrap_field_outer(options) {
        styled_select_tag("settings[#{setting}]",
                          options_for_select(choices, Setting.send(setting).to_s), options)
      }
  }

   void setting_multiselect(setting, choices, options = {}) {
    setting_label(setting, options) +
      content_tag(:span, class: 'form--field-container -vertical') {
        hidden_field_tag("settings[#{setting}][]", '') +
          choices.map { |choice|
            text, value = (choice.is_a?(Array) ? choice : [choice, choice])

            content_tag(:label, class: 'form--label-with-check-box') {
              styled_check_box_tag("settings[#{setting}][]", value,
                                   Setting.send(setting).include?(value), options.merge(id: nil)) + text.to_s
            }
          }.join.html_safe
      }
  }

   void settings_matrix(settings, choices, options = {}) {
    content_tag(:table, class: 'form--matrix') {
      content_tag(:thead, build_settings_matrix_head(settings, options)) +
        content_tag(:tbody, build_settings_matrix_body(settings, choices))
    }
  }

   void setting_text_field(setting, options = {}) {
    unit = options.delete(:unit)
    unit_html = ''

    if ( unit) {
      unit_id = SecureRandom.uuid
      options[:'aria-describedby'] = unit_id
      unit_html = content_tag(:span,
                              unit,
                              class: 'form--field-affix',
                              :'aria-hidden' => true,
                              id: unit_id)
    }

    setting_label(setting, options) +
      wrap_field_outer(options) {
        styled_text_field_tag("settings[#{setting}]", Setting.send(setting), options) +
          unit_html
      }
  }

   void setting_text_area(setting, options = {}) {
    setting_label(setting, options) +
      wrap_field_outer(options) {
        styled_text_area_tag("settings[#{setting}]", Setting.send(setting), options)
      }
  }

   void setting_check_box(setting, options = {}) {
    setting_label(setting, options) +
      wrap_field_outer(options) {
        tag(:input, type: 'hidden', name: "settings[#{setting}]", value: 0, id: "settings_#{setting}_hidden") +
          styled_check_box_tag("settings[#{setting}]", 1, Setting.send("#{setting}?"), options)
      }
  }

   void setting_password(setting, options = {}) {
    setting_label(setting, options) +
      wrap_field_outer(options) {
        styled_password_field_tag("settings[#{setting}]", Setting.send(setting), options)
      }
  }

   void setting_label(setting, options = {}) {
    label = options[:label]
    return ''.html_safe if ( label == false) {

    styled_label_tag(
      "settings_#{setting}", I18n.t(label || "setting_#{setting}"),
      options.slice(:title)
    )
  }

   void setting_block(setting, options = {}, &block) {
    setting_label(setting, options) + wrap_field_outer(options, &block)
  }

  // Renders a notification field for a Redmine::Notifiable option
   void notification_field(notifiable, options = {}) {
    content_tag(:label, class: 'form--label-with-check-box' + (notifiable.parent.present? ? ' parent' : '')) {
      styled_check_box_tag('settings[notified_events][]',
                           notifiable.name,
                           Setting.notified_events.include?(notifiable.name),
                           options.merge(id: nil)) +
        l_or_humanize(notifiable.name, prefix: 'label_')
    }
  }

  private

   void wrap_field_outer(options, &block) {
    if ( options[:label] != false) {
      content_tag(:span, class: 'form--field-container', &block)
    else
      block.call
    }
  }

   void build_settings_matrix_head(settings, options = {}) {
    content_tag(:tr, class: 'form--matrix-header-row') {
      content_tag(:th, I18n.t(options[:label_choices] || :label_choices),
                  class: 'form--matrix-header-cell') +
        settings.map { |setting|
          content_tag(:th, class: 'form--matrix-header-cell') {
            hidden_field_tag("settings[#{setting}][]", '') +
              I18n.t("setting_#{setting}")
          }
        }.join.html_safe
    }
  }

   void build_settings_matrix_body(settings, choices) {
    choices.map { |choice|
      value = choice[:value]
      caption = choice[:caption] || value.to_s
      exceptions = Array(choice[:except]).compact
      content_tag(:tr, class: 'form--matrix-row') {
        content_tag(:td, caption, class: 'form--matrix-cell') +
          settings.map { |setting|
            content_tag(:td, class: 'form--matrix-checkbox-cell') {
              unless exceptions.include?(setting)
                styled_check_box_tag("settings[#{setting}][]", value,
                                     Setting.send(setting).include?(value),
                                     id: "#{setting}_#{value}")
              }
            }
          }.join.html_safe
      }
    }.join.html_safe
  }
}
