#include "./auth.h"

#include <utility>
#include "../../../sql/dba.h"
#include "./session.h"
#include "fmt/format.h"

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
//#include
//"core/service/openproj/controllers/work_packages/settings_controller.h"

#include "core/service/openproj/controllers/work_packages_controller.h"

#include "core/service/openproj/helpers/accessibility_helper.h"
#include "core/service/openproj/helpers/accounts_helper.h"
#include "core/service/openproj/helpers/additional_url_helpers.h"
#include "core/service/openproj/helpers/admin_helper.h"
#include "core/service/openproj/helpers/angular_helper.h"
#include "core/service/openproj/helpers/announcements_helper.h"
#include "core/service/openproj/helpers/application_helper.h"
#include "core/service/openproj/helpers/attachments_helper.h"
#include "core/service/openproj/helpers/attribute_help_texts_helper.h"
#include "core/service/openproj/helpers/augmenting_helper.h"
#include "core/service/openproj/helpers/authentication_stage_path_helper.h"
#include "core/service/openproj/helpers/avatar_helper.h"
#include "core/service/openproj/helpers/breadcrumb_helper.h"
#include "core/service/openproj/helpers/browser_helper.h"
#include "core/service/openproj/helpers/calendars_helper.h"
#include "core/service/openproj/helpers/cells_helper.h"
#include "core/service/openproj/helpers/colors_helper.h"
#include "core/service/openproj/helpers/content_for_helper.h"
#include "core/service/openproj/helpers/crowdin_helper.h"
#include "core/service/openproj/helpers/custom_fields_helper.h"
#include "core/service/openproj/helpers/error_message_helper.h"
#include "core/service/openproj/helpers/errors_helper.h"
#include "core/service/openproj/helpers/frontend_asset_helper.h"
#include "core/service/openproj/helpers/groups_helper.h"
#include "core/service/openproj/helpers/hide_sections_helper.h"
#include "core/service/openproj/helpers/highlighting_helper.h"
#include "core/service/openproj/helpers/homescreen_helper.h"
#include "core/service/openproj/helpers/hook_helper.h"
#include "core/service/openproj/helpers/icons_helper.h"
#include "core/service/openproj/helpers/issues_helper.h"
#include "core/service/openproj/helpers/messages_helper.h"
#include "core/service/openproj/helpers/meta_tags_helper.h"
#include "core/service/openproj/helpers/no_results_helper.h"
#include "core/service/openproj/helpers/oauth_helper.h"
#include "core/service/openproj/helpers/omniauth_helper.h"
#include "core/service/openproj/helpers/open_project_error_helper.h"
#include "core/service/openproj/helpers/pagination_helper.h"
#include "core/service/openproj/helpers/password_helper.h"
#include "core/service/openproj/helpers/projects_helper.h"
#include "core/service/openproj/helpers/queries_helper.h"
#include "core/service/openproj/helpers/query_menu_items_helper.h"
#include "core/service/openproj/helpers/relations_helper.h"
#include "core/service/openproj/helpers/removed_js_helpers_helper.h"
#include "core/service/openproj/helpers/reorder_links_helper.h"
#include "core/service/openproj/helpers/reports_helper.h"
#include "core/service/openproj/helpers/repositories_helper.h"
#include "core/service/openproj/helpers/roles_helper.h"
#include "core/service/openproj/helpers/search_helper.h"
#include "core/service/openproj/helpers/security_badge_helper.h"
#include "core/service/openproj/helpers/settings_helper.h"
#include "core/service/openproj/helpers/sort_helper.h"
#include "core/service/openproj/helpers/static_links_helper.h"
#include "core/service/openproj/helpers/tabs_helper.h"
#include "core/service/openproj/helpers/text_formatting_helper.h"
#include "core/service/openproj/helpers/timelog_helper.h"
#include "core/service/openproj/helpers/toolbar_helper.h"
#include "core/service/openproj/helpers/types_helper.h"
#include "core/service/openproj/helpers/user_consent_helper.h"
#include "core/service/openproj/helpers/users_helper.h"
#include "core/service/openproj/helpers/versions_helper.h"
#include "core/service/openproj/helpers/warning_bar_helper.h"
#include "core/service/openproj/helpers/watchers_helper.h"
#include "core/service/openproj/helpers/wiki_helper.h"
#include "core/service/openproj/helpers/work_packages_filter_helper.h"
#include "core/service/openproj/helpers/work_packages_helper.h"

#include "core/service/openproj/mailers/base_mailer.h"
#include "core/service/openproj/mailers/project_mailer.h"
#include "core/service/openproj/mailers/user_mailer.h"

// models 467 files

#include "core/service/openproj/policies/base_policy.h"
#include "core/service/openproj/policies/query_policy.h"
#include "core/service/openproj/policies/redirect_policy.h"
#include "core/service/openproj/policies/version_policy.h"
#include "core/service/openproj/policies/work_package_policy.h"

#include "core/service/openproj/policies/scm/authorization_policy.h"
#include "core/service/openproj/policies/scm/git_authorization_policy.h"
#include "core/service/openproj/policies/scm/subversion_authorization_policy.h"

// seeders 42 files

#include "core/service/openproj/services/add_attachment_service.h"
#include "core/service/openproj/services/add_work_package_note_service.h"

#include "core/service/openproj/services/api/v3/params_to_query_service.h"
#include "core/service/openproj/services/api/v3/parse_query_params_service.h"
#include "core/service/openproj/services/api/v3/parse_resource_params_service.h"
#include "core/service/openproj/services/api/v3/update_query_from_v3_params_service.h"
#include "core/service/openproj/services/api/v3/work_package_collection_from_query_params_service.h"
#include "core/service/openproj/services/api/v3/work_package_collection_from_query_service.h"

#include "core/service/openproj/services/attachments/set_replacements.h"

#include "core/service/openproj/services/authorization.h"
#include "core/service/openproj/services/authorization/abstract_query.h"
#include "core/service/openproj/services/authorization/abstract_user_query.h"
#include "core/service/openproj/services/authorization/enterprise_service.h"
#include "core/service/openproj/services/authorization/project_query.h"
#include "core/service/openproj/services/authorization/query_transformation.h"
#include "core/service/openproj/services/authorization/query_transformation_visitor.h"
#include "core/service/openproj/services/authorization/query_transformations.h"
#include "core/service/openproj/services/authorization/query_transformations_order.h"
#include "core/service/openproj/services/authorization/user_allowed_query.h"
#include "core/service/openproj/services/authorization/user_allowed_service.h"
#include "core/service/openproj/services/authorization/user_global_roles_query.h"
#include "core/service/openproj/services/authorization/user_project_roles_query.h"
#include "core/service/openproj/services/authorization/user_roles_query.h"
#include "core/service/openproj/services/authorization_service.h"
#include "core/service/openproj/services/base_project_service.h"

#include "core/service/openproj/services/base_services/create.h"
#include "core/service/openproj/services/base_services/delete.h"
#include "core/service/openproj/services/base_services/set_attributes.h"
#include "core/service/openproj/services/base_services/update.h"
#include "core/service/openproj/services/base_type_service.h"

#include "core/service/openproj/services/changesets/log_time_service.h"

#include "core/service/openproj/services/concerns/contracted.h"
#include "core/service/openproj/services/create_type_service.h"

#include "core/service/openproj/services/custom_actions/base_service.h"
#include "core/service/openproj/services/custom_actions/create_service.h"
#include "core/service/openproj/services/custom_actions/update_service.h"
#include "core/service/openproj/services/custom_actions/update_work_package_service.h"

#include "core/service/openproj/services/members/create_service.h"
#include "core/service/openproj/services/members/delete_service.h"
#include "core/service/openproj/services/members/edit_membership_service.h"
#include "core/service/openproj/services/members/set_attributes_service.h"
#include "core/service/openproj/services/members/update_service.h"

#include "core/service/openproj/services/oauth/persist_application_service.h"
#include "core/service/openproj/services/params_to_query_service.h"
#include "core/service/openproj/services/parse_schema_filter_params_service.h"

#include "core/service/openproj/services/projects/delete_project_service.h"
#include "core/service/openproj/services/projects/set_attributes_service.h"
#include "core/service/openproj/services/projects/update_service.h"

#include "core/service/openproj/services/queries/create_query_service.h"
#include "core/service/openproj/services/queries/query_service.h"
#include "core/service/openproj/services/queries/update_query_service.h"

#include "core/service/openproj/services/relations/base_service.h"
#include "core/service/openproj/services/relations/create_service.h"
#include "core/service/openproj/services/relations/update_service.h"

#include "core/service/openproj/services/reports/assignee_report.h"
#include "core/service/openproj/services/reports/author_report.h"
#include "core/service/openproj/services/reports/category_report.h"
#include "core/service/openproj/services/reports/priority_report.h"
#include "core/service/openproj/services/reports/report.h"
#include "core/service/openproj/services/reports/reports_service.h"
#include "core/service/openproj/services/reports/responsible_report.h"
#include "core/service/openproj/services/reports/subproject_report.h"
#include "core/service/openproj/services/reports/type_report.h"
#include "core/service/openproj/services/reports/version_report.h"

#include "core/service/openproj/services/roles/create_service.h"
#include "core/service/openproj/services/roles/notify_mixin.h"
#include "core/service/openproj/services/roles/set_attributes_service.h"
#include "core/service/openproj/services/roles/update_service.h"

#include "core/service/openproj/services/scm/base_repository_service.h"
#include "core/service/openproj/services/scm/checkout_instructions_service.h"
#include "core/service/openproj/services/scm/create_managed_repository_service.h"
#include "core/service/openproj/services/scm/delete_managed_repository_service.h"
#include "core/service/openproj/services/scm/repository_factory_service.h"
#include "core/service/openproj/services/service_result.h"

#include "core/service/openproj/services/sessions/base_service.h"
#include "core/service/openproj/services/sessions/drop_other_sessions_service.h"
#include "core/service/openproj/services/sessions/initialize_session_service.h"
#include "core/service/openproj/services/set_localization_service.h"

#include "core/service/openproj/services/settings/update_service.h"

#include "core/service/openproj/services/shared/block_service.h"
#include "core/service/openproj/services/shared/service_context.h"

#include "core/service/openproj/services/time_entries/create_service.h"
#include "core/service/openproj/services/time_entries/delete_service.h"
#include "core/service/openproj/services/time_entries/set_attributes_service.h"
#include "core/service/openproj/services/time_entries/update_service.h"
#include "core/service/openproj/services/update_projects_types_service.h"
#include "core/service/openproj/services/update_query_from_params_service.h"
#include "core/service/openproj/services/update_type_service.h"
#include "core/service/openproj/services/update_user_email_settings_service.h"

#include "core/service/openproj/services/user_search_service.h"
#include "core/service/openproj/services/users/change_password_service.h"
#include "core/service/openproj/services/users/create_user_service.h"
#include "core/service/openproj/services/users/delete_service.h"
#include "core/service/openproj/services/users/update_service.h"
#include "core/service/openproj/services/users/update_user_service.h"

#include "core/service/openproj/services/versions/create_service.h"
#include "core/service/openproj/services/versions/delete_service.h"
#include "core/service/openproj/services/versions/set_attributes_service.h"
#include "core/service/openproj/services/versions/update_service.h"

#include "core/service/openproj/services/workflows/bulk_update_service.h"

#include "core/service/openproj/services/work_packages/bulk/update_service.h"
#include "core/service/openproj/services/work_packages/copy_service.h"
#include "core/service/openproj/services/work_packages/create_service.h"
#include "core/service/openproj/services/work_packages/delete_service.h"
#include "core/service/openproj/services/work_packages/move_service.h"
#include "core/service/openproj/services/work_packages/reschedule_service.h"
#include "core/service/openproj/services/work_packages/schedule_dependency.h"
#include "core/service/openproj/services/work_packages/set_attributes_service.h"
#include "core/service/openproj/services/work_packages/set_schedule_service.h"

#include "core/service/openproj/services/work_packages/shared/update_ancestors.h"
#include "core/service/openproj/services/work_packages/shared/update_attributes.h"
#include "core/service/openproj/services/work_packages/update_ancestors_service.h"
#include "core/service/openproj/services/work_packages/update_service.h"

//---
#include "core/service/openproj/uploaders/file_uploader.h"
#include "core/service/openproj/uploaders/fog_file_uploader.h"
#include "core/service/openproj/uploaders/local_file_uploader.h"

#include "core/service/openproj/validators/url_validator.h"

#include "core/service/openproj/workers/application_job.h"
#include "core/service/openproj/workers/attachments/cleanup_uncontainered_job.h"
#include "core/service/openproj/workers/copy_project_job.h"
#include "core/service/openproj/workers/delete_user_job.h"
#include "core/service/openproj/workers/deliver_invitation_job.h"
#include "core/service/openproj/workers/deliver_notification_job.h"
#include "core/service/openproj/workers/deliver_watcher_notification_job.h"
#include "core/service/openproj/workers/deliver_work_package_notification_job.h"
#include "core/service/openproj/workers/enqueue_work_package_notification_job.h"
#include "core/service/openproj/workers/extract_fulltext_job.h"
#include "core/service/openproj/workers/mail_user_job.h"
#include "core/service/openproj/workers/oauth/cleanup_job.h"
#include "core/service/openproj/workers/projects/delete_project_job.h"
#include "core/service/openproj/workers/rake_job.h"
#include "core/service/openproj/workers/scm/create_local_repository_job.h"
#include "core/service/openproj/workers/scm/create_remote_repository_job.h"
#include "core/service/openproj/workers/scm/delete_local_repository_job.h"
#include "core/service/openproj/workers/scm/delete_remote_repository_job.h"
#include "core/service/openproj/workers/scm/relocate_repository_job.h"
#include "core/service/openproj/workers/scm/remote_repository_job.h"
#include "core/service/openproj/workers/scm/storage_updater_job.h"

#include "core/service/openproj/seeders/admin_user_seeder.h"

#include "core/service/openproj/seeders/basic_data/activity_seeder.h"
#include "core/service/openproj/seeders/basic_data/builtin_roles_seeder.h"
#include "core/service/openproj/seeders/basic_data/color_scheme_seeder.h"
#include "core/service/openproj/seeders/basic_data/color_seeder.h"
#include "core/service/openproj/seeders/basic_data/priority_seeder.h"
#include "core/service/openproj/seeders/basic_data/role_seeder.h"
#include "core/service/openproj/seeders/basic_data/setting_seeder.h"
#include "core/service/openproj/seeders/basic_data/status_seeder.h"
#include "core/service/openproj/seeders/basic_data/type_seeder.h"
#include "core/service/openproj/seeders/basic_data/workflow_seeder.h"
#include "core/service/openproj/seeders/basic_data_seeder.h"
#include "core/service/openproj/seeders/composite_seeder.h"

#include "core/service/openproj/seeders/demo_data/attribute_help_text_seeder.h"
#include "core/service/openproj/seeders/demo_data/custom_field_seeder.h"
#include "core/service/openproj/seeders/demo_data/global_query_seeder.h"
#include "core/service/openproj/seeders/demo_data/group_seeder.h"
#include "core/service/openproj/seeders/demo_data/project_seeder.h"
#include "core/service/openproj/seeders/demo_data/query_builder.h"
#include "core/service/openproj/seeders/demo_data/references.h"
#include "core/service/openproj/seeders/demo_data/version_builder.h"
#include "core/service/openproj/seeders/demo_data/wiki_seeder.h"
#include "core/service/openproj/seeders/demo_data/work_package_board_seeder.h"
#include "core/service/openproj/seeders/demo_data/work_package_seeder.h"
#include "core/service/openproj/seeders/demo_data_seeder.h"

#include "core/service/openproj/seeders/development_data/custom_fields_seeder.h"
#include "core/service/openproj/seeders/development_data/projects_seeder.h"
#include "core/service/openproj/seeders/development_data/users_seeder.h"
#include "core/service/openproj/seeders/development_data_seeder.h"

#include "core/service/openproj/seeders/random_data/forum_seeder.h"
#include "core/service/openproj/seeders/random_data/news_seeder.h"
#include "core/service/openproj/seeders/random_data/wiki_seeder.h"
#include "core/service/openproj/seeders/random_data/work_package_seeder.h"
#include "core/service/openproj/seeders/random_data_seeder.h"
#include "core/service/openproj/seeders/root_seeder.h"
#include "core/service/openproj/seeders/seeder.h"

#include "core/service/openproj/seeders/standard_seeder/basic_data/activity_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data/priority_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data/status_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data/type_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data/workflow_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data_seeder.h"

#include "core/service/openproj/models/activerecord.h"

#include "core/service/openproj/models/activity/base_activity_provider.h"
#include "core/service/openproj/models/activity/changeset_activity_provider.h"
#include "core/service/openproj/models/activity/message_activity_provider.h"
#include "core/service/openproj/models/activity/news_activity_provider.h"
#include "core/service/openproj/models/activity/time_entry_activity_provider.h"
#include "core/service/openproj/models/activity/wiki_content_activity_provider.h"
#include "core/service/openproj/models/activity/work_package_activity_provider.h"
#include "core/service/openproj/models/announcement.h"
#include "core/service/openproj/models/application_record.h"
#include "core/service/openproj/models/attachment.h"

#include "core/service/openproj/models/attribute_help_text/work_package.h"
#include "core/service/openproj/models/attribute_help_text.h"
#include "core/service/openproj/models/auth_source.h"
#include "core/service/openproj/models/category.h"
#include "core/service/openproj/models/change.h"
#include "core/service/openproj/models/changeset.h"
#include "core/service/openproj/models/color.h"
#include "core/service/openproj/models/comment.h"

#include "core/service/openproj/models/concerns/virtual_attribute.h"
#include "core/service/openproj/models/custom_action.h"


#include "core/service/openproj/models/custom_actions/actions/assigned_to.h"
#include "core/service/openproj/models/custom_actions/actions/base.h"
#include "core/service/openproj/models/custom_actions/actions/custom_field.h"
#include "core/service/openproj/models/custom_actions/actions/date.h"
#include "core/service/openproj/models/custom_actions/actions/done_ratio.h"
#include "core/service/openproj/models/custom_actions/actions/due_date.h"
#include "core/service/openproj/models/custom_actions/actions/estimated_hours.h"
#include "core/service/openproj/models/custom_actions/actions/inexistent.h"
#include "core/service/openproj/models/custom_actions/actions/notify.h"
#include "core/service/openproj/models/custom_actions/actions/priority.h"
#include "core/service/openproj/models/custom_actions/actions/project.h"
#include "core/service/openproj/models/custom_actions/actions/responsible.h"
#include "core/service/openproj/models/custom_actions/actions/serializer.h"
#include "core/service/openproj/models/custom_actions/actions/start_date.h"
#include "core/service/openproj/models/custom_actions/actions/status.h"

#include "core/service/openproj/models/custom_actions/actions/strategies/associated_custom_field.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/associated.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/boolean.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/custom_field.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/date.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/date_property.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/float.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/integer.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/string.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/text.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/validate_in_range.h"
#include "core/service/openproj/models/custom_actions/actions/strategies/values_to_string.h"
#include "core/service/openproj/models/custom_actions/actions/type.h"

#include "core/service/openproj/models/custom_actions/conditions/base.h"
#include "core/service/openproj/models/custom_actions/conditions/inexistent.h"
#include "core/service/openproj/models/custom_actions/conditions/project.h"
#include "core/service/openproj/models/custom_actions/conditions/role.h"
#include "core/service/openproj/models/custom_actions/conditions/status.h"
#include "core/service/openproj/models/custom_actions/conditions/type.h"
#include "core/service/openproj/models/custom_actions/register.h"
#include "core/service/openproj/models/custom_actions/validate_allowed_value.h"
#include "core/service/openproj/models/custom_actions/values_to_integer.h"

#include "core/service/openproj/models/custom_field/order_statements.h"
#include "core/service/openproj/models/custom_field.h"
#include "core/service/openproj/models/custom_option.h"
#include "core/service/openproj/models/custom_style.h"

#include "core/service/openproj/models/custom_value/ar_object_strategy.h"
#include "core/service/openproj/models/custom_value/bool_strategy.h"
#include "core/service/openproj/models/custom_value/date_strategy.h"
#include "core/service/openproj/models/custom_value/float_strategy.h"
#include "core/service/openproj/models/custom_value/format_strategy.h"
#include "core/service/openproj/models/custom_value/formattable_strategy.h"
#include "core/service/openproj/models/custom_value/int_strategy.h"
#include "core/service/openproj/models/custom_value/list_strategy.h"
#include "core/service/openproj/models/custom_value/string_strategy.h"
#include "core/service/openproj/models/custom_value/user_strategy.h"
#include "core/service/openproj/models/custom_value/version_strategy.h"
#include "core/service/openproj/models/custom_value.h"
#include "core/service/openproj/models/design_color.h"
#include "core/service/openproj/models/dummy_auth_source.h"
#include "core/service/openproj/models/enabled_module.h"
#include "core/service/openproj/models/enterprise_token.h"
#include "core/service/openproj/models/enumeration.h"
#include "core/service/openproj/models/forum.h"

#include "core/service/openproj/models/group/destroy.h"
#include "core/service/openproj/models/group_custom_field.h"
#include "core/service/openproj/models/group.h"
#include "core/service/openproj/models/issue_priority_custom_field.h"
#include "core/service/openproj/models/issue_priority.h"

#include "core/service/openproj/models/journal/aggregated_journal.h"
#include "core/service/openproj/models/journal/attachable_journal.h"
#include "core/service/openproj/models/journal/attachment_journal.h"
#include "core/service/openproj/models/journal/base_journal.h"
#include "core/service/openproj/models/journal/changeset_journal.h"
#include "core/service/openproj/models/journal/customizable_journal.h"
#include "core/service/openproj/models/journal/message_journal.h"
#include "core/service/openproj/models/journal/news_journal.h"
#include "core/service/openproj/models/journal/time_entry_journal.h"
#include "core/service/openproj/models/journal/wiki_content_journal.h"
#include "core/service/openproj/models/journal/work_package_journal.h"
#include "core/service/openproj/models/journal.h"
#include "core/service/openproj/models/journal_manager.h"
#include "core/service/openproj/models/journal_notification_mailer.h"
#include "core/service/openproj/models/journal_version.h"
#include "core/service/openproj/models/ldap_auth_source.h"
#include "core/service/openproj/models/legacy_journal.h"
#include "core/service/openproj/models/mail_handler.h"
#include "core/service/openproj/models/member.h"
#include "core/service/openproj/models/member_role.h"
#include "core/service/openproj/models/menu_item.h"

#include "core/service/openproj/models/menu_items/query_menu_item.h"
#include "core/service/openproj/models/menu_items/wiki_menu_item.h"
#include "core/service/openproj/models/message.h"

#include "core/service/openproj/models/mixins/changed_by_system.h"
#include "core/service/openproj/models/mixins/unique_finder.h"
#include "core/service/openproj/models/news.h"
#include "core/service/openproj/models/ordered_work_package.h"

#include "core/service/openproj/models/permitted_params/allowed_settings.h"
#include "core/service/openproj/models/permitted_params.h"
#include "core/service/openproj/models/principal.h"

#include "core/service/openproj/models/project/activity.h"
#include "core/service/openproj/models/project/copy.h"
#include "core/service/openproj/models/project/storage.h"
#include "core/service/openproj/models/project_custom_field.h"
#include "core/service/openproj/models/project.h"

#include "core/service/openproj/models/queries/available_filters.h"
#include "core/service/openproj/models/queries/available_orders.h"
#include "core/service/openproj/models/queries/base_order.h"
#include "core/service/openproj/models/queries/base_query.h"

#include "core/service/openproj/models/queries/columns/base.h"

#include "core/service/openproj/models/queries/filters/base.h"
#include "core/service/openproj/models/queries/filters/me_value.h"
#include "core/service/openproj/models/queries/filters/serializable.h"

#include "core/service/openproj/models/queries/filters/shared/any_user_name_attribute_filter.h"
#include "core/service/openproj/models/queries/filters/shared/custom_field_filter.h"

#include "core/service/openproj/models/queries/filters/shared/custom_fields/base.h"
#include "core/service/openproj/models/queries/filters/shared/custom_fields/bool.h"
#include "core/service/openproj/models/queries/filters/shared/custom_fields/list_optional.h"
#include "core/service/openproj/models/queries/filters/shared/custom_fields/user.h"
#include "core/service/openproj/models/queries/filters/shared/group_filter.h"
#include "core/service/openproj/models/queries/filters/shared/me_value_filter.h"
#include "core/service/openproj/models/queries/filters/shared/project_filter.h"
#include "core/service/openproj/models/queries/filters/shared/user_blocked_filter.h"
#include "core/service/openproj/models/queries/filters/shared/user_name_filter.h"
#include "core/service/openproj/models/queries/filters/shared/user_status_filter.h"

#include "core/service/openproj/models/queries/filters/strategies/base_strategy.h"
#include "core/service/openproj/models/queries/filters/strategies/boolean_list.h"
#include "core/service/openproj/models/queries/filters/strategies/cf_float.h"
#include "core/service/openproj/models/queries/filters/strategies/cf_integer.h"
#include "core/service/openproj/models/queries/filters/strategies/cf_list_optional.h"
#include "core/service/openproj/models/queries/filters/strategies/cf_numeric.h"
#include "core/service/openproj/models/queries/filters/strategies/date.h"
#include "core/service/openproj/models/queries/filters/strategies/date_interval.h"
#include "core/service/openproj/models/queries/filters/strategies/date_time_past.h"
#include "core/service/openproj/models/queries/filters/strategies/empty_value.h"
#include "core/service/openproj/models/queries/filters/strategies/float.h"
#include "core/service/openproj/models/queries/filters/strategies/float_numeric.h"
#include "core/service/openproj/models/queries/filters/strategies/huge_list.h"
#include "core/service/openproj/models/queries/filters/strategies/inexistent.h"
#include "core/service/openproj/models/queries/filters/strategies/integer.h"
#include "core/service/openproj/models/queries/filters/strategies/integer_list.h"
#include "core/service/openproj/models/queries/filters/strategies/integer_list_optional.h"
#include "core/service/openproj/models/queries/filters/strategies/integer_numeric.h"
#include "core/service/openproj/models/queries/filters/strategies/list_all.h"
#include "core/service/openproj/models/queries/filters/strategies/list.h"
#include "core/service/openproj/models/queries/filters/strategies/list_optional.h"
#include "core/service/openproj/models/queries/filters/strategies/numeric.h"
#include "core/service/openproj/models/queries/filters/strategies/relation.h"
#include "core/service/openproj/models/queries/filters/strategies/search.h"
#include "core/service/openproj/models/queries/filters/strategies/string.h"
#include "core/service/openproj/models/queries/filters/strategies/text.h"
#include "core/service/openproj/models/queries/filters/strategies/validations.h"
#include "core/service/openproj/models/queries/filters/strategies.h"
#include "core/service/openproj/models/queries/filters/templated_value.h"
#include "core/service/openproj/models/queries/filters.h"


#include "core/service/openproj/models/queries/members/filters/any_name_attribute_filter.h"
#include "core/service/openproj/models/queries/members/filters/blocked_filter.h"
#include "core/service/openproj/models/queries/members/filters/group_filter.h"
#include "core/service/openproj/models/queries/members/filters/member_filter.h"
#include "core/service/openproj/models/queries/members/filters/name_filter.h"
#include "core/service/openproj/models/queries/members/filters/principal_filter.h"
#include "core/service/openproj/models/queries/members/filters/project_filter.h"
#include "core/service/openproj/models/queries/members/filters/role_filter.h"
#include "core/service/openproj/models/queries/members/filters/status_filter.h"
#include "core/service/openproj/models/queries/members/member_query.h"

#include "core/service/openproj/models/queries/members/orders/default_order.h"
#include "core/service/openproj/models/queries/members.h"


#include "core/service/openproj/models/queries/news/filters/news_filter.h"
#include "core/service/openproj/models/queries/news/filters/project_filter.h"
#include "core/service/openproj/models/queries/news/news_query.h"

#include "core/service/openproj/models/queries/news/orders/default_order.h"
#include "core/service/openproj/models/queries/news.h"
#include "core/service/openproj/models/queries/not_existing_filter.h"
#include "core/service/openproj/models/queries/not_existing_order.h"

#include "core/service/openproj/models/queries/operators/ago.h"
#include "core/service/openproj/models/queries/operators/all_and_non_blank.h"
#include "core/service/openproj/models/queries/operators/all.h"
#include "core/service/openproj/models/queries/operators/base.h"
#include "core/service/openproj/models/queries/operators/between_date.h"
#include "core/service/openproj/models/queries/operators/between_date_time.h"
#include "core/service/openproj/models/queries/operators/blocked.h"
#include "core/service/openproj/models/queries/operators/blocks.h"
#include "core/service/openproj/models/queries/operators/boolean_equals.h"
#include "core/service/openproj/models/queries/operators/boolean_not_equals.h"
#include "core/service/openproj/models/queries/operators/casted_greater_or_equal.h"
#include "core/service/openproj/models/queries/operators/casted_less_or_equal.h"
#include "core/service/openproj/models/queries/operators/children.h"
#include "core/service/openproj/models/queries/operators/closed_work_packages.h"
#include "core/service/openproj/models/queries/operators/contains.h"
#include "core/service/openproj/models/queries/operators/date_range_clauses.h"
#include "core/service/openproj/models/queries/operators/datetime_range_clauses.h"
#include "core/service/openproj/models/queries/operators/duplicated.h"
#include "core/service/openproj/models/queries/operators/duplicates.h"
#include "core/service/openproj/models/queries/operators/equals.h"
#include "core/service/openproj/models/queries/operators/everywhere.h"
#include "core/service/openproj/models/queries/operators/follows.h"
#include "core/service/openproj/models/queries/operators/greater_or_equal.h"
#include "core/service/openproj/models/queries/operators/includes.h"
#include "core/service/openproj/models/queries/operators/in.h"
#include "core/service/openproj/models/queries/operators/in_less_than.h"
#include "core/service/openproj/models/queries/operators/in_more_than.h"
#include "core/service/openproj/models/queries/operators/less_or_equal.h"
#include "core/service/openproj/models/queries/operators/less_than_ago.h"
#include "core/service/openproj/models/queries/operators/more_than_ago.h"
#include "core/service/openproj/models/queries/operators/none.h"
#include "core/service/openproj/models/queries/operators/none_or_blank.h"
#include "core/service/openproj/models/queries/operators/not_contains.h"
#include "core/service/openproj/models/queries/operators/not_equals.h"
#include "core/service/openproj/models/queries/operators/on_date.h"
#include "core/service/openproj/models/queries/operators/on_date_time.h"
#include "core/service/openproj/models/queries/operators/open_work_packages.h"
#include "core/service/openproj/models/queries/operators/ordered_work_packages.h"
#include "core/service/openproj/models/queries/operators/parent.h"
#include "core/service/openproj/models/queries/operators/part_of.h"
#include "core/service/openproj/models/queries/operators/precedes.h"
#include "core/service/openproj/models/queries/operators/relates.h"
#include "core/service/openproj/models/queries/operators/required.h"
#include "core/service/openproj/models/queries/operators/requires.h"
#include "core/service/openproj/models/queries/operators/this_week.h"
#include "core/service/openproj/models/queries/operators/today.h"
#include "core/service/openproj/models/queries/operators.h"


#include "core/service/openproj/models/queries/principals/filters/id_filter.h"
#include "core/service/openproj/models/queries/principals/filters/member_filter.h"
#include "core/service/openproj/models/queries/principals/filters/name_filter.h"
#include "core/service/openproj/models/queries/principals/filters/principal_filter.h"
#include "core/service/openproj/models/queries/principals/filters/status_filter.h"
#include "core/service/openproj/models/queries/principals/filters/type_filter.h"

#include "core/service/openproj/models/queries/principals/orders/name_order.h"
#include "core/service/openproj/models/queries/principals/principal_query.h"
#include "core/service/openproj/models/queries/principals.h"


#include "core/service/openproj/models/queries/projects/filters/active_or_archived_filter.h"
#include "core/service/openproj/models/queries/projects/filters/ancestor_filter.h"
#include "core/service/openproj/models/queries/projects/filters/created_on_filter.h"
#include "core/service/openproj/models/queries/projects/filters/custom_field_context.h"
#include "core/service/openproj/models/queries/projects/filters/custom_field_filter.h"
#include "core/service/openproj/models/queries/projects/filters/id_filter.h"
#include "core/service/openproj/models/queries/projects/filters/latest_activity_at_filter.h"
#include "core/service/openproj/models/queries/projects/filters/name_and_identifier_filter.h"
#include "core/service/openproj/models/queries/projects/filters/parent_filter.h"
#include "core/service/openproj/models/queries/projects/filters/principal_filter.h"
#include "core/service/openproj/models/queries/projects/filters/project_filter.h"
#include "core/service/openproj/models/queries/projects/filters/type_filter.h"

#include "core/service/openproj/models/queries/projects/orders/custom_field_order.h"
#include "core/service/openproj/models/queries/projects/orders/default_order.h"
#include "core/service/openproj/models/queries/projects/orders/latest_activity_at_order.h"
#include "core/service/openproj/models/queries/projects/orders/required_disk_space_order.h"
#include "core/service/openproj/models/queries/projects/project_query.h"
#include "core/service/openproj/models/queries/projects.h"


#include "core/service/openproj/models/queries/queries/filters/hidden_filter.h"
#include "core/service/openproj/models/queries/queries/filters/id_filter.h"
#include "core/service/openproj/models/queries/queries/filters/project_filter.h"
#include "core/service/openproj/models/queries/queries/filters/project_identifier_filter.h"
#include "core/service/openproj/models/queries/queries/filters/query_filter.h"
#include "core/service/openproj/models/queries/queries/filters/updated_at_filter.h"
#include "core/service/openproj/models/queries/queries/query_query.h"
#include "core/service/openproj/models/queries/queries.h"
#include "core/service/openproj/models/queries/register.h"


#include "core/service/openproj/models/queries/relations/filters/from_filter.h"
#include "core/service/openproj/models/queries/relations/filters/id_filter.h"
#include "core/service/openproj/models/queries/relations/filters/involved_filter.h"
#include "core/service/openproj/models/queries/relations/filters/relation_filter.h"
#include "core/service/openproj/models/queries/relations/filters/to_filter.h"
#include "core/service/openproj/models/queries/relations/filters/type_filter.h"
#include "core/service/openproj/models/queries/relations/filters/visibility_checking.h"

#include "core/service/openproj/models/queries/relations/orders/default_order.h"
#include "core/service/openproj/models/queries/relations/relation_query.h"
#include "core/service/openproj/models/queries/relations.h"


#include "core/service/openproj/models/queries/roles/filters/grantable_filter.h"
#include "core/service/openproj/models/queries/roles/filters/role_filter.h"
#include "core/service/openproj/models/queries/roles/filters/unit_filter.h"
#include "core/service/openproj/models/queries/roles/role_query.h"
#include "core/service/openproj/models/queries/roles.h"


#include "core/service/openproj/models/queries/time_entries/filters/activity_filter.h"
#include "core/service/openproj/models/queries/time_entries/filters/created_on_filter.h"
#include "core/service/openproj/models/queries/time_entries/filters/project_filter.h"
#include "core/service/openproj/models/queries/time_entries/filters/spent_on_filter.h"
#include "core/service/openproj/models/queries/time_entries/filters/time_entry_filter.h"
#include "core/service/openproj/models/queries/time_entries/filters/user_filter.h"
#include "core/service/openproj/models/queries/time_entries/filters/work_package_filter.h"

#include "core/service/openproj/models/queries/time_entries/orders/default_order.h"
#include "core/service/openproj/models/queries/time_entries/time_entry_query.h"
#include "core/service/openproj/models/queries/time_entries.h"


#include "core/service/openproj/models/queries/users/filters/any_name_attribute_filter.h"
#include "core/service/openproj/models/queries/users/filters/blocked_filter.h"
#include "core/service/openproj/models/queries/users/filters/group_filter.h"
#include "core/service/openproj/models/queries/users/filters/login_filter.h"
#include "core/service/openproj/models/queries/users/filters/name_filter.h"
#include "core/service/openproj/models/queries/users/filters/status_filter.h"
#include "core/service/openproj/models/queries/users/filters/user_filter.h"

#include "core/service/openproj/models/queries/users/orders/default_order.h"
#include "core/service/openproj/models/queries/users/orders/group_order.h"
#include "core/service/openproj/models/queries/users/orders/name_order.h"
#include "core/service/openproj/models/queries/users/user_query.h"
#include "core/service/openproj/models/queries/users.h"


#include "core/service/openproj/models/queries/versions/filters/sharing_filter.h"
#include "core/service/openproj/models/queries/versions/filters/version_filter.h"

#include "core/service/openproj/models/queries/versions/orders/name_order.h"
#include "core/service/openproj/models/queries/versions/version_query.h"
#include "core/service/openproj/models/queries/versions.h"


#include "core/service/openproj/models/queries/work_packages/columns/custom_field_column.h"
#include "core/service/openproj/models/queries/work_packages/columns/manual_sorting_column.h"
#include "core/service/openproj/models/queries/work_packages/columns/property_column.h"
#include "core/service/openproj/models/queries/work_packages/columns/relation_column.h"
#include "core/service/openproj/models/queries/work_packages/columns/relation_of_type_column.h"
#include "core/service/openproj/models/queries/work_packages/columns/relation_to_type_column.h"
#include "core/service/openproj/models/queries/work_packages/columns/work_package_column.h"

#include "core/service/openproj/models/queries/work_packages/common/manual_sorting.h"

#include "core/service/openproj/models/queries/work_packages/filter/assigned_to_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/assignee_or_group_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/attachment_base_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/attachment_content_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/attachment_file_name_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/author_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/blocked_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/blocks_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/category_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/comment_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/created_at_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/custom_field_context.h"
#include "core/service/openproj/models/queries/work_packages/filter/custom_field_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/dates_interval_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/description_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/done_ratio_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/due_date_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/duplicated_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/duplicates_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/estimated_hours_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/filter_configuration.h"
#include "core/service/openproj/models/queries/work_packages/filter/filter_for_wp_mixin.h"
#include "core/service/openproj/models/queries/work_packages/filter/filter_on_directed_relations_mixin.h"
#include "core/service/openproj/models/queries/work_packages/filter/filter_on_tsv_mixin.h"
#include "core/service/openproj/models/queries/work_packages/filter/filter_on_undirected_relations_mixin.h"
#include "core/service/openproj/models/queries/work_packages/filter/follows_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/group_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/id_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/includes_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/manual_sort_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/me_value_filter_mixin.h"
#include "core/service/openproj/models/queries/work_packages/filter/or_filter_for_wp_mixin.h"
#include "core/service/openproj/models/queries/work_packages/filter/parent_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/partof_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/precedes_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/principal_base_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/principal_loader.h"
#include "core/service/openproj/models/queries/work_packages/filter/priority_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/project_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/relatable_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/relates_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/required_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/requires_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/responsible_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/role_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/search_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/start_date_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/status_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/subject_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/subject_or_id_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/subproject_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/text_filter_on_join_mixin.h"
#include "core/service/openproj/models/queries/work_packages/filter/type_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/updated_at_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/version_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/watcher_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter/work_package_filter.h"
#include "core/service/openproj/models/queries/work_packages/filter.h"
#include "core/service/openproj/models/queries/work_packages/filter_serializer.h"
#include "core/service/openproj/models/queries/work_packages.h"

#include "core/service/openproj/models/query/group_by.h"
#include "core/service/openproj/models/query/highlighting.h"
#include "core/service/openproj/models/query/manual_sorting.h"
#include "core/service/openproj/models/query/results.h"
#include "core/service/openproj/models/query/statement_invalid.h"
#include "core/service/openproj/models/query/sums.h"
#include "core/service/openproj/models/query/timelines.h"
#include "core/service/openproj/models/query.h"
#include "core/service/openproj/models/relation.h"

#include "core/service/openproj/models/repository/git.h"
#include "core/service/openproj/models/repository/subversion.h"
#include "core/service/openproj/models/repository.h"
#include "core/service/openproj/models/role.h"
#include "core/service/openproj/models/role_permission.h"

#include "core/service/openproj/models/setting/aliases.h"
#include "core/service/openproj/models/setting/callbacks.h"
#include "core/service/openproj/models/setting.h"
#include "core/service/openproj/models/status.h"
#include "core/service/openproj/models/system_user.h"
#include "core/service/openproj/models/time_entry_activity_custom_field.h"
#include "core/service/openproj/models/time_entry_activity.h"
#include "core/service/openproj/models/time_entry_custom_field.h"
#include "core/service/openproj/models/time_entry.h"

#include "core/service/openproj/models/token/api.h"
#include "core/service/openproj/models/token/auto_login.h"
#include "core/service/openproj/models/token/base.h"
#include "core/service/openproj/models/token/expirable_token.h"
#include "core/service/openproj/models/token/hashed_token.h"
#include "core/service/openproj/models/token/invitation.h"
#include "core/service/openproj/models/token/recovery.h"
#include "core/service/openproj/models/token/rss.h"

#include "core/service/openproj/models/type/attribute_group.h"
#include "core/service/openproj/models/type/attribute_groups.h"
#include "core/service/openproj/models/type/attributes.h"
#include "core/service/openproj/models/type/form_group.h"
#include "core/service/openproj/models/type/query_group.h"
#include "core/service/openproj/models/type.h"

#include "core/service/openproj/models/user/project_authorization_cache.h"
#include "core/service/openproj/models/user/project_role_cache.h"
#include "core/service/openproj/models/user/status_options.h"
#include "core/service/openproj/models/user_custom_field.h"
#include "core/service/openproj/models/user.h"

#include "core/service/openproj/models/user_password/bcrypt.h"
#include "core/service/openproj/models/user_password/sha1.h"
#include "core/service/openproj/models/user_password.h"
#include "core/service/openproj/models/user_preference.h"
#include "core/service/openproj/models/user_session.h"

#include "core/service/openproj/models/version/project_sharing.h"
#include "core/service/openproj/models/version_custom_field.h"
#include "core/service/openproj/models/version.h"
#include "core/service/openproj/models/watcher.h"
#include "core/service/openproj/models/watcher_notification_mailer.h"
#include "core/service/openproj/models/wiki_content.h"
#include "core/service/openproj/models/wiki.h"
#include "core/service/openproj/models/wiki_page.h"
#include "core/service/openproj/models/wiki_redirect.h"
#include "core/service/openproj/models/workflow.h"

#include "core/service/openproj/models/work_package/ancestors.h"
#include "core/service/openproj/models/work_package/ask_before_destruction.h"
#include "core/service/openproj/models/work_package/available_custom_fields.h"
#include "core/service/openproj/models/work_package/custom_actions.h"

#include "core/service/openproj/models/work_package/exporter/base.h"
#include "core/service/openproj/models/work_package/exporter/csv.h"
#include "core/service/openproj/models/work_package/exporter/error.h"
#include "core/service/openproj/models/work_package/exporter/pdf.h"
#include "core/service/openproj/models/work_package/exporter/result.h"
#include "core/service/openproj/models/work_package/exporter/success.h"
#include "core/service/openproj/models/work_package/exporter.h"
#include "core/service/openproj/models/work_package/inexistent_work_package.h"
#include "core/service/openproj/models/work_package/journalized.h"
#include "core/service/openproj/models/work_package/parent.h"

#include "core/service/openproj/models/work_package/pdf_export/attachments.h"
#include "core/service/openproj/models/work_package/pdf_export/common.h"
#include "core/service/openproj/models/work_package/pdf_export/to_pdf_helper.h"
#include "core/service/openproj/models/work_package/pdf_export/view.h"
#include "core/service/openproj/models/work_package/pdf_export/work_package_list_to_pdf.h"
#include "core/service/openproj/models/work_package/pdf_export/work_package_to_pdf.h"
#include "core/service/openproj/models/work_package/scheduling_rules.h"
#include "core/service/openproj/models/work_package/spent_time.h"
#include "core/service/openproj/models/work_package/status_transitions.h"
#include "core/service/openproj/models/work_package/time_entries.h"
#include "core/service/openproj/models/work_package/typed_dag_defaults.h"
#include "core/service/openproj/models/work_package/validations.h"
#include "core/service/openproj/models/work_package_custom_field.h"
#include "core/service/openproj/models/work_package.h"

namespace todo {
namespace service {
Auth::Auth(std::shared_ptr<websocket::todo::TodoContext> context_)
    : context(std::move(context_)) {
  setupTable();
}

void Auth::setupTable() {}

nlohmann::json Auth::handleEvent(nlohmann::json event, unsigned long next,
                                 nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "login") {
    nlohmann::json res = {{}, {}};
    if (args.is_object() && args["user"].is_string() &&
        args["pass"].is_string()) {
      auto isauthorised =
          "select (u.expiry > now()) as isexpired, u.disabled from music.user "
          "as u WHERE "
          "username = $1";
      auto r = sql::Dba::read(isauthorised, args["user"].get<std::string>());
      if (r.empty()) {
        return {websocket::WsFns::successJsonObject(event, false, "Error")};
      } else if (!r[0]["isexpired"].isNull() && r[0]["isexpired"].as<bool>()) {
        return {websocket::WsFns::successJsonObject(event, false, "Expired")};
      } else if (r[0]["disabled"].as<bool>()) {
        return {websocket::WsFns::successJsonObject(event, false, "Locked")};
      }

      auto [session_id, user_id] = login(args["user"].get<std::string>(),
                                         args["pass"].get<std::string>());
      res[0][1] = session_id;
      if (session_id) {
        context->setSessionId(session_id);
        context->setUserId(user_id);
        context->setUser();
        res[0] = websocket::WsFns::successJsonObject(event, true, "Done");
        res[1] = {{"auth", "set_cookie", 0}, session_id};
        return res;
      }
    }
    return {websocket::WsFns::successJsonObject(event, false, "Error")};
  }
  if (event_cmp == "logout") {
    auto r = logout();
    if (r) {
      return {websocket::WsFns::successJsonObject(event, true, "Done")};
    }
    return {websocket::WsFns::successJsonObject(event, false, "UnAuthorised")};
  } else if (event_cmp == "file_meta_data") {
    return saveFileMeta(event, args);
  } else if (event_cmp == "ins") {
    return query.ins(event, args);
  } else if (event_cmp == "upd") {
    return query.upd(event, args);
  } else if (event_cmp == "del") {
    return query.del(event, args);
  } else {
    return nullptr;
  }
}
// Save Image meta on server temporary
nlohmann::json Auth::saveFileMeta(const nlohmann::json& event,
                                  nlohmann::json args) {
  if (!args.is_array() || args.size() <= 3) {
    nlohmann::json ret;
    ret[0] =
        websocket::WsFns::successJsonObject(event, false, "No Valid arguments");
    return ret;
  }
  long c = context->sessionId();

  // auto strSql = "INSERT INTO music.temp_file_meta ( session_id, event, name,
  // size, type ) VALUES( $1, $2, $3, $4, $5 )";
  auto strSql = fmt::format(
      "INSERT INTO music.temp_file_meta ( session_id, event, name, size, type "
      ") VALUES( {0}, '{1}','{2}', {3}, '{4}' )",
      c, args[0].dump(), args[1].get<std::string>(), args[2].get<long>(),
      args[3].get<std::string>());
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    auto r = sql::Dba::writeInTrans(transPtr, strSql);
    // auto r = sql::Dba::writeInTrans(transPtr, strSql, c, args[0].dump(),
    // args[1].get<std::string>(), args[2].get<long>(),
    // args[3].get<std::string>());
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
    return ret;
  } catch (const std::exception& e) {
    LOG_DEBUG << e.what();
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, false, "Error");
    return ret;
  }
}

bool Auth::logout(long key, bool relogin) {
  // If no key is passed try to find the session id
  key = key ? key : context->sessionId();

  // Nuke the cookie before all else
  auto r = Session::destroy(key);
  if (r) {
    context->setSessionId(0);
    return true;
  }
  return false;
  // if ((!relogin) && AmpConfig::get('logout_redirect')) {
  // target = AmpConfig::get('logout_redirect');
  //} else {
  // target = AmpConfig::get('web_path') . '/login.php';
  //}

  // Do a quick check to see if this is an AJAXed logout request
  // if so use the iframe to redirect
  // if (defined('AJAX_INCLUDE')) {
  // ob_end_clean();
  // ob_start();

  // xoutput_headers();

  // results            = array();
  // results['rfc3514'] = '<script type="text/javascript">reloadRedirect("' .
  // target . '")</script>'; echo xoutput_from_array(results);
  //} else {
  /* Redirect them to the login page */
  // header('Location: ' . target);
  //}
}

std::tuple<long, long> Auth::login(const std::string& username,
                                   const std::string& password, bool allow_ui) {
  long session_id = 0;
  long user_id = 0;
  if (!password.empty() && !username.empty()) {
    try {
      auto sql =
          "SELECT id, password FROM music.user WHERE username = $1 and "
          "password = $2";
      auto clientPtr = drogon::app().getDbClient("sce");
      auto transPtr = clientPtr->newTransaction();
      auto r = sql::Dba::writeInTrans(transPtr, sql, username, password);

      if (r.size() == 1) {
        user_id = r[0]["id"].as<long>();
        auto sqlSession =
            "INSERT INTO music.session (user_id, expire, value) VALUES ($1, "
            "$2, $3) returning id";
        auto rs = sql::Dba::writeInTrans(transPtr, sqlSession, user_id, 0L, "");
        session_id = rs[0]["id"].as<long>();
      }
    } catch (const std::exception& e) {
      LOG_DEBUG << e.what();
    }
  }
  return {session_id, user_id};
}
}  // namespace service
}  // namespace todo
