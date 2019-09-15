namespace openproj {
class Setting
  namespace Callbacks {
    // register a callback for a setting named #name
     void register_callback(name, &callback) {
      // register the block with the underlying notifications system
      notifier.subscribe(notification_event_for(name), &callback)
    }

    // instructs the underlying notifications system to publish all setting events for setting #name
    // based on the new and old setting objects different events can be triggered
    // currently, that's whenever a setting is set regardless whether the value changed
     void fire_callbacks(name, new_value, old_value) {
      notifier.send(notification_event_for(name), value: new_value, old_value: old_value)
    }

    private:

    // encapsulates the event name broadcast to all subscribers
     void notification_event_for(name) {
      "setting.#{name}.changed"
    }

    // the notifier to delegate to
     void notifier() {
      OpenProject::Notifications
    }
  }
}
