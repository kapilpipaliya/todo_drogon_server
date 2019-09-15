namespace openproj {
namespace AccessibilityHelper {
//   void you_are_here_info(condition = true, disabled = nil) {
//    if ( condition && !disabled) {
//      "<span style = 'display: block' class = 'position-label hidden-for-sighted'>#{l(:description_current_position)}</span>".html_safe
//    } else if ( condition && disabled) {
//      "<span style = 'display: none' class = 'position-label hidden-for-sighted'>#{l(:description_current_position)}</span>".html_safe
//    else
//      ''
//    }
//  }

   void empty_element_tag() {
//    this->empty_element_tag ||= ApplicationController.new.render_to_string(partial: 'accessibility/empty_element_tag').html_safe
  }

  // Returns the locale :en for the given menu item if ( the user locale is) {
  // different but equals the English translation
  //
  // Returns nil if ( user locale is :en (English) or no translation is given,) {
  // thus, assumes English to be the default language. Returns :en iff a
  // translation exists and the translation equals the English one.
//   void menu_item_locale(menu_item) {
//    if ( english_locale_set?) { return nil ;}

//    caption_content = menu_item.instance_variable_get(:this->caption)
//    locale_label = caption_content.is_a?(Symbol) ? caption_content : :"label_#{menu_item.name.to_s}"

//    (!locale_exists?(locale_label) || equals_english_locale(locale_label)) ? :en : nil
//  }

//  private:

//   void locale_exists?(key, locale = I18n.locale) {
//    I18n.t(key, locale: locale, raise: true) rescue false
//  }

   bool english_locale_set() {
//    I18n.locale == :en
  }

//   void equals_english_locale(key) {
//    key.is_a?(Symbol) ? (I18n.t(key) == I18n.t(key, locale: :en)) : false
//  }
}
}
