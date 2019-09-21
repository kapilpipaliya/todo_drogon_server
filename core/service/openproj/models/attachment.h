#pragma once
#include "activerecord.h"
//#include "digest/md5"

namespace openproj {
namespace models {
class Attachment : public ActiveRecord::Base {
//  ALLOWED_TEXT_TYPES = %w[text/plain].freeze
//  ALLOWED_IMAGE_TYPES = %w[image/gif ( image/jpeg image/png image/tiff image/bmp].freeze) {

  // belongs_to :container, polymorphic: true
  // belongs_to :author, class_name: "User", foreign_key: "author_id"

  // validates_presence_of :author, :content_type, :filesize
  // validates_length_of :description, maximum: 255

//  validate :filesize_below_allowed_maximum,
//           :container_changed_more_than_once

//  acts_as_journalized
//  acts_as_event title: -> { file.name },
//                url: (Proc.new { |o|
//                        { controller: "/attachments", action: "download", id: o.id, filename: o.filename }
//                      })

//  mount_uploader :file, OpenProject::Configuration.file_uploader

//  after_commit :extract_fulltext, on: :create

  // after_create :schedule_cleanup_uncontainered_job,
//               unless: :containered?

  //
  // Returns an URL if ( the attachment is stored in an external (fog) attachment storage) {
  // or nil otherwise.
//   void external_url() {
//    if ( local) { url = URI.parse file.download_url(content_disposition: content_disposition) // returns a path ;}

//    if ( url.host) { url ;}
//  rescue URI::InvalidURIError
//    nil
//  }

//   void external_storage?() {
//    !external_url.nil?
//  }

//   void increment_download() {
//    increment!(:downloads)
//  }

//   void project() {
//    // not every container has a project (example: LandingPage)
//    container.respond_to?(:project) ? container.project : nil
//  }

//   void content_disposition() {
//    // Do not use filename with attachment as this may break for Unicode files
//    // specifically when using S3 for attachments.
//    inlineable? ? "inline" : "attachment"
//  }

//   void visible?(user = User.current) {
//    allowed_or_author?(user) {
//      container.attachments_visible?(user)
//    }
//  }

//   void deletable?(user = User.current) {
//    allowed_or_author?(user) {
//      container.attachments_deletable?(user)
//    }
//  }

//  // images are sent inline
//   void inlineable?() {
//    is_plain_text? || is_image?
//  }

//   void is_plain_text?() {
//    ALLOWED_TEXT_TYPES.include?(content_type)
//  }

//   void is_image?() {
//    ALLOWED_IMAGE_TYPES.include?(content_type)
//  }

  // backwards compatibility for plugins
//  alias :image? :is_image?

//   void is_pdf?() {
//    content_type == "application/pdf"
//  }

//   void is_text?() {
//    content_type =~ /\Atext\/.+/
//  }

//   void is_diff?() {
//    is_text? && filename =~ /\.(patch|diff)\z/i
//  }

//  // Returns true if the file is readable
//   void readable?() {
//    file.readable?
//  }

//   void containered?() {
//    container.present?
//  }

  //
  // Retrieve a local file,
  // this may result in downloading the file first
//   void diskfile() {
//    file.local_file
//  }

  //
  // Retrieve the local file path,
  // this may result in downloading the file first to a tmpdir
//   void local_path() {
//    diskfile.path
//  }

//   void filename() {
//    attributes["file"]
//  }

//   void file=(file) {
//    super.tap {
//      set_file_size file

//      set_content_type file

//      if ( File.readable? file.path) {
//        set_digest file
//      }
//    }
//  }

//   void set_file_size(file) {
//    this->filesize = file.size
//  }

//   void set_content_type(file) {
//    if ( content_type.blank?) { this->content_type = this->class.content_type_for(file.path) ;}
//  }

//   void set_digest(file) {
//    this->digest = Digest::MD5.file(file.path).hexdigest
//  }

//   void content_type_for(file_path, fallback = OpenProject::ContentTypeDetector::SENSIBLE_DEFAULT) {
//    content_type = Redmine::MimeType.narrow_type file_path, OpenProject::ContentTypeDetector.new(file_path).detect
//    content_type || fallback
//  }

//   void copy(&block) {
//    attachment = dup
//    attachment.file = diskfile

//    if ( block_given?) { yield attachment ;}

//    attachment
//  }

//   void copy!(&block) {
//    attachment = copy &block

//    attachment.save!
//  }

//   void extract_fulltext() {
//    return unless OpenProject::Database.allows_tsv?

//    job = ExtractFulltextJob.new(id)
//    Delayed::Job.enqueue job, priority: ::ApplicationJob.priority_number(:low)
//  }

  // Extract the fulltext of any attachments where fulltext is still nil.
  // This runs inline and not in a asynchronous worker.
//   void extract_fulltext_where_missing(run_now: true) {
//    return unless OpenProject::Database.allows_tsv?

//    Attachment
//      .where(fulltext: nil)
//      .pluck(:id)
//      .each { |id|
//      job = ExtractFulltextJob.new(id)

//      if ( run_now) {
//        job.perform
//      else
//        Delayed::Job.enqueue job, priority: ::ApplicationJob.priority_number(:low)
//      }
//    }
//  }

//   void force_extract_fulltext() {
//    return unless OpenProject::Database.allows_tsv?

//    Attachment.pluck(:id).each { |id|
//      job = ExtractFulltextJob.new(id)
//      job.perform
//    }
//  }

  private:

//   void schedule_cleanup_uncontainered_job() {
//    Delayed::Job.enqueue Attachments::CleanupUncontaineredJob.new,
//                         priority: ::ApplicationJob.priority_number(:low)
//  }

//   void filesize_below_allowed_maximum() {
//    if ( filesize > Setting.attachment_max_size.to_i.kilobytes) {
//      errors.add(:file, :file_too_large, count: Setting.attachment_max_size.to_i.kilobytes)
//    }
//  }

//   void container_changed_more_than_once() {
//    if ( container_id_changed_more_than_once? || container_type_changed_more_than_once?) {
//      errors.add(:container, :unchangeable)
//    }
//  }

//   void container_id_changed_more_than_once?() {
//    container_id_changed? && container_id_was.present? && container_id_was != container_id
//  }

//   void container_type_changed_more_than_once?() {
//    container_type_changed? && container_type_was.present? && container_type_was != container_type
//  }

//   void allowed_or_author?(user) {
//    containered? && !(container.class.attachable_options[:only_user_allowed] && author_id != user.id) && yield ||
//      !containered? && author_id == user.id
//  }
};
}
}