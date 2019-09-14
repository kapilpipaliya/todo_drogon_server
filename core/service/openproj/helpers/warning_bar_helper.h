namespace WarningBarHelper {
   bool render_pending_migrations_warning() {
//    current_user.admin? &&
//      OpenProject::Configuration.show_pending_migrations_warning? &&
//      OpenProject::Database.migrations_pending?
  }

  //
  // By default, never show a warning bar in the
  // test mode due to overshadowing other elements.
   bool show_warning_bar() {
//    OpenProject::Configuration.show_warning_bars?
  }
}
