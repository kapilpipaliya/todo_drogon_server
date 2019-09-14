namespace UsersHelper {
  // include OpenProject::FormTagHelper

  //
  // @param selected The option to be marked as selected.
  // @param extra [Hash] A hash containing extra entries with a count for each.
  //                     For example: { random: 42 }
//   void users_status_options_for_select(selected, extra: {}) {
//    statuses = User::StatusOptions.user_statuses_with_count extra: extra

//    options = statuses.map { |sym, count|
//      ["#{translate_user_status(sym)} (#{count})", sym]
//    }

//    options_for_select options.sort, selected
//  }

//   void translate_user_status(status_name) {
//    I18n.t(status_name.to_sym, scope: :user)
//  }

  // Format user status, including brute force prevention status
//   void full_user_status(user, include_num_failed_logins = false) {
//    user_status = ''
//    unless [User::STATUSES[:active], User::STATUSES[:builtin]].include?(user.status)
//      user_status = translate_user_status(user.status_name)
//    }
//    brute_force_status = ''
//    if ( user.failed_too_many_recent_login_attempts?) {
//      format = include_num_failed_logins ? :blocked_num_failed_logins : :blocked
//      brute_force_status = I18n.t(format,
//                                  count: user.failed_login_count,
//                                  scope: :user)
//    }

//    both_statuses = user_status + brute_force_status
//    if ( user_status.present? and brute_force_status.present?) {
//      I18n.t(:status_user_and_brute_force,
//             user: user_status,
//             brute_force: brute_force_status,
//             scope: :user)
//    } else if ( not both_statuses.empty?) {
//      both_statuses
//    else
//      I18n.t(:status_active)
//    }
//  }

//  STATUS_CHANGE_ACTIONS = {
//    // status, blocked    => [[button_title, button_name], ...]
//    [:active, false]     => [[:lock, 'lock']],
//    [:active, true]      => [[:reset_failed_logins, 'unlock'],
//                             [:lock, 'lock']],
//    [:locked, false]     => [[:unlock, 'unlock']],
//    [:locked, true]      => [[:unlock_and_reset_failed_logins, 'unlock']],
//    [:registered, false] => [[:activate, 'activate']],
//    [:registered, true]  => [[:activate_and_reset_failed_logins, 'activate']],
//  }

  // Create buttons to lock/unlock a user and reset failed logins
//   void build_change_user_status_action(user) {
//    status = user.status_name.to_sym
//    blocked = !!user.failed_too_many_recent_login_attempts?

//    result = ''.html_safe
//    (STATUS_CHANGE_ACTIONS[[status, blocked]] || []).each { |title, name|
//      result << (yield I18n.t(title, scope: :user), name) + ' '.html_safe
//    }
//    result
//  }

//   void change_user_status_buttons(user) {
//    build_change_user_status_action(user) { |title, name|
//      submit_tag(title, name: name, class: 'button')
//    }
//  }

//   void change_user_status_links(user) {
//    icons = {
//      'unlock' => 'unlocked',
//      'activate' => 'unlocked',
//      'lock' => 'locked'
//    }
//    build_change_user_status_action(user) { |title, name|
//      link_to title,
//              change_status_user_path(user,
//                                      name.to_sym => '1',
//                                      back_url: request.fullpath),
//              method: :post,
//              class: "icon icon-#{icons[name]}"
//    }
//  }

  // Options for the new membership projects combo-box
  //
  // Disables projects the user is already member in
//   void options_for_membership_project_select(user, projects) {
//    options = project_tree_options_for_select(projects, disabled: user.projects.ids.to_set)
//    content_tag('option', "--- #{l(:actionview_instancetag_blank_option)} ---") + options
//  }

//   void user_mail_notification_options(user) {
//    user.valid_notification_options.map { |o| [l(o.last), o.first] }
//  }
}
