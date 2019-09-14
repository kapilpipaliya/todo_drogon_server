#ifndef TODO_PROJECT_H
#define TODO_PROJECT_H

#include "./account_controller.h"
#include "./activities_controller.h"
#include "./admin_controller.h"
#include "./announcements_controller.h"
#include "./application_controller.h"
#include "./attribute_help_texts_controller.h"
#include "./auth_sources_controller.h"
#include "./authentication_controller.h"
#include "./categories_controller.h"
#include "./colors_controller.h"

#include "./concerns/auth_source_sso.h"
#include "./concerns/authentication_stages.h"
#include "./concerns/layout.h"
#include "./concerns/omniauth_login.h"
#include "./concerns/password_confirmation.h"
#include "./concerns/redirect_after_login.h"
#include "./concerns/user_consent.h"
#include "./concerns/user_invitation.h"
#include "./concerns/user_limits.h"
#include "./concerns/user_password_change.h"

#include "./copy_projects_controller.h"
#include "./custom_actions_controller.h"
#include "./custom_fields_controller.h"
#include "./custom_styles_controller.h"
#include "./enterprises_controller.h"
#include "./enumerations_controller.h"
#include "./forums_controller.h"
#include "./groups_controller.h"
#include "./help_controller.h"
#include "./highlighting_controller.h"
#include "./homescreen_controller.h"
#include "./journals_controller.h"
#include "./ldap_auth_sources_controller.h"
#include "./members_controller.h"
#include "./messages_controller.h"
#include "./my_controller.h"

#include "./news/comments_controller.h"
#include "./news_controller.h"

#include "./oauth/applications_controller.h"
#include "./oauth/auth_base_controller.h"
#include "./oauth/grants_controller.h"

#include "./onboarding_controller.h"
#include "./project_enumerations_controller.h"
#include "./project_settings_controller.h"
#include "./projects_controller.h"
#include "./repositories_controller.h"
#include "./roles_controller.h"
#include "./search_controller.h"
#include "./settings_controller.h"
#include "./statuses_controller.h"
#include "./sys_controller.h"

#include "./time_entries/reports_controller.h"

#include "./timelog_controller.h"
#include "./types_controller.h"

#include "./users/memberships_controller.h"
#include "./users_controller.h"
#include "./users_settings_controller.h"
#include "./versions_controller.h"
#include "./watchers_controller.h"
#include "./wiki_controller.h"
#include "./wiki_menu_items_controller.h"
#include "./workflows_controller.h"

#include "./work_packages/auto_completes_controller.h"
#include "./work_packages/bulk_controller.h"
#include "./work_packages/calendars_controller.h"
#include "./work_packages/moves_controller.h"
#include "./work_packages/reports_controller.h"
#include "./work_packages/settings_controller.h"

#include "./work_packages_controller.h"

namespace todo {

class Project {};

}  // namespace todo
#endif
