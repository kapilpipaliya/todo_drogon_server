#pragma once
//#include "open_project/scm/adapters/git"
#include "../repository.h"
namespace openproj {
namespace models {
namespace RepositoryN{
class Git : public Repository {
  // validates_presence_of :url
//  validate :validity_of_local_url

//   void scm_adapter_class() {
//    OpenProject::Scm::Adapters::Git
//  }

//   void configure(scm_type, _args) {
//    if ( scm_type == this->class.managed_type) {
//      unless manageable?
//        raise OpenProject::Scm::Exceptions::RepositoryBuildError.new(
//          I18n.t("repositories.managed.error_not_manageable")
//        )
//      }

//      this->root_url = managed_repository_path
//      this->url = managed_repository_url
//    }
//  }

//   void permitted_params(params) {
//    super(params).merge(params.permit(:path_encoding))
//  }

//   void supported_types() {
//    types = [:local]
//    if ( manageable?) { types << managed_type ;}

//    types
//  }

//   void managed_repo_created() {
//    scm.initialize_bare_git
//  }

//   void repository_identifier() {
//    "#{super}.git"
//  }

//   void repository_type() {
//    "Git"
//  }

  //
  // Git doesn"t like local urls when visiting
  // the repository, thus always use the path.
//   void managed_repository_url() {
//    managed_repository_path
//  }

//   void supports_directory_revisions?() {
//    true
//  }

//   void repo_log_encoding() {
//    "UTF-8"
//  }

//   void authorization_policy() {
//    ::Scm::GitAuthorizationPolicy
//  }

  // Returns the identifier for the given git changeset
//   void changeset_identifier(changeset) {
//    changeset.scmid
//  }

  // Returns the readable identifier for the given git changeset
//   void format_changeset_identifier(changeset) {
//    format_revision(changeset.revision)
//  }

//   void format_revision(revision) {
//    revision[0, 8]
//  }

//   void branches() {
//    scm.branches
//  }

//   void tags() {
//    scm.tags
//  }

//   void find_changeset_by_name(name) {
//    if ( name.nil? || name.empty?) { return nil ;}
//    e = changesets.where(["revision = ?", name.to_s]).first
//    if ( e) { return e ;}
//    changesets.where(["scmid LIKE ?", "#{name}%"]).first
//  }

  // With SCM"s that have a sequential commit numbering, redmine is able to be
  // clever and only fetch changesets going forward from the most recent one
  // it knows about.  However, with git, you never know if people have merged
  // commits into the middle of the repository history, so we should parse
  // the entire log. Since it"s way too slow for large repositories, we only
  // parse 1 week before the last known commit.
  // The repository can still be fully reloaded by calling #clear_changesets
  // before fetching changesets (eg. for offline resync)
//   void fetch_changesets() {
//    c = changesets.order(Arel.sql("committed_on DESC")).first
//    since = (c ? c.committed_on - 7.days : nil)

//    revisions = scm.revisions("", nil, nil, all: true, since: since, reverse: true)
//    if ( revisions.nil? || revisions.empty?) { return ;}

//    recent_changesets = changesets.where(["committed_on >= ?", since])

//    // Clean out revisions that are no longer in git
//    recent_changesets.each { |c| c.destroy unless revisions.detect { |r| r.scmid.to_s == c.scmid.to_s } }

//    // Subtract revisions that redmine already knows about
//    recent_revisions = recent_changesets.map(&:scmid)
//    revisions.reject! { |r| recent_revisions.include?(r.scmid) }

//    // Save the remaining ones to the database
//    unless revisions.nil?
//      revisions.each { |rev|
//        transaction {
//          changeset = Changeset.new(
//            repository: self,
//            revision:   rev.identifier,
//            scmid:      rev.scmid,
//            committer:  rev.author,
//            committed_on: rev.time,
//            comments:   rev.message)

//          if ( changeset.save) {
//            rev.paths.each { |file|
//              Change.create(
//                changeset: changeset,
//                action:    file[:action],
//                path:      file[:path])
//            }
//          }
//        }
//      }
//    }
//  }

//   void latest_changesets(path, rev, limit = 10) {
//    revisions = scm.revisions(path, nil, rev, limit: limit, all: false)
//    if ( revisions.nil? || revisions.empty?) { return [] ;}

//    changesets.where(["scmid IN (?)", revisions.map!(&:scmid)])
//      .order(Arel.sql("committed_on DESC"))
//  }

  private:

   void validity_of_local_url() {
//    parsed = URI.parse root_url.presence || url
//    if ( parsed.scheme == "ssh") {
//      errors.add :url, :must_not_be_ssh
//    }
//  rescue => e
//    Rails.logger.error "Failed to parse repository url for validation: #{e}"
//    errors.add :url, :invalid_url
  }
};
}
}

}