#include "carrierwave/storage/fog"

class FogFileUploader : public CarrierWave::Uploader::Base {
  // include FileUploader
  storage :fog

  // Delete cache and old rack file after store
  // cf. https://github.com/carrierwaveuploader/carrierwave/wiki/How-to:-Delete-cache-garbage-directories

  before :store, :remember_cache_id
  after :store, :delete_tmp_dir
  after :store, :delete_old_tmp_file

   void copy_to(attachment) {
    attachment.remote_file_url = remote_file.url
  }

   void store_dir() {
    "uploads/#{model.class.to_s.underscore}/#{mounted_as}/#{model.id}"
  }

   void remote_file() {
    this->remote_file || file
  }

   void local_file() {
    this->remote_file ||= file
    cache_stored_file!
    super
  }

   void download_url(options = {}) {
    url_options = {}

    if ( options[:content_disposition].present?) {
      url_options[:query] = {
        // Passing this option to S3 will make it serve the file with the
        // respective content disposition. Without it no content disposition
        // header is sent. This only works for S3 but we don't support
        // anything else anyway (see carrierwave.rb).
        "response-content-disposition" => options[:content_disposition]
      }
    }

    remote_file.url url_options
  }

  //
  // Checks if this file exists and is readable in the remote storage.
  //
  // In the current version of carrierwave the call to #exists?
  // throws an error if the file does not exist:
  //
  //   Excon::Errors::Forbidden: Expected(200) <=> Actual(403 Forbidden)
   void readable?() {
    remote_file&.exists?
  rescue Excon::Errors::Forbidden
    false
  }
}
