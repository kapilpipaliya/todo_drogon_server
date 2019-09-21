#include "seed.h"

#include "./auth.h"

#include <utility>
#include "../../../sql/dba.h"
#include "./session.h"
#include "core/service/openproj/seeders/basic_data/builtin_roles_seeder.h"
#include "core/service/openproj/seeders/basic_data/role_seeder.h"
#include "core/service/openproj/seeders/root_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data/type_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data/workflow_seeder.h"
#include "fmt/format.h"
#include "wscontroller/wsfns.h"

#include "../../../sql/dba.h"

#include "models/Announcements.h"
#include "models/ArInternalMetadata.h"
#include "models/AttachableJournals.h"
#include "models/AttachmentJournals.h"
#include "models/Attachments.h"
#include "models/AttributeHelpTexts.h"
#include "models/AuthSources.h"
#include "models/Categories.h"
#include "models/Changes.h"
#include "models/ChangesetJournals.h"
#include "models/Changesets.h"
#include "models/ChangesetsWorkPackages.h"
#include "models/Colors.h"
#include "models/Comments.h"
#include "models/CostEntries.h"
#include "models/CostObjectJournals.h"
#include "models/CostObjects.h"
#include "models/CostQueries.h"
#include "models/CostTypes.h"
#include "models/CustomActions.h"
#include "models/CustomActionsProjects.h"
#include "models/CustomActionsRoles.h"
#include "models/CustomActionsStatuses.h"
#include "models/CustomActionsTypes.h"
#include "models/CustomFields.h"
#include "models/CustomFieldsProjects.h"
#include "models/CustomFieldsTypes.h"
#include "models/CustomOptions.h"
#include "models/CustomStyles.h"
#include "models/CustomValues.h"
#include "models/CustomizableJournals.h"
#include "models/DelayedJobs.h"
#include "models/DesignColors.h"
#include "models/DocumentJournals.h"
#include "models/Documents.h"
#include "models/DoneStatusesForProject.h"
#include "models/EnabledModules.h"
#include "models/EnterpriseTokens.h"
#include "models/Enumerations.h"
#include "models/ExportCardConfigurations.h"
#include "models/Forums.h"
#include "models/GridWidgets.h"
#include "models/Grids.h"
#include "models/GroupUsers.h"
#include "models/JournalVersions.h"
#include "models/Journals.h"
#include "models/LaborBudgetItems.h"
#include "models/LdapGroupsMemberships.h"
#include "models/LdapGroupsSynchronizedGroups.h"
#include "models/MaterialBudgetItems.h"
#include "models/MeetingContentJournals.h"
#include "models/MeetingContents.h"
#include "models/MeetingJournals.h"
#include "models/MeetingParticipants.h"
#include "models/Meetings.h"
#include "models/MemberRoles.h"
#include "models/Members.h"
#include "models/MenuItems.h"
#include "models/MessageJournals.h"
#include "models/Messages.h"
#include "models/News.h"
#include "models/NewsJournals.h"
#include "models/OauthAccessGrants.h"
#include "models/OauthAccessTokens.h"
#include "models/OauthApplications.h"
#include "models/OrderedWorkPackages.h"
#include "models/PlaintextTokens.h"
#include "models/PrincipalRoles.h"
#include "models/ProjectAssociations.h"
#include "models/Projects.h"
#include "models/ProjectsTypes.h"
#include "models/Queries.h"
#include "models/Rates.h"
#include "models/RecaptchaEntries.h"
#include "models/Relations.h"
#include "models/Repositories.h"
#include "models/RolePermissions.h"
#include "models/Roles.h"
#include "models/SchemaMigrations.h"
#include "models/Sessions.h"
#include "models/Settings.h"
#include "models/Statuses.h"
#include "models/TimeEntries.h"
#include "models/TimeEntryJournals.h"
#include "models/Tokens.h"
#include "models/TwoFactorAuthenticationDevices.h"
#include "models/Types.h"
#include "models/UserPasswords.h"
#include "models/UserPreferences.h"
#include "models/Users.h"
#include "models/VersionSettings.h"
#include "models/Versions.h"
#include "models/Watchers.h"
#include "models/WebhooksEvents.h"
#include "models/WebhooksLogs.h"
#include "models/WebhooksProjects.h"
#include "models/WebhooksWebhooks.h"
#include "models/WikiContentJournals.h"
#include "models/WikiContents.h"
#include "models/WikiPages.h"
#include "models/WikiRedirects.h"
#include "models/Wikis.h"
#include "models/WorkPackageJournals.h"
#include "models/WorkPackages.h"
#include "models/Workflows.h"
namespace todo {
namespace service {
Seed::Seed(std::shared_ptr<websocket::todo::TodoContext> context_)
    : context(std::move(context_)) {
  setupTable();
}

void Seed::setupTable() {}

nlohmann::json Seed::handleEvent(nlohmann::json event, unsigned long next,
                                 nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "seed1") {
    openproj::seeder::BasicData::BuiltinRolesSeeder a;
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seed2") {
    openproj::seeder::BasicData::RoleSeeder a;
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seed3") {
    openproj::seeder::BasicData::SettingSeeder a;
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seed4") {
    openproj::seeder::StandardSeeder::BasicData::WorkflowSeeder a;
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seed5") {
    openproj::seeder::StandardSeeder::BasicData::TypeSeeder a;
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seedall") {
    openproj::seeder::RootSeeder a;
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "summary") {
    openproj::seeder::RootSeeder a;
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Announcements>
        mapper_announcements(clientPtr);
    LOG_DEBUG << "announcements : " << mapper_announcements.count();
    drogon::orm::Mapper<drogon_model::openproject6::ArInternalMetadata>
        mapper_ar_internal_metadata(clientPtr);
    LOG_DEBUG << "ar_internal_metadata : "
              << mapper_ar_internal_metadata.count();
    drogon::orm::Mapper<drogon_model::openproject6::AttachableJournals>
        mapper_attachable_journals(clientPtr);
    LOG_DEBUG << "attachable_journals : " << mapper_attachable_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::AttachmentJournals>
        mapper_attachment_journals(clientPtr);
    LOG_DEBUG << "attachment_journals : " << mapper_attachment_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::Attachments>
        mapper_attachments(clientPtr);
    LOG_DEBUG << "attachments : " << mapper_attachments.count();
    drogon::orm::Mapper<drogon_model::openproject6::AttributeHelpTexts>
        mapper_attribute_help_texts(clientPtr);
    LOG_DEBUG << "attribute_help_texts : "
              << mapper_attribute_help_texts.count();
    drogon::orm::Mapper<drogon_model::openproject6::AuthSources>
        mapper_auth_sources(clientPtr);
    LOG_DEBUG << "auth_sources : " << mapper_auth_sources.count();
    drogon::orm::Mapper<drogon_model::openproject6::Categories>
        mapper_categories(clientPtr);
    LOG_DEBUG << "categories : " << mapper_categories.count();
    drogon::orm::Mapper<drogon_model::openproject6::Changes> mapper_changes(
        clientPtr);
    LOG_DEBUG << "changes : " << mapper_changes.count();
    drogon::orm::Mapper<drogon_model::openproject6::ChangesetJournals>
        mapper_changeset_journals(clientPtr);
    LOG_DEBUG << "changeset_journals : " << mapper_changeset_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::Changesets>
        mapper_changesets(clientPtr);
    LOG_DEBUG << "changesets : " << mapper_changesets.count();
    drogon::orm::Mapper<drogon_model::openproject6::ChangesetsWorkPackages>
        mapper_changesets_work_packages(clientPtr);
    LOG_DEBUG << "changesets_work_packages : "
              << mapper_changesets_work_packages.count();
    drogon::orm::Mapper<drogon_model::openproject6::Colors> mapper_colors(
        clientPtr);
    LOG_DEBUG << "colors : " << mapper_colors.count();
    drogon::orm::Mapper<drogon_model::openproject6::Comments> mapper_comments(
        clientPtr);
    LOG_DEBUG << "comments : " << mapper_comments.count();
    drogon::orm::Mapper<drogon_model::openproject6::CostEntries>
        mapper_cost_entries(clientPtr);
    LOG_DEBUG << "cost_entries : " << mapper_cost_entries.count();
    drogon::orm::Mapper<drogon_model::openproject6::CostObjectJournals>
        mapper_cost_object_journals(clientPtr);
    LOG_DEBUG << "cost_object_journals : "
              << mapper_cost_object_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::CostObjects>
        mapper_cost_objects(clientPtr);
    LOG_DEBUG << "cost_objects : " << mapper_cost_objects.count();
    drogon::orm::Mapper<drogon_model::openproject6::CostQueries>
        mapper_cost_queries(clientPtr);
    LOG_DEBUG << "cost_queries : " << mapper_cost_queries.count();
    drogon::orm::Mapper<drogon_model::openproject6::CostTypes>
        mapper_cost_types(clientPtr);
    LOG_DEBUG << "cost_types : " << mapper_cost_types.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomActions>
        mapper_custom_actions(clientPtr);
    LOG_DEBUG << "custom_actions : " << mapper_custom_actions.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomActionsProjects>
        mapper_custom_actions_projects(clientPtr);
    LOG_DEBUG << "custom_actions_projects : "
              << mapper_custom_actions_projects.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomActionsRoles>
        mapper_custom_actions_roles(clientPtr);
    LOG_DEBUG << "custom_actions_roles : "
              << mapper_custom_actions_roles.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomActionsStatuses>
        mapper_custom_actions_statuses(clientPtr);
    LOG_DEBUG << "custom_actions_statuses : "
              << mapper_custom_actions_statuses.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomActionsTypes>
        mapper_custom_actions_types(clientPtr);
    LOG_DEBUG << "custom_actions_types : "
              << mapper_custom_actions_types.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomFields>
        mapper_custom_fields(clientPtr);
    LOG_DEBUG << "custom_fields : " << mapper_custom_fields.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomFieldsProjects>
        mapper_custom_fields_projects(clientPtr);
    LOG_DEBUG << "custom_fields_projects : "
              << mapper_custom_fields_projects.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomFieldsTypes>
        mapper_custom_fields_types(clientPtr);
    LOG_DEBUG << "custom_fields_types : " << mapper_custom_fields_types.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomOptions>
        mapper_custom_options(clientPtr);
    LOG_DEBUG << "custom_options : " << mapper_custom_options.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomStyles>
        mapper_custom_styles(clientPtr);
    LOG_DEBUG << "custom_styles : " << mapper_custom_styles.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomValues>
        mapper_custom_values(clientPtr);
    LOG_DEBUG << "custom_values : " << mapper_custom_values.count();
    drogon::orm::Mapper<drogon_model::openproject6::CustomizableJournals>
        mapper_customizable_journals(clientPtr);
    LOG_DEBUG << "customizable_journals : "
              << mapper_customizable_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::DelayedJobs>
        mapper_delayed_jobs(clientPtr);
    LOG_DEBUG << "delayed_jobs : " << mapper_delayed_jobs.count();
    drogon::orm::Mapper<drogon_model::openproject6::DesignColors>
        mapper_design_colors(clientPtr);
    LOG_DEBUG << "design_colors : " << mapper_design_colors.count();
    drogon::orm::Mapper<drogon_model::openproject6::DocumentJournals>
        mapper_document_journals(clientPtr);
    LOG_DEBUG << "document_journals : " << mapper_document_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::Documents> mapper_documents(
        clientPtr);
    LOG_DEBUG << "documents : " << mapper_documents.count();
    drogon::orm::Mapper<drogon_model::openproject6::DoneStatusesForProject>
        mapper_done_statuses_for_project(clientPtr);
    LOG_DEBUG << "done_statuses_for_project : "
              << mapper_done_statuses_for_project.count();
    drogon::orm::Mapper<drogon_model::openproject6::EnabledModules>
        mapper_enabled_modules(clientPtr);
    LOG_DEBUG << "enabled_modules : " << mapper_enabled_modules.count();
    drogon::orm::Mapper<drogon_model::openproject6::EnterpriseTokens>
        mapper_enterprise_tokens(clientPtr);
    LOG_DEBUG << "enterprise_tokens : " << mapper_enterprise_tokens.count();
    drogon::orm::Mapper<drogon_model::openproject6::Enumerations>
        mapper_enumerations(clientPtr);
    LOG_DEBUG << "enumerations : " << mapper_enumerations.count();
    drogon::orm::Mapper<drogon_model::openproject6::ExportCardConfigurations>
        mapper_export_card_configurations(clientPtr);
    LOG_DEBUG << "export_card_configurations : "
              << mapper_export_card_configurations.count();
    drogon::orm::Mapper<drogon_model::openproject6::Forums> mapper_forums(
        clientPtr);
    LOG_DEBUG << "forums : " << mapper_forums.count();
    drogon::orm::Mapper<drogon_model::openproject6::GridWidgets>
        mapper_grid_widgets(clientPtr);
    LOG_DEBUG << "grid_widgets : " << mapper_grid_widgets.count();
    drogon::orm::Mapper<drogon_model::openproject6::Grids> mapper_grids(
        clientPtr);
    LOG_DEBUG << "grids : " << mapper_grids.count();
    drogon::orm::Mapper<drogon_model::openproject6::GroupUsers>
        mapper_group_users(clientPtr);
    LOG_DEBUG << "group_users : " << mapper_group_users.count();
    drogon::orm::Mapper<drogon_model::openproject6::JournalVersions>
        mapper_journal_versions(clientPtr);
    LOG_DEBUG << "journal_versions : " << mapper_journal_versions.count();
    drogon::orm::Mapper<drogon_model::openproject6::Journals> mapper_journals(
        clientPtr);
    LOG_DEBUG << "journals : " << mapper_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::LaborBudgetItems>
        mapper_labor_budget_items(clientPtr);
    LOG_DEBUG << "labor_budget_items : " << mapper_labor_budget_items.count();
    drogon::orm::Mapper<drogon_model::openproject6::LdapGroupsMemberships>
        mapper_ldap_groups_memberships(clientPtr);
    LOG_DEBUG << "ldap_groups_memberships : "
              << mapper_ldap_groups_memberships.count();
    drogon::orm::Mapper<
        drogon_model::openproject6::LdapGroupsSynchronizedGroups>
        mapper_ldap_groups_synchronized_groups(clientPtr);
    LOG_DEBUG << "ldap_groups_synchronized_groups : "
              << mapper_ldap_groups_synchronized_groups.count();
    drogon::orm::Mapper<drogon_model::openproject6::MaterialBudgetItems>
        mapper_material_budget_items(clientPtr);
    LOG_DEBUG << "material_budget_items : "
              << mapper_material_budget_items.count();
    drogon::orm::Mapper<drogon_model::openproject6::MeetingContentJournals>
        mapper_meeting_content_journals(clientPtr);
    LOG_DEBUG << "meeting_content_journals : "
              << mapper_meeting_content_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::MeetingContents>
        mapper_meeting_contents(clientPtr);
    LOG_DEBUG << "meeting_contents : " << mapper_meeting_contents.count();
    drogon::orm::Mapper<drogon_model::openproject6::MeetingJournals>
        mapper_meeting_journals(clientPtr);
    LOG_DEBUG << "meeting_journals : " << mapper_meeting_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::MeetingParticipants>
        mapper_meeting_participants(clientPtr);
    LOG_DEBUG << "meeting_participants : "
              << mapper_meeting_participants.count();
    drogon::orm::Mapper<drogon_model::openproject6::Meetings> mapper_meetings(
        clientPtr);
    LOG_DEBUG << "meetings : " << mapper_meetings.count();
    drogon::orm::Mapper<drogon_model::openproject6::MemberRoles>
        mapper_member_roles(clientPtr);
    LOG_DEBUG << "member_roles : " << mapper_member_roles.count();
    drogon::orm::Mapper<drogon_model::openproject6::Members> mapper_members(
        clientPtr);
    LOG_DEBUG << "members : " << mapper_members.count();
    drogon::orm::Mapper<drogon_model::openproject6::MenuItems>
        mapper_menu_items(clientPtr);
    LOG_DEBUG << "menu_items : " << mapper_menu_items.count();
    drogon::orm::Mapper<drogon_model::openproject6::MessageJournals>
        mapper_message_journals(clientPtr);
    LOG_DEBUG << "message_journals : " << mapper_message_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::Messages> mapper_messages(
        clientPtr);
    LOG_DEBUG << "messages : " << mapper_messages.count();
    drogon::orm::Mapper<drogon_model::openproject6::News> mapper_news(
        clientPtr);
    LOG_DEBUG << "news : " << mapper_news.count();
    drogon::orm::Mapper<drogon_model::openproject6::NewsJournals>
        mapper_news_journals(clientPtr);
    LOG_DEBUG << "news_journals : " << mapper_news_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::OauthAccessGrants>
        mapper_oauth_access_grants(clientPtr);
    LOG_DEBUG << "oauth_access_grants : " << mapper_oauth_access_grants.count();
    drogon::orm::Mapper<drogon_model::openproject6::OauthAccessTokens>
        mapper_oauth_access_tokens(clientPtr);
    LOG_DEBUG << "oauth_access_tokens : " << mapper_oauth_access_tokens.count();
    drogon::orm::Mapper<drogon_model::openproject6::OauthApplications>
        mapper_oauth_applications(clientPtr);
    LOG_DEBUG << "oauth_applications : " << mapper_oauth_applications.count();
    drogon::orm::Mapper<drogon_model::openproject6::OrderedWorkPackages>
        mapper_ordered_work_packages(clientPtr);
    LOG_DEBUG << "ordered_work_packages : "
              << mapper_ordered_work_packages.count();
    drogon::orm::Mapper<drogon_model::openproject6::PlaintextTokens>
        mapper_plaintext_tokens(clientPtr);
    LOG_DEBUG << "plaintext_tokens : " << mapper_plaintext_tokens.count();
    drogon::orm::Mapper<drogon_model::openproject6::PrincipalRoles>
        mapper_principal_roles(clientPtr);
    LOG_DEBUG << "principal_roles : " << mapper_principal_roles.count();
    drogon::orm::Mapper<drogon_model::openproject6::ProjectAssociations>
        mapper_project_associations(clientPtr);
    LOG_DEBUG << "project_associations : "
              << mapper_project_associations.count();
    drogon::orm::Mapper<drogon_model::openproject6::Projects> mapper_projects(
        clientPtr);
    LOG_DEBUG << "projects : " << mapper_projects.count();
    drogon::orm::Mapper<drogon_model::openproject6::ProjectsTypes>
        mapper_projects_types(clientPtr);
    LOG_DEBUG << "projects_types : " << mapper_projects_types.count();
    drogon::orm::Mapper<drogon_model::openproject6::Queries> mapper_queries(
        clientPtr);
    LOG_DEBUG << "queries : " << mapper_queries.count();
    drogon::orm::Mapper<drogon_model::openproject6::Rates> mapper_rates(
        clientPtr);
    LOG_DEBUG << "rates : " << mapper_rates.count();
    drogon::orm::Mapper<drogon_model::openproject6::RecaptchaEntries>
        mapper_recaptcha_entries(clientPtr);
    LOG_DEBUG << "recaptcha_entries : " << mapper_recaptcha_entries.count();
    drogon::orm::Mapper<drogon_model::openproject6::Relations> mapper_relations(
        clientPtr);
    LOG_DEBUG << "relations : " << mapper_relations.count();
    drogon::orm::Mapper<drogon_model::openproject6::Repositories>
        mapper_repositories(clientPtr);
    LOG_DEBUG << "repositories : " << mapper_repositories.count();
    drogon::orm::Mapper<drogon_model::openproject6::RolePermissions>
        mapper_role_permissions(clientPtr);
    LOG_DEBUG << "role_permissions : " << mapper_role_permissions.count();
    drogon::orm::Mapper<drogon_model::openproject6::Roles> mapper_roles(
        clientPtr);
    LOG_DEBUG << "roles : " << mapper_roles.count();
    drogon::orm::Mapper<drogon_model::openproject6::SchemaMigrations>
        mapper_schema_migrations(clientPtr);
    LOG_DEBUG << "schema_migrations : " << mapper_schema_migrations.count();
    drogon::orm::Mapper<drogon_model::openproject6::Sessions> mapper_sessions(
        clientPtr);
    LOG_DEBUG << "sessions : " << mapper_sessions.count();
    drogon::orm::Mapper<drogon_model::openproject6::Settings> mapper_settings(
        clientPtr);
    LOG_DEBUG << "settings : " << mapper_settings.count();
    drogon::orm::Mapper<drogon_model::openproject6::Statuses> mapper_statuses(
        clientPtr);
    LOG_DEBUG << "statuses : " << mapper_statuses.count();
    drogon::orm::Mapper<drogon_model::openproject6::TimeEntries>
        mapper_time_entries(clientPtr);
    LOG_DEBUG << "time_entries : " << mapper_time_entries.count();
    drogon::orm::Mapper<drogon_model::openproject6::TimeEntryJournals>
        mapper_time_entry_journals(clientPtr);
    LOG_DEBUG << "time_entry_journals : " << mapper_time_entry_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::Tokens> mapper_tokens(
        clientPtr);
    LOG_DEBUG << "tokens : " << mapper_tokens.count();
    drogon::orm::Mapper<
        drogon_model::openproject6::TwoFactorAuthenticationDevices>
        mapper_two_factor_authentication_devices(clientPtr);
    LOG_DEBUG << "two_factor_authentication_devices : "
              << mapper_two_factor_authentication_devices.count();
    drogon::orm::Mapper<drogon_model::openproject6::Types> mapper_types(
        clientPtr);
    LOG_DEBUG << "types : " << mapper_types.count();
    drogon::orm::Mapper<drogon_model::openproject6::UserPasswords>
        mapper_user_passwords(clientPtr);
    LOG_DEBUG << "user_passwords : " << mapper_user_passwords.count();
    drogon::orm::Mapper<drogon_model::openproject6::UserPreferences>
        mapper_user_preferences(clientPtr);
    LOG_DEBUG << "user_preferences : " << mapper_user_preferences.count();
    drogon::orm::Mapper<drogon_model::openproject6::Users> mapper_users(
        clientPtr);
    LOG_DEBUG << "users : " << mapper_users.count();
    drogon::orm::Mapper<drogon_model::openproject6::VersionSettings>
        mapper_version_settings(clientPtr);
    LOG_DEBUG << "version_settings : " << mapper_version_settings.count();
    drogon::orm::Mapper<drogon_model::openproject6::Versions> mapper_versions(
        clientPtr);
    LOG_DEBUG << "versions : " << mapper_versions.count();
    drogon::orm::Mapper<drogon_model::openproject6::Watchers> mapper_watchers(
        clientPtr);
    LOG_DEBUG << "watchers : " << mapper_watchers.count();
    drogon::orm::Mapper<drogon_model::openproject6::WebhooksEvents>
        mapper_webhooks_events(clientPtr);
    LOG_DEBUG << "webhooks_events : " << mapper_webhooks_events.count();
    drogon::orm::Mapper<drogon_model::openproject6::WebhooksLogs>
        mapper_webhooks_logs(clientPtr);
    LOG_DEBUG << "webhooks_logs : " << mapper_webhooks_logs.count();
    drogon::orm::Mapper<drogon_model::openproject6::WebhooksProjects>
        mapper_webhooks_projects(clientPtr);
    LOG_DEBUG << "webhooks_projects : " << mapper_webhooks_projects.count();
    drogon::orm::Mapper<drogon_model::openproject6::WebhooksWebhooks>
        mapper_webhooks_webhooks(clientPtr);
    LOG_DEBUG << "webhooks_webhooks : " << mapper_webhooks_webhooks.count();
    drogon::orm::Mapper<drogon_model::openproject6::WikiContentJournals>
        mapper_wiki_content_journals(clientPtr);
    LOG_DEBUG << "wiki_content_journals : "
              << mapper_wiki_content_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::WikiContents>
        mapper_wiki_contents(clientPtr);
    LOG_DEBUG << "wiki_contents : " << mapper_wiki_contents.count();
    drogon::orm::Mapper<drogon_model::openproject6::WikiPages>
        mapper_wiki_pages(clientPtr);
    LOG_DEBUG << "wiki_pages : " << mapper_wiki_pages.count();
    drogon::orm::Mapper<drogon_model::openproject6::WikiRedirects>
        mapper_wiki_redirects(clientPtr);
    LOG_DEBUG << "wiki_redirects : " << mapper_wiki_redirects.count();
    drogon::orm::Mapper<drogon_model::openproject6::Wikis> mapper_wikis(
        clientPtr);
    LOG_DEBUG << "wikis : " << mapper_wikis.count();
    drogon::orm::Mapper<drogon_model::openproject6::WorkPackageJournals>
        mapper_work_package_journals(clientPtr);
    LOG_DEBUG << "work_package_journals : "
              << mapper_work_package_journals.count();
    drogon::orm::Mapper<drogon_model::openproject6::WorkPackages>
        mapper_work_packages(clientPtr);
    LOG_DEBUG << "work_packages : " << mapper_work_packages.count();
    drogon::orm::Mapper<drogon_model::openproject6::Workflows> mapper_workflows(
        clientPtr);
    LOG_DEBUG << "workflows : " << mapper_workflows.count();
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "clear") {
    sql::Dba::write("delete from public.announcements;");
    sql::Dba::write("delete from public.ar_internal_metadata;");
    sql::Dba::write("delete from public.attachable_journals;");
    sql::Dba::write("delete from public.attachment_journals;");
    sql::Dba::write("delete from public.attachments;");
    sql::Dba::write("delete from public.attribute_help_texts;");
    sql::Dba::write("delete from public.auth_sources;");
    sql::Dba::write("delete from public.categories;");
    sql::Dba::write("delete from public.changes;");
    sql::Dba::write("delete from public.changeset_journals;");
    sql::Dba::write("delete from public.changesets;");
    sql::Dba::write("delete from public.changesets_work_packages;");
    sql::Dba::write("delete from public.colors;");
    sql::Dba::write("delete from public.comments;");
    sql::Dba::write("delete from public.cost_entries;");
    sql::Dba::write("delete from public.cost_object_journals;");
    sql::Dba::write("delete from public.cost_objects;");
    sql::Dba::write("delete from public.cost_queries;");
    sql::Dba::write("delete from public.cost_types;");
    sql::Dba::write("delete from public.custom_actions;");
    sql::Dba::write("delete from public.custom_actions_projects;");
    sql::Dba::write("delete from public.custom_actions_roles;");
    sql::Dba::write("delete from public.custom_actions_statuses;");
    sql::Dba::write("delete from public.custom_actions_types;");
    sql::Dba::write("delete from public.custom_fields;");
    sql::Dba::write("delete from public.custom_fields_projects;");
    sql::Dba::write("delete from public.custom_fields_types;");
    sql::Dba::write("delete from public.custom_options;");
    sql::Dba::write("delete from public.custom_styles;");
    sql::Dba::write("delete from public.custom_values;");
    sql::Dba::write("delete from public.customizable_journals;");
    sql::Dba::write("delete from public.delayed_jobs;");
    sql::Dba::write("delete from public.design_colors;");
    sql::Dba::write("delete from public.document_journals;");
    sql::Dba::write("delete from public.documents;");
    sql::Dba::write("delete from public.done_statuses_for_project;");
    sql::Dba::write("delete from public.enabled_modules;");
    sql::Dba::write("delete from public.enterprise_tokens;");
    sql::Dba::write("delete from public.enumerations;");
    sql::Dba::write("delete from public.export_card_configurations;");
    sql::Dba::write("delete from public.forums;");
    sql::Dba::write("delete from public.grid_widgets;");
    sql::Dba::write("delete from public.grids;");
    sql::Dba::write("delete from public.group_users;");
    sql::Dba::write("delete from public.journal_versions;");
    sql::Dba::write("delete from public.journals;");
    sql::Dba::write("delete from public.labor_budget_items;");
    sql::Dba::write("delete from public.ldap_groups_memberships;");
    sql::Dba::write("delete from public.ldap_groups_synchronized_groups;");
    sql::Dba::write("delete from public.material_budget_items;");
    sql::Dba::write("delete from public.meeting_content_journals;");
    sql::Dba::write("delete from public.meeting_contents;");
    sql::Dba::write("delete from public.meeting_journals;");
    sql::Dba::write("delete from public.meeting_participants;");
    sql::Dba::write("delete from public.meetings;");
    sql::Dba::write("delete from public.member_roles;");
    sql::Dba::write("delete from public.members;");
    sql::Dba::write("delete from public.menu_items;");
    sql::Dba::write("delete from public.message_journals;");
    sql::Dba::write("delete from public.messages;");
    sql::Dba::write("delete from public.news;");
    sql::Dba::write("delete from public.news_journals;");
    sql::Dba::write("delete from public.oauth_access_grants;");
    sql::Dba::write("delete from public.oauth_access_tokens;");
    sql::Dba::write("delete from public.oauth_applications;");
    sql::Dba::write("delete from public.ordered_work_packages;");
    sql::Dba::write("delete from public.plaintext_tokens;");
    sql::Dba::write("delete from public.principal_roles;");
    sql::Dba::write("delete from public.project_associations;");
    sql::Dba::write("delete from public.projects;");
    sql::Dba::write("delete from public.projects_types;");
    sql::Dba::write("delete from public.queries;");
    sql::Dba::write("delete from public.rates;");
    sql::Dba::write("delete from public.recaptcha_entries;");
    sql::Dba::write("delete from public.relations;");
    sql::Dba::write("delete from public.repositories;");
    sql::Dba::write("delete from public.role_permissions;");
    sql::Dba::write("delete from public.roles;");
    sql::Dba::write("delete from public.schema_migrations;");
    sql::Dba::write("delete from public.sessions;");
    sql::Dba::write("delete from public.settings;");
    sql::Dba::write("delete from public.statuses;");
    sql::Dba::write("delete from public.time_entries;");
    sql::Dba::write("delete from public.time_entry_journals;");
    sql::Dba::write("delete from public.tokens;");
    sql::Dba::write("delete from public.two_factor_authentication_devices;");
    sql::Dba::write("delete from public.types;");
    sql::Dba::write("delete from public.user_passwords;");
    sql::Dba::write("delete from public.user_preferences;");
    sql::Dba::write("delete from public.users;");
    sql::Dba::write("delete from public.version_settings;");
    sql::Dba::write("delete from public.versions;");
    sql::Dba::write("delete from public.watchers;");
    sql::Dba::write("delete from public.webhooks_events;");
    sql::Dba::write("delete from public.webhooks_logs;");
    sql::Dba::write("delete from public.webhooks_projects;");
    sql::Dba::write("delete from public.webhooks_webhooks;");
    sql::Dba::write("delete from public.wiki_content_journals;");
    sql::Dba::write("delete from public.wiki_contents;");
    sql::Dba::write("delete from public.wiki_pages;");
    sql::Dba::write("delete from public.wiki_redirects;");
    sql::Dba::write("delete from public.wikis;");
    sql::Dba::write("delete from public.work_package_journals;");
    sql::Dba::write("delete from public.work_packages;");
    sql::Dba::write("delete from public.workflows;");
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else {
    return nullptr;
  }
}

}  // namespace service
}  // namespace todo
