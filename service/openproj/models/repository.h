#pragma once
#include "activerecord.h"
#include "Repositories.h"
namespace openproj {
namespace models {
class Repository : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::Repositories {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Repositories> mapper_repositories(clientPtr);
    drogon_model::openproject6::Repositories* repositories = this;
    mapper_repositories.insert(*repositories);
  }
  // include Redmine::Ciphering
  // include OpenProject::Scm::ManageableRepository

  // belongs_to :project
  // has_many :changesets, -> {
//    order("#{Changeset.table_name}.committed_on DESC, #{Changeset.table_name}.id DESC")
//  }

//  before_save :sanitize_urls

//  // Managed repository lifetime
//  // after_create :create_managed_repository, if (: Proc.new { |repo| repo.managed? }) {
//  after_destroy :delete_managed_repository, if (: Proc.new { |repo| repo.managed? }) {

//  // Raw SQL to delete changesets and changes in the database
//  // has_many :changesets, dependent: :destroy is too slow for big repositories
//  before_destroy :clear_changesets

//  // validates_length_of :password, maximum: 255, allow_nil: true
//  validate :validate_enabled_scm, on: :create

//   void file_changes() {
//    Change.where(changeset_id: changesets).joins(:changeset)
//  }

//  // Checks if ( the SCM is enabled when creating a repository) {
//   void validate_enabled_scm() {
//    errors.add(:type, :not_available) unless OpenProject::Scm::Manager.enabled?(vendor)
//  }

//  // Removes leading and trailing whitespace
//   void url=(arg) {
//    write_attribute(:url, arg ? arg.to_s.strip : nil)
//  }

//  // Removes leading and trailing whitespace
//   void root_url=(arg) {
//    write_attribute(:root_url, arg ? arg.to_s.strip : nil)
//  }

//   void password() {
//    read_ciphered_attribute(:password)
//  }

//   void password=(arg) {
//    write_ciphered_attribute(:password, arg)
//  }

//   void scm_adapter() {
//    this->class.scm_adapter_class
//  }

//   void scm() {
//    this->scm ||= scm_adapter.new(
//      url, root_url,
//      login, password, path_encoding,
//      project.identifier
//    )

//    // override the adapter"s root url with the full url
//    // if ( none other was set.) {
//    unless this->scm.root_url.present?
//      this->scm.root_url = root_url.presence || url
//    }

//    this->scm
//  }

//   void authorization_policy() {
//    nil
//  }

//   void scm_config() {
//    scm_adapter_class.config
//  }

//   void available_types() {
//    supported_types - disabled_types
//  }

//  //
//  // Retrieves the :disabled_types setting from `configuration.yml
//  // To avoid wrong set operations for string-based configuration, force them to symbols.
//   void disabled_types() {
//    (scm_config[:disabled_types] || []).map(&:to_sym)
//  }

//   void vendor() {
//    this->class.vendor
//  }

//   void supports_cat?() {
//    scm.supports_cat?
//  }

//   void supports_annotate?() {
//    scm.supports_annotate?
//  }

//   void supports_all_revisions?() {
//    true
//  }

//   void supports_directory_revisions?() {
//    false
//  }

//   void supports_checkout_info?() {
//    true
//  }

//   void requires_checkout_base_url?() {
//    true
//  }

//   void entry(path = nil, identifier = nil) {
//    scm.entry(path, identifier)
//  }

//   void entries(path = nil, identifier = nil, limit: nil) {
//    entries = scm.entries(path, identifier)

//    if ( limit && limit < entries.size) {
//      result = OpenProject::Scm::Adapters::Entries.new entries.take(limit)
//      result.truncated = entries.size - result.size

//      result
//    else
//      entries
//    }
//  }

//   void branches() {
//    scm.branches
//  }

//   void tags() {
//    scm.tags
//  }

//   void default_branch() {
//    scm.default_branch
//  }

//   void properties(path, identifier = nil) {
//    scm.properties(path, identifier)
//  }

//   void cat(path, identifier = nil) {
//    scm.cat(path, identifier)
//  }

//   void diff(path, rev, rev_to) {
//    scm.diff(path, rev, rev_to)
//  }

//   void diff_format_revisions(cs, cs_to, sep = ":") {
//    text = ""
//    if ( cs_to) { text << cs_to.format_identifier + sep ;}
//    if ( cs) { text << cs.format_identifier ;}
//    text
//  }

//  // Returns a path relative to the url of the repository
//   void relative_path(path) {
//    path
//  }

//  //
//  // Update the required storage information, when necessary.
//  // Returns whether an asynchronous count refresh has been requested.
//   void update_required_storage() {
//   if ( scm.storage_available?) {  ;}
//      oldest_cachable_time = Setting.repository_storage_cache_minutes.to_i.minutes.ago
//      if ( storage_updated_at.nil? ||) {
//         storage_updated_at < oldest_cachable_time

//        Delayed::Job.enqueue ::Scm::StorageUpdaterJob.new(self), priority: ::ApplicationJob.priority_number(:low)
//        return true
//      }
//    }

//    false
//  }

  // Finds and returns a revision with a number or the beginning of a hash
//   void find_changeset_by_name(name) {
//    name = name.to_s
//    if ( name.blank?) { return nil ;}
//    changesets.where((name.match(/\A\d*\z/) ? ["revision = ?", name] : ["revision LIKE ?", name + "%"])).first
//  }

//   void latest_changeset() {
//    this->latest_changeset ||= changesets.first
//  }

//  // Returns the latest changesets for +path+
//  // Default behaviour is to search in cached changesets
//   void latest_changesets(path, _rev, limit = 10) {
//    if ( path.blank?) {
//      changesets.includes(:user)
//        .order("#{Changeset.table_name}.committed_on DESC, #{Changeset.table_name}.id DESC")
//        .limit(limit)
//    else
//      changesets.includes(changeset: :user)
//        .where(["path = ?", path.with_leading_slash])
//        .order("#{Changeset.table_name}.committed_on DESC, #{Changeset.table_name}.id DESC")
//        .limit(limit)
//        .map(&:changeset)
//    }
//  }

//   void scan_changesets_for_work_package_ids() {
//    changesets.each(&:scan_comment_for_work_package_ids)
//  }

//  // Returns an array of committers usernames and associated user_id
//   void committers() {
//    this->committers ||= Changeset.where(repository_id: id).distinct.pluck(:committer, :user_id)
//  }

//  // Maps committers username to a user ids
//   void committer_ids=(h) {
//    if ( h.is_a?(Hash)) {
//      committers.each { |committer, user_id|
//        new_user_id = h[committer]
//        if ( new_user_id && (new_user_id.to_i != user_id.to_i)) {
//          new_user_id = (new_user_id.to_i > 0 ? new_user_id.to_i : nil)
//          Changeset.where(["repository_id = ? AND committer = ?", id, committer])
//            .update_all("user_id = #{new_user_id.nil? ? "NULL" : new_user_id}")
//        }
//      }
//      this->committers = nil
//      this->found_committer_users = nil
//      true
//    else
//      false
//    }
//  }

  // Returns the Redmine User corresponding to the given +committer+
  // It will return nil if ( the committer is not yet mapped and if no User) {
  // with the same username or email was found
//   void find_committer_user(committer) {
//    unless committer.blank?
//      this->found_committer_users ||= {}
//      if ( this->found_committer_users.has_key?(committer)) { return this->found_committer_users[committer] ;}

//      user = nil
//      c = changesets.includes(:user).references(:users).find_by(committer: committer)
//      if ( c && c.user) {
//        user = c.user
//      } else if ( committer.strip =~ /\A([^<]+)(<(.*)>)?\z/) {
//        username = $1.strip
//        email = $3
//        u = User.find_by_login(username)
//        u ||= User.find_by_mail(email) unless email.blank?
//        user = u
//      }
//      this->found_committer_users[committer] = user
//      user
//    }
//  }

//   void repo_log_encoding() {
//    encoding = log_encoding.to_s.strip
//    encoding.blank? ? "UTF-8" : encoding
//  }

  // Fetches new changesets for all repositories of active projects
  // Can be called periodically by an external script
  // eg. ruby script/runner "Repository.fetch_changesets"
//   void fetch_changesets() {
//    Project.active.has_module(:repository).includes(:repository).each { |project|
//      if ( project.repository) {
//        begin
//          project.repository.fetch_changesets
//        rescue OpenProject::Scm::Exceptions::CommandFailed => e
//          logger.error "scm: error during fetching changesets: #{e.message}"
//        }
//      }
//    }
//  }

  // scan changeset comments to find related and fixed work packages for all repositories
//   void scan_changesets_for_work_package_ids() {
//    all.each(&:scan_changesets_for_work_package_ids)
//  }


  //
  // Builds a model instance of type +Repository::#{vendor}+ with the given parameters.
  //
  // @param [Project] project The project this repository belongs to.
  // @param [Symbol] vendor   The SCM vendor symbol (e.g., :git, :subversion)
  // @param [Hash] params     Custom parameters for this SCM as delivered from the repository
  //                          field.
  //
  // @param [Symbol] type     SCM tag to determine the type this repository should be built as
  //
  // this->raise [OpenProject::Scm::RepositoryBuildError]
  //                                  Raised when the instance could not be built
  //                                  given the parameters.
  // this->raise [::NameError] Raised when the given +vendor+ could not be resolved to a class.
//   void build(project, vendor, params, type) {
//    klass = build_scm_class(vendor)

//    // We can"t possibly know the form fields this particular vendor
//    // desires, so we allow it to filter them from raw params
//    // before building the instance with it.
//    args = klass.permitted_params(params)

//    repository = klass.new(args)
//    repository.attributes = args
//    repository.project = project

//    set_verified_type!(repository, type) unless type.nil?

//    repository.configure(type, args)

//    repository
//  }

  //
  // Build a temporary model instance of the given vendor for temporary use in forms.
  // Will not receive any args.
//   void build_scm_class(vendor) {
//    klass = OpenProject::Scm::Manager.registered[vendor]

//    if ( klass.nil?) {
//      raise OpenProject::Scm::Exceptions::RepositoryBuildError.new(
//        I18n.t("repositories.errors.disabled_or_unknown_vendor", vendor: vendor)
//      )
//    else
//      klass
//    }
//  }

//  //
//  // Verifies that the chosen scm type can be selected
//   void set_verified_type!(repository, type) {
//    if ( repository.class.available_types.include? type) {
//      repository.scm_type = type
//    else
//      raise OpenProject::Scm::Exceptions::RepositoryBuildError.new(
//        I18n.t("repositories.errors.disabled_or_unknown_type",
//               type: type,
//               vendor: repository.vendor)
//      )
//    }
//  }

  //
  // Allow global permittible params. May be overridden by plugins
//   void permitted_params(params) {
//    params.permit(:url)
//  }

//   void scm_adapter_class() {
//    nil
//  }

//   void enabled?() {
//    OpenProject::Scm::Manager.enabled?(vendor)
//  }

  //
  // Returns the SCM vendor symbol for this repository
  // e.g., Repository::Git => :git
   void vendor() {
//    vendor_name.underscore.to_sym
  }

  //
  // Returns the SCM vendor name for this repository
  // e.g., Repository::Git => Git
   void vendor_name() {
//    name.demodulize
  }

  // Strips url and root_url
   void sanitize_urls() {
//    if ( url.present?) { url.strip! ;}
//    if ( root_url.present?) { root_url.strip! ;}
//    true
  }

   void clear_changesets() {
//    cs = Changeset.table_name
//    ch = Change.table_name
//    ci = "#{table_name_prefix}changesets_work_packages#{table_name_suffix}"
//    this->class.connection.delete("DELETE FROM #{ch} WHERE #{ch}.changeset_id IN (SELECT #{cs}.id FROM #{cs} WHERE #{cs}.repository_id = #{id})")
//    this->class.connection.delete("DELETE FROM #{ci} WHERE #{ci}.changeset_id IN (SELECT #{cs}.id FROM #{cs} WHERE #{cs}.repository_id = #{id})")
//    this->class.connection.delete("DELETE FROM #{cs} WHERE #{cs}.repository_id = #{id}")
  }

  protected:

  //
  // Create local managed repository request when the built instance
  // is managed by OpenProject
   void create_managed_repository() {
//    service = Scm::CreateManagedRepositoryService.new(self)
//    if ( service.call) {
//      true
//    else
//      raise OpenProject::Scm::Exceptions::RepositoryBuildError.new(
//        service.localized_rejected_reason
//      )
//    }
  }

  //
  // Destroy local managed repository request when the built instance
  // is managed by OpenProject
   void delete_managed_repository() {
//    service = Scm::DeleteManagedRepositoryService.new(self)
//    if ( service.call) {
//      true
//    else
//      errors.add(:base, service.localized_rejected_reason)
//      raise ActiveRecord::Rollback
//    }
  }
};
}

}
