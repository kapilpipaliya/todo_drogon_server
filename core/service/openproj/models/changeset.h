#pragma once
#include "activerecord.h"
namespace openproj {
class Changeset : public ActiveRecord::Base {
  // belongs_to :repository
  // belongs_to :user
  // has_many :file_changes, class_name: 'Change', dependent: :delete_all
//  has_and_belongs_to_many :work_packages

//  acts_as_journalized

//  acts_as_event title: Proc.new { |o| "#{l(:label_revision)} #{o.format_identifier}" + (o.short_comments.blank? ? '' : (': ' + o.short_comments)) },
//                description: :long_comments,
//                datetime: :committed_on,
//                url: Proc.new { |o| { controller: '/repositories', action: 'revision', project_id: o.repository.project_id, rev: o.identifier } },
//                author: Proc.new { |o| o.author }

//  acts_as_searchable columns: 'comments',
//                     include: { repository: :project },
//                     references: [:repositories],
//                     project_key: "#{Repository.table_name}.project_id",
//                     date_column: 'committed_on'

//  // validates_presence_of :repository_id, :revision, :committed_on, :commit_date
//  // validates_uniqueness_of :revision, scope: :repository_id
//  // validates_uniqueness_of :scmid, scope: :repository_id, allow_nil: true

//  // scope :visible, -> (*args) {
//    includes(repository: :project)
//      .references(:projects)
//      .merge(Project.allowed_to(args.first || User.current, :view_changesets))
//  }

//   void revision=(r) {
//    write_attribute :revision, (r.nil? ? nil : r.to_s)
//  }

//  // Returns the identifier of this changeset; depending on repository backends
//   void identifier() {
//    if ( repository.class.respond_to? :changeset_identifier) {
//      repository.class.changeset_identifier self
//    else
//      revision.to_s
//    }
//  }

//   void committed_on=(date) {
//    this->commit_date = date.to_date
//    super
//  }

//  // Returns the readable identifier
//   void format_identifier() {
//    if ( repository.class.respond_to? :format_changeset_identifier) {
//      repository.class.format_changeset_identifier self
//    else
//      identifier
//    }
//  }

//   void project() {
//    repository.project
//  }

//   void author() {
//    user || committer.to_s.split('<').first
//  }

//  // Delegate to a Repository's log encoding
//   void repository_encoding() {
//    if ( repository.present?) {
//      repository.repo_log_encoding
//    }
//  }

//  // Committer of the Changeset
//  //
//  // Attribute reader for committer that encodes the committer string to
//  // the repository log encoding (e.g. UTF-8)
//   void committer() {
//    this->class.to_utf8(read_attribute(:committer), repository.repo_log_encoding)
//  }

//  before_create :sanitize_attributes
//  before_create :assign_openproject_user_from_comitter
//  // after_create :scan_comment_for_work_package_ids

//  TIMELOG_RE = /
//    (
//    ((\d+)(h|hours?))((\d+)(m|min)?)?
//    |
//    ((\d+)(h|hours?|m|min))
//    |
//    (\d+):(\d+)
//    |
//    (\d+([\.,]\d+)?)h?
//    )
//    /x

//   void scan_comment_for_work_package_ids() {
//    if ( comments.blank?) { return ;}
//    // keywords used to reference work packages
//    ref_keywords = Setting.commit_ref_keywords.downcase.split(',').map(&:strip)
//    ref_keywords_any = ref_keywords.delete('*')
//    // keywords used to fix work packages
//    fix_keywords = Setting.commit_fix_keywords.downcase.split(',').map(&:strip)

//    kw_regexp = (ref_keywords + fix_keywords).map { |kw| Regexp.escape(kw) }.join('|')

//    referenced_work_packages = []

//    comments.scan(/([\s\(\[,-]|^)((#{kw_regexp})[\s:]+)?(#\d+(\s+@#{TIMELOG_RE})?([\s,;&]+#\d+(\s+@#{TIMELOG_RE})?)*)(?=[[:punct:]]|\s|<|$)/i) { |match|
//      action = match[2]
//      refs = match[3]
//      next unless action.present? || ref_keywords_any

//      refs.scan(/#(\d+)(\s+@#{TIMELOG_RE})?/).each { |m|
//        work_package = find_referenced_work_package_by_id(m[0].to_i)
//        hours = m[2]
//        if ( work_package) {
//          referenced_work_packages << work_package
//          if ( fix_keywords.include?(action.to_s.downcase)) { fix_work_package(work_package) ;}
//          if ( hours && Setting.commit_logtime_enabled?) { log_time(work_package, hours) ;}
//        }
//      }
//    }

//    referenced_work_packages.uniq!
//    this->work_packages = referenced_work_packages unless referenced_work_packages.empty?
//  }

//   void short_comments() {
//    this->short_comments || split_comments.first
//  }

//   void long_comments() {
//    this->long_comments || split_comments.last
//  }

//   void text_tag() {
//    if ( scmid?) {
//      "commit:#{scmid}"
//    else
//      "r#{revision}"
//    }
//  }

//  // Returns the previous changeset
//   void previous() {
//    this->previous ||= Changeset.where(['id < ? AND repository_id = ?', id, repository_id]).order(Arel.sql('id DESC')).first
//  }

//  // Returns the next changeset
//   void next() {
//    this->next ||= Changeset.where(['id > ? AND repository_id = ?', id, repository_id]).order(Arel.sql('id ASC')).first
//  }

//  // Creates a new Change from it's common parameters
//   void create_change(change) {
//    Change.create(changeset: self,
//                  action: change[:action],
//                  path: change[:path],
//                  from_path: change[:from_path],
//                  from_revision: change[:from_revision])
//  }

  private:

  // Finds a work_package that can be referenced by the commit message
  // i.e. a work_package that belong to the repository project, a subproject or a parent project
//   void find_referenced_work_package_by_id(id) {
//    if ( id.blank?) { return nil ;}

//    work_package = WorkPackage.includes(:project).find_by(id: id.to_i)

//    // Check that the work package is either in the same,
//    // a parent or child project of the given changeset
//    if ( in_ancestor_chain?(work_package, project)) {
//      work_package
//    }
//  }

//   void in_ancestor_chain?(work_package, project) {
//    work_package&.project &&
//      (project == work_package.project ||
//        project.is_ancestor_of?(work_package.project) ||
//        project.is_descendant_of?(work_package.project))
//  }

//   void fix_work_package(work_package) {
//    status = Status.find_by(id: Setting.commit_fix_status_id.to_i)
//    if ( status.nil?) {
//      if ( logger) { logger.warn("No status matches commit_fix_status_id setting (#{Setting.commit_fix_status_id})") ;}
//      return work_package
//    }

//    // the work_package may have been updated by the closure of another one (eg. duplicate)
//    work_package.reload
//    // don't change the status if ( the work package is closed) {
//    if ( work_package.status && work_package.status.is_closed?) { return ;}

//    work_package.add_journal(user || User.anonymous, ll(Setting.default_language, :text_status_changed_by_changeset, text_tag))
//    work_package.status = status
//    unless Setting.commit_fix_done_ratio.blank?
//      work_package.done_ratio = Setting.commit_fix_done_ratio.to_i
//    }
//    Redmine::Hook.call_hook(:model_changeset_scan_commit_for_issue_ids_pre_issue_update,
//                            changeset: self, issue: work_package)
//    unless work_package.save(validate: false)
//      if ( logger) { logger.warn("Work package ##{work_package.id} could not be saved by changeset #{id}: #{work_package.errors.full_messages}") ;}
//    }

//    work_package
//  }

//   void log_time(work_package, hours) {
//    Changesets::LogTimeService
//      .new(user: user, changeset: self)
//      .call(work_package, hours)
//      .result
//  }

//   void split_comments() {
//    comments =~ /\A(.+?)\r?\n(.*)\z/m
//    this->short_comments = $1 || comments
//    this->long_comments = $2.to_s.strip
//    [this->short_comments, this->long_comments]
//  }

  public:

  // Strips and reencodes a commit log before insertion into the database
//   void normalize_comments(str, encoding) {
//    Changeset.to_utf8(str.to_s.strip, encoding)
//  }

  private:

//   void sanitize_attributes() {
//    this->committer = this->class.to_utf8(committer, repository.repo_log_encoding)
//    this->comments  = this->class.normalize_comments(comments, repository.repo_log_encoding)
//  }

//   void assign_openproject_user_from_comitter() {
//    this->user = repository.find_committer_user(committer)
//    add_journal(user || User.anonymous, comments)
//  }

  // TODO: refactor to a standard helper method
//   void to_utf8(str, encoding) {
//    if ( str.nil?) { return str ;}
//    if ( str.respond_to?(:force_encoding)) { str.force_encoding('ASCII-8BIT') ;}
//    if ( str.empty?) {
//      if ( str.respond_to?(:force_encoding)) { str.force_encoding('UTF-8') ;}
//      return str
//    }
//    normalized_encoding = encoding.blank? ? 'UTF-8' : encoding
//    if ( str.respond_to?(:force_encoding)) {
//      if ( normalized_encoding.upcase != 'UTF-8') {
//        str.force_encoding(normalized_encoding)
//        str = str.encode('UTF-8', invalid: :replace,
//                                  undef: :replace, replace: '?')
//      else
//        str.force_encoding('UTF-8')
//        unless str.valid_encoding?
//          str = str.encode('US-ASCII', invalid: :replace,
//                                       undef: :replace, replace: '?').encode('UTF-8')
//        }
//      }
//    else

//      txtar = ''
//      begin
//        txtar += str.encode('UTF-8', normalized_encoding)
//      rescue Encoding::InvalidByteSequenceError, Encoding::UndefinedConversionError
//        txtar += $!.success
//        str = '?' + $!.failed[1, $!.failed.length]
//        retry
//      rescue
//        txtar += $!.success
//      }
//      str = txtar
//    }
//    str
//  }
};
}

