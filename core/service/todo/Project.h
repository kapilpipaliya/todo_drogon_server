#ifndef TODO_PROJECT_H
#define TODO_PROJECT_H

#include "core/service/openproj/controllers/account_controller.h"
#include "core/service/openproj/controllers/activities_controller.h"
#include "core/service/openproj/controllers/admin_controller.h"
#include "core/service/openproj/controllers/announcements_controller.h"
#include "core/service/openproj/controllers/application_controller.h"
#include "core/service/openproj/controllers/attribute_help_texts_controller.h"
#include "core/service/openproj/controllers/auth_sources_controller.h"
#include "core/service/openproj/controllers/authentication_controller.h"
#include "core/service/openproj/controllers/categories_controller.h"
#include "core/service/openproj/controllers/colors_controller.h"

#include "core/service/openproj/controllers/concerns/auth_source_sso.h"
#include "core/service/openproj/controllers/concerns/authentication_stages.h"
#include "core/service/openproj/controllers/concerns/layout.h"
#include "core/service/openproj/controllers/concerns/omniauth_login.h"
#include "core/service/openproj/controllers/concerns/password_confirmation.h"
#include "core/service/openproj/controllers/concerns/redirect_after_login.h"
#include "core/service/openproj/controllers/concerns/user_consent.h"
#include "core/service/openproj/controllers/concerns/user_invitation.h"
#include "core/service/openproj/controllers/concerns/user_limits.h"
#include "core/service/openproj/controllers/concerns/user_password_change.h"

#include "core/service/openproj/controllers/copy_projects_controller.h"
#include "core/service/openproj/controllers/custom_actions_controller.h"
#include "core/service/openproj/controllers/custom_fields_controller.h"
#include "core/service/openproj/controllers/custom_styles_controller.h"
#include "core/service/openproj/controllers/enterprises_controller.h"
#include "core/service/openproj/controllers/enumerations_controller.h"
#include "core/service/openproj/controllers/forums_controller.h"
#include "core/service/openproj/controllers/groups_controller.h"
#include "core/service/openproj/controllers/help_controller.h"
#include "core/service/openproj/controllers/highlighting_controller.h"
#include "core/service/openproj/controllers/homescreen_controller.h"
#include "core/service/openproj/controllers/journals_controller.h"
#include "core/service/openproj/controllers/ldap_auth_sources_controller.h"
#include "core/service/openproj/controllers/members_controller.h"
#include "core/service/openproj/controllers/messages_controller.h"
#include "core/service/openproj/controllers/my_controller.h"

#include "core/service/openproj/controllers/news/comments_controller.h"
#include "core/service/openproj/controllers/news_controller.h"

#include "core/service/openproj/controllers/oauth/applications_controller.h"
#include "core/service/openproj/controllers/oauth/auth_base_controller.h"
#include "core/service/openproj/controllers/oauth/grants_controller.h"

#include "core/service/openproj/controllers/onboarding_controller.h"
#include "core/service/openproj/controllers/project_enumerations_controller.h"
#include "core/service/openproj/controllers/project_settings_controller.h"
#include "core/service/openproj/controllers/projects_controller.h"
#include "core/service/openproj/controllers/repositories_controller.h"
#include "core/service/openproj/controllers/roles_controller.h"
#include "core/service/openproj/controllers/search_controller.h"
#include "core/service/openproj/controllers/settings_controller.h"
#include "core/service/openproj/controllers/statuses_controller.h"
#include "core/service/openproj/controllers/sys_controller.h"

#include "core/service/openproj/controllers/time_entries/reports_controller.h"

#include "core/service/openproj/controllers/timelog_controller.h"
#include "core/service/openproj/controllers/types_controller.h"

#include "core/service/openproj/controllers/users/memberships_controller.h"
#include "core/service/openproj/controllers/users_controller.h"
#include "core/service/openproj/controllers/users_settings_controller.h"
#include "core/service/openproj/controllers/versions_controller.h"
#include "core/service/openproj/controllers/watchers_controller.h"
#include "core/service/openproj/controllers/wiki_controller.h"
#include "core/service/openproj/controllers/wiki_menu_items_controller.h"
#include "core/service/openproj/controllers/workflows_controller.h"

#include "core/service/openproj/controllers/work_packages/auto_completes_controller.h"
#include "core/service/openproj/controllers/work_packages/bulk_controller.h"
#include "core/service/openproj/controllers/work_packages/calendars_controller.h"
#include "core/service/openproj/controllers/work_packages/moves_controller.h"
#include "core/service/openproj/controllers/work_packages/reports_controller.h"
#include "core/service/openproj/controllers/work_packages/settings_controller.h"

#include "core/service/openproj/controllers/work_packages_controller.h"

namespace todo {

class Project {};

}  // namespace todo
#endif
