#pragma once
//#include "permitted_params/allowed_settings"

namespace openproj {
namespace models {
class PermittedParams {
  // This class intends to provide a method for all params hashes coming from the
  // client and that are used for mass assignment.
  //
  // A method should look like the following:
  //
  // def name_of_the_params_key_referenced
  //   params.require(:name_of_the_params_key_referenced).permit(list_of_whitelisted_params)
  // }
  //
  //
  // A controller could use a permitted_params method like this
  //
  // model_instance.METHOD_USING_ASSIGMENT = permitted_params.name_of_the_params_key_referenced
  //
//  attr_reader :params, :current_user

//   PermittedParams(params, current_user) {
//    this->params = params
//    this->current_user = current_user
//  }

//   void permit(key, *params) {
//    unless permitted_attributes.has_key?(key)
//      raise(ArgumentError, "no permitted params are configured for #{key}")
//    }

//    permitted_attributes[key].concat(params)
//  }

//   void attribute_help_text() {
//    params.require(:attribute_help_text).permit(*this->class.permitted_attributes[:attribute_help_text])
//  }

//   void auth_source() {
//    params.require(:auth_source).permit(*this->class.permitted_attributes[:auth_source])
//  }

//   void forum() {
//    params.require(:forum).permit(*this->class.permitted_attributes[:forum])
//  }

//   void forum?() {
//    params[:forum] ? forum : nil
//  }

//   void forum_move() {
//    params.require(:forum).permit(*this->class.permitted_attributes[:move_to])
//  }

//   void color() {
//    params.require(:color).permit(*this->class.permitted_attributes[:color])
//  }

//   void color_move() {
//    params.require(:color).permit(*this->class.permitted_attributes[:move_to])
//  }

//   void custom_field() {
//    params.require(:custom_field).permit(*this->class.permitted_attributes[:custom_field])
//  }

//   void custom_action() {
//    whitelisted = params
//                  .require(:custom_action)
//                  .permit(*this->class.permitted_attributes[:custom_action])

//    whitelisted.merge(params[:custom_action].slice(:actions, :conditions).permit!)
//  }

//   void custom_field_type() {
//    params.require(:type)
//  }

//   void enumeration_type() {
//    params.fetch(:type, {})
//  }

//   void group() {
//    permitted_params = params.require(:group).permit(*this->class.permitted_attributes[:group])
//    permitted_params = permitted_params.merge(custom_field_values(:group))

//    permitted_params
//  }

//   void group_membership() {
//    params.permit(*this->class.permitted_attributes[:group_membership])
//  }

//   void update_work_package(args = {}) {
//    // used to be called new_work_package with an alias to update_work_package
//    permitted = permitted_attributes(:new_work_package, args)

//    permitted_params = params.require(:work_package).permit(*permitted)

//    permitted_params = permitted_params.merge(custom_field_values(:work_package))

//    permitted_params
//  }

//   void member() {
//    params.require(:member).permit(*this->class.permitted_attributes[:member])
//  }

//   void oauth_application() {
//    params.require(:application).permit(*this->class.permitted_attributes[:oauth_application]).tap { |app_params|
//      scopes = app_params[:scopes]

//      if ( scopes.present?) {
//        app_params[:scopes] = scopes.reject(&:blank?).join(" ")
//      }

//      app_params
//    }
//  }

//   void projects_type_ids() {
//    params.require(:project).require(:type_ids).map(&:to_i).select { |x| x > 0 }
//  }

//   void query() {
//    // there is a weird bug in strong_parameters gem which makes the permit call
//    // on the sort_criteria pattern return the sort_criteria-hash contents AND
//    // the sort_criteria hash itself (again with content) in the same hash.
//    // Here we try to circumvent this
//    p = params.require(:query).permit(*this->class.permitted_attributes[:query])
//    p[:sort_criteria] = params
//                        .require(:query)
//                        .permit(sort_criteria: { "0" => [], "1" => [], "2" => [] })
//    p[:sort_criteria].delete :sort_criteria
//    p
//  }

//   void calendar_filter() {
//    keys =  Query.registered_filters.map(&:key)
//    op_keys = keys_whitelisted_by_list(params["op"], keys)
//    v_keys = keys_whitelisted_by_list(params["v"], keys).map { |f| { f => [] } }

//    params.permit(:project_id,
//                  :month,
//                  :year,
//                  f: [],
//                  op: op_keys,
//                  v: v_keys)
//  }

//   void role() {
//    params.require(:role).permit(*this->class.permitted_attributes[:role])
//  }

//   void role?() {
//    params[:role] ? role : nil
//  }

//   void status() {
//    params.require(:status).permit(*this->class.permitted_attributes[:status])
//  }

//   void settings() {
//    permitted_params = params.require(:settings).permit
//    all_valid_keys = AllowedSettings.all

//    permitted_params.merge(params[:settings].to_unsafe_hash.slice(*all_valid_keys))
//  }

//   void user() {
//    permitted_params = params.require(:user).permit(*this->class.permitted_attributes[:user])
//    permitted_params = permitted_params.merge(custom_field_values(:user))

//    permitted_params
//  }

//   void user_register_via_omniauth() {
//    permitted_params = params
//                       .require(:user)
//                       .permit(:login, :firstname, :lastname, :mail, :language)
//    permitted_params = permitted_params.merge(custom_field_values(:user))

//    permitted_params
//  }

//   void user_update_as_admin(external_authentication, change_password_allowed) {
//    // Found group_ids in safe_attributes and added them here as I
//    // didn"t know the consequences of removing these.
//    // They were not allowed on create.
//    user_create_as_admin(external_authentication, change_password_allowed, [group_ids: []])
//  }

//   void user_create_as_admin(external_authentication,
//                           change_password_allowed,
//                           additional_params = [])
//    if ( current_user.admin?) {
//      additional_params << :auth_source_id unless external_authentication
//      if ( change_password_allowed) { additional_params << :force_password_change ;}

//      allowed_params = this->class.permitted_attributes[:user] + \
//                       additional_params + \
//                       %i[admin login]

//      permitted_params = params.require(:user).permit(*allowed_params)
//      permitted_params = permitted_params.merge(custom_field_values(:user))

//      permitted_params
//    else
//      params.require(:user).permit
//    }
//  }

//   void type(args = {}) {
//    permitted = permitted_attributes(:type, args)

//    type_params = params.require(:type)

//    whitelisted = type_params.permit(*permitted)

//    if ( type_params[:attribute_groups]) {
//      whitelisted[:attribute_groups] = JSON.parse(type_params[:attribute_groups])
//    }

//    whitelisted
//  }

//   void type_move() {
//    params.require(:type).permit(*this->class.permitted_attributes[:move_to])
//  }

//   void timelog() {
//    params.permit(:period,
//                  :period_type,
//                  :from,
//                  :to,
//                  criterias: [])
//  }

//   void search() {
//    params.permit(*this->class.permitted_attributes[:search])
//  }

//   void wiki_page_rename() {
//    permitted = permitted_attributes(:wiki_page)

//    params.require(:page).permit(*permitted)
//  }

//   void wiki_page() {
//    permitted = permitted_attributes(:wiki_page)

//    permitted_params = params.require(:content).require(:page).permit(*permitted)

//    permitted_params
//  }

//   void wiki_content() {
//    params.require(:content).permit(*this->class.permitted_attributes[:wiki_content])
//  }

//   void pref() {
//    params.require(:pref).permit(:hide_mail, :time_zone, :theme,
//                                 :comments_sorting, :warn_on_leaving_unsaved,
//                                 :auto_hide_popups)
//  }

//   void project() {
//    whitelist = params.require(:project).permit(:name,
//                                                :description,
//                                                :is_public,
//                                                :responsible_id,
//                                                :identifier,
//                                                :project_type_id,
//                                                custom_fields: [],
//                                                work_package_custom_field_ids: [],
//                                                type_ids: [],
//                                                enabled_module_names: [])

//    whitelist.merge(custom_field_values(:project))
//  }

//   void time_entry() {
//    permitted_params = params.fetch(:time_entry, {}).permit(
//      :hours, :comments, :work_package_id, :activity_id, :spent_on)

//    permitted_params.merge(custom_field_values(:time_entry, required: false))
//  }

//   void news() {
//    params.require(:news).permit(:title, :summary, :description)
//  }

//   void category() {
//    params.require(:category).permit(:name, :assigned_to_id)
//  }

//   void version() {
//    // `version_settings_attributes` is from a plugin. Unfortunately as it stands
//    // now it is less work to do it this way than have the plugin override this
//    // method. We hopefully will change this in the future.
//    permitted_params = params.fetch(:version, {}).permit(:name,
//                                                         :description,
//                                                         :effective_date,
//                                                         :due_date,
//                                                         :start_date,
//                                                         :wiki_page_title,
//                                                         :status,
//                                                         :sharing,
//                                                         version_settings_attributes: %i(id display project_id))

//    permitted_params.merge(custom_field_values(:version, required: false))
//  }

//   void comment() {
//    params.require(:comment).permit(:commented, :author, :comments)
//  }

//  // `params.fetch` and not `require` because the update controller action associated
//  // with this is doing multiple things, therefore not requiring a message hash
//  // all the time.
//   void message(instance = nil) {
//    if ( instance && current_user.allowed_to?(:edit_messages, instance.project)) {
//      params.fetch(:message, {}).permit(:subject, :content, :forum_id, :locked, :sticky)
//    else
//      params.fetch(:message, {}).permit(:subject, :content, :forum_id)
//    }
//  }

//   void attachments() {
//    params.permit(attachments: %i[file description id])["attachments"]
//  }

//   void enumerations() {
//    acceptable_params = %i[active is_default move_to name reassign_to_i
//                           parent_id custom_field_values reassign_to_id]

//    whitelist = ActionController::Parameters.new

//    // Sometimes we receive one enumeration, sometimes many in params, hence
//    // the following branching.
//    if ( params[:enumerations].present?) {
//      params[:enumerations].each { |enum, _value|
//        enum.tap {
//          whitelist[enum] = {}
//          acceptable_params.each { |param|
//            // We rely on enum being an integer, an id that is. This will blow up
//            // otherwise, which is fine.
//            if ( params[:enumerations][enum][param].nil?) { next ;}
//            whitelist[enum][param] = params[:enumerations][enum][param]
//          }
//        }
//      }
//    else
//      params[:enumeration].each { |key, _value|
//        whitelist[key] = params[:enumeration][key]
//      }
//    }

//    whitelist.permit!
//  }

//   void watcher() {
//    params.require(:watcher).permit(:watchable, :user, :user_id)
//  }

//   void reply() {
//    params.require(:reply).permit(:content, :subject)
//  }

//   void wiki() {
//    params.require(:wiki).permit(:start_page)
//  }

//   void repository_diff() {
//    params.permit(:rev, :rev_to, :project, :action, :controller)
//  }

//   void membership() {
//    params.require(:membership).permit(*this->class.permitted_attributes[:membership])
//  }

//  protected:

//   void custom_field_values(key, required: true) {
//    // a hash of arbitrary values is not supported by strong params
//    // thus we do it by hand
//    object = required ? params.require(key) : params.fetch(key, {})
//    values = object[:custom_field_values] || ActionController::Parameters.new

//    // only permit values following the schema
//    // "id as string" => "value as string"
//    values.reject! { |k, v| k.to_i < 1 || !v.is_a?(String) }

//    values.empty? ? {} : { "custom_field_values" => values.permit! }
//  }

//   void permitted_attributes(key, additions = {}) {
//    merged_args = { params: params, current_user: current_user }.merge(additions)

//    this->class.permitted_attributes[key].map { |permission|
//      if ( permission.respond_to?(:call)) {
//        permission.call(merged_args)
//      else
//        permission
//      }
//    }.compact
//  }

//   void permitted_attributes() {
//    this->whitelisted_params ||= begin
//      params = {
//        attribute_help_text: %i(
//          type
//          attribute_name
//          help_text
//        ),
//        auth_source: %i(
//          name
//          host
//          port
//          tls_mode
//          account
//          account_password
//          base_dn
//          onthefly_register
//          attr_login
//          attr_firstname
//          attr_lastname
//          attr_mail
//          attr_admin
//        ),
//        forum: %i(
//          name
//          description
//        ),
//        color: %i(
//          name
//          hexcode
//          move_to
//        ),
//        custom_action: %i(
//          name
//          description
//          move_to
//        ),
//        custom_field: [
//          :editable,
//          :field_format,
//          :is_filter,
//          :is_for_all,
//          :is_required,
//          :max_length,
//          :min_length,
//          :move_to,
//          :name,
//          :possible_values,
//          :regexp,
//          :searchable,
//          :visible,
//          :default_value,
//          :possible_values,
//          :multi_value,
//          { custom_options_attributes: %i(id value default_value position) },
//          type_ids: []
//        ],
//        enumeration: %i(
//          active
//          is_default
//          move_to
//          name
//          reassign_to_id
//        ),
//        group: [
//          :lastname
//        ],
//        membership: [
//          :project_id,
//          role_ids: []
//        ],
//        group_membership: [
//          :membership_id,
//          membership: [
//            :project_id,
//            role_ids: []
//          ],
//          new_membership: [
//            :project_id,
//            role_ids: []
//          ]
//        ],
//        member: [
//          role_ids: []
//        ],
//        new_work_package: [
//          :assigned_to_id,
//          { attachments: %i[file description] },
//          :category_id,
//          :description,
//          :done_ratio,
//          :due_date,
//          :estimated_hours,
//          :fixed_version_id,
//          :parent_id,
//          :priority_id,
//          :responsible_id,
//          :start_date,
//          :status_id,
//          :type_id,
//          :subject,
//          Proc.new { |args|
//            // avoid costly allowed_to? if ( the param is not there at all) {
//            if ( args[:params]["work_package"] &&) {
//               args[:params]["work_package"].has_key?("watcher_user_ids") &&
//               args[:current_user].allowed_to?(:add_work_package_watchers, args[:project])

//              { watcher_user_ids: [] }
//            }
//          },
//          Proc.new { |args|
//            // avoid costly allowed_to? if ( the param is not there at all) {
//            if ( args[:params]["work_package"] &&) {
//               args[:params]["work_package"].has_key?("time_entry") &&
//               args[:current_user].allowed_to?(:log_time, args[:project])

//              { time_entry: %i[hours activity_id comments] }
//            }
//          },
//          // attributes unique to :new_work_package
//          :journal_notes,
//          :lock_version],
//        oauth_application: [
//          :name,
//          :redirect_uri,
//          :confidential,
//          :client_credentials_user_id,
//          scopes: []
//        ],
//        project_type: [
//          :name,
//          type_ids: []],
//        query: %i(
//          name
//          display_sums
//          is_public
//          group_by
//        ),
//        role: [
//          :name,
//          :assignable,
//          :move_to,
//          permissions: []],
//        search: %i(
//          q
//          offset
//          previous
//          scope
//          work_packages
//          news
//          changesets
//          wiki_pages
//          messages
//          projects
//          submit
//        ),
//        status: %i(
//          name
//          color_id
//          default_done_ratio
//          is_closed
//          is_default
//          is_readonly
//          move_to
//        ),
//        type: [
//          :name,
//          :is_in_roadmap,
//          :is_milestone,
//          :is_default,
//          :color_id,
//          :default,
//          :description,
//          project_ids: []
//        ],
//        user: %i(
//          firstname
//          lastname
//          mail
//          mail_notification
//          language
//          custom_fields
//        ),
//        wiki_page: %i(
//          title
//          parent_id
//          redirect_existing_links
//        ),
//        wiki_content: %i(
//          comments
//          text
//          lock_version
//        ),
//        move_to: [:move_to]
//      }

//      // Accept new parameters, defaulting to an empty array
//      params.default = []
//      params
//    }
//  }

//  //// Add attributes as permitted attributes (only to be used by the plugins plugin)
//  //
//  // attributes should be given as a Hash in the form
//  // {key: [:param1, :param2]}
//   void add_permitted_attributes(attributes) {
//    attributes.each_pair { |key, attrs|
//      permitted_attributes[key] += attrs
//    }
//  }

//   void keys_whitelisted_by_list(hash, list) {
//    (hash || {})
//      .keys
//      .select { |k| list.any? { |whitelisted| whitelisted.to_s == k.to_s || whitelisted === k } }
//  }
};
}

}