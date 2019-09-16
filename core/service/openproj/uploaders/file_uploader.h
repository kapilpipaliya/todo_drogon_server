#pragma once
namespace openproj {
namespace uploader {
namespace FileUploader {
//   void included(base) {
//    base.extend ClassMethods
//  }

  //
  // Returns an URL if the attachment is stored in an external (fog) attachment storage
  // or nil otherwise.
//   void external_url() {
//    url = URI.parse download_url
//    if ( url.host) { url ;}
//  rescue URI::InvalidURIError
//    nil
//  }

//   void external_storage?() {
//    !external_url.nil?
//  }

//   void local_file() {
//    file.to_file
//  }

//   void download_url(options = {}) {
//    file.is_path? ? file.path : file.url
//  }

//   void cache_dir() {
//    this->class.cache_dir
//  }

//   void readable?() {
//    return false unless file && local_file

//    File.readable?(local_file)
//  }

//   // store! nil's the cache_id after it finishes so we need to remember it for deletion
//  void remember_cache_id(_new_file) {
//    this->cache_id_was = cache_id
//  }

//   void delete_tmp_dir(_new_file) {
//    // make sure we don't delete other things accidentally by checking the name pattern
//    if ( this->cache_id_was.present? && this->cache_id_was =~ /\A[\d]{8}\-[\d]{4}\-[\d]+\-[\d]{4}\z/) {
//      FileUtils.rm_rf(File.join(cache_dir, this->cache_id_was))
//    }
//  rescue => e
//    Rails.logger.error "Failed cleanup of upload file #{this->cache_id_was}: #{e}"
//  }

//  // remember the tmp file
//   void cache!(new_file = sanitized_file) {
//    super
//    this->old_tmp_file = new_file
//  rescue => e
//    Rails.logger.error "Failed cache! of temporary upload file: #{e}"
//  }

//   void delete_old_tmp_file(_dummy) {
//    this->old_tmp_file.try :delete
//  rescue => e
//    Rails.logger.error "Failed cleanup of temporary upload file: #{e}"
//  }

  namespace ClassMethods {
     void cache_dir() {
//      this->cache_dir ||= File.join(Dir.tmpdir, 'op_uploaded_files')
    }
  }
}
}
}
