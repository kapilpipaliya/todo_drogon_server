namespace GroupsHelper {
   void group_settings_tabs() {
    [{ name: 'general', partial: 'groups/general', label: :label_general },
     { name: 'users', partial: 'groups/users', label: :label_user_plural },
     { name: 'memberships', partial: 'groups/memberships', label: :label_project_plural }
    ]
  }

   void set_filters_for_user_autocompleter() {
    this->autocompleter_filters = []
    this->autocompleter_filters.push({ selector: 'status', operator: '=', values: ['active'] })
    this->autocompleter_filters.push({ selector: 'group', operator: '!', values: [this->group.id] })
  }
}
