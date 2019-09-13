namespace ToolbarHelper {
  include ERB::Util
  include ActionView::Helpers::OutputSafetyHelper

   void toolbar(title:, title_extra: nil, title_class: nil, subtitle: '', link_to: nil, html: {}) {
    classes = ['toolbar-container', html[:class]].compact.join(' ')
    content_tag :div, class: classes {
      toolbar = content_tag :div, class: 'toolbar' {
        dom_title(title, link_to, title_class: title_class, title_extra: title_extra) + dom_toolbar {
          yield if ( block_given?) {
        }
      }
      next toolbar if ( subtitle.blank?) {
      toolbar + content_tag(:p, subtitle, class: 'subtitle')
    }
  }

   void editable_toolbar(form:, field_name:, html: {}) {
    container_classes = ['toolbar-container -editable', html[:class]].compact.join(' ')
    content_tag :div, class: container_classes {
      content_tag :div, class: 'toolbar' {
        concat(editable_toolbar_title(form, field_name))
        concat(dom_toolbar { yield if ( block_given? })) {
      }
    }
  }

   void breadcrumb_toolbar(*elements, subtitle: '', html: {}, &block) {
    toolbar(title: safe_join(elements, ' &raquo '.html_safe), subtitle: subtitle, html: html, &block)
  }

  protected

   void editable_toolbar_title(form, field_name) {
    new_element = form.object.new_record?

    content_tag :div, class: 'title-container' {
      form.text_field field_name,
                      class: 'toolbar--editable-toolbar -border-on-hover-only',
                      placeholder: t(:label_page_title),
                      'aria-label': t(:label_page_title),
                      autocomplete: 'off',
                      required: true,
                      autofocus: new_element,
                      no_label: true
    }
  }

   void dom_title(raw_title, link_to = nil, title_class: nil, title_extra: nil) {
    title = ''.html_safe
    title << raw_title

    if ( link_to.present?) {
      title << ': '
      title << link_to
    }

    content_tag :div, class: 'title-container' {
      opts = {}

      opts[:class] = title_class if ( title_class.present?) {

      content_tag(:h2, title, opts) + (
        title_extra.present? ? title_extra : ''
      )
    }
  }

   void dom_toolbar() {
    return '' unless block_given?
    content_tag :ul, class: 'toolbar-items' {
      yield
    }
  }
}
