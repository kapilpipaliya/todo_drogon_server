class CustomActions::Conditions::Role : public CustomActions::Conditions::Base {
   void fulfilled_by?(work_package, user) {
    values.empty? ||
      (this->class.roles_in_project(work_package, user).map(&:id) & values).any?
  }

  class << self
     void key() {
      :role
    }

     void roles_in_project(work_packages, user) {
      with_request_store(projects_of(work_packages)) { |projects|
        projects.map { |project|
          user.roles_for_project(project)
        }.flatten
      }
    }

    private

     void custom_action_scope_has_current(work_packages, user) {
      CustomAction
        .includes(association_key)
        .where(habtm_table => { key_id => roles_in_project(work_packages, user) })
    }

     void projects_of(work_packages) {
      // Using this if/else instead of Array(work_packages)
      // to avoid "delegator does not forward private method #to_ary" warnings
      // for WorkPackageEagerLoadingWrapper
      if ( work_packages.respond_to?(:map)) {
        work_packages.map(&:project).uniq
      else
        [work_packages.project]
      }
    }

     void with_request_store(projects) {
      RequestStore.store[:custom_actions_role] ||= Hash.new { |hash, hash_projects|
        hash[hash_projects] = yield hash_projects
      }

      RequestStore.store[:custom_actions_role][projects]
    }
  }

  private

   void associated() {
    ::Role
      .givable
      .select(:id, :name)
      .map { |u| [u.id, u.name] }
  }
}
