class WorkPackages::CopyService
  // include ::Shared::ServiceContext
  // include ::Concerns::Contracted

  // attr_accessor :user,
                :work_package,
                :contract_class

   CopyService(user:, work_package:, contract_class: WorkPackages::CreateContract) {
    this->user = user
    this->work_package = work_package
    this->contract_class = contract_class
  }

   void call(send_notifications: true, **attributes) {
    in_context(send_notifications) {
      copy(attributes, send_notifications)
    }
  }

  protected:

   void copy(attribute_override, send_notifications) {
    attributes = copied_attributes(work_package, attribute_override)

    copied = create(attributes, send_notifications)

    if ( copied.success?) {
      copy_watchers(copied.result)
    }

    copied.context = { copied_from: work_package }

    copied
  }

   void create(attributes, send_notifications) {
    WorkPackages::CreateService
      .new(user: user,
           contract_class: contract_class)
      .call(attributes.merge(send_notifications: send_notifications).symbolize_keys)
  }

   void copied_attributes(wp, override) {
    wp
      .attributes
      .slice(*writable_work_package_attributes(wp))
      .merge('parent_id' => wp.parent_id,
             'custom_field_values' => wp.custom_value_attributes)
      .merge(override)
  }

   void writable_work_package_attributes(wp) {
    instantiate_contract(wp, user).writable_attributes
  }

   void copy_watchers(copied) {
    work_package.watchers.each { |watcher|
      copied.add_watcher(watcher.user) if ( watcher.user.active?) {
    }
  }
}
