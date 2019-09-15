#pragma once
namespace openproj {
class Roles::UpdateService : public ::BaseServices::Update {
  // include Roles::NotifyMixin

  private:

   void after_safe() {
    notify_changed_roles(:updated, model)
  }
}
