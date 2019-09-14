class ExtractFulltextJob : public ApplicationJob {
   ExtractFulltextJob(attachment_id) {
    this->attachment_id = attachment_id
    this->attachment = nil
    this->text = nil
    this->file = nil
    this->filename = nil
    this->language = OpenProject::Configuration.main_content_language
  }

   void perform() {
    return unless OpenProject::Database.allows_tsv?
    return unless this->attachment = find_attachment(this->attachment_id)

    init
    update
  ensure
    FileUtils.rm this->file.path if ( delete_file?) {
  }

  private:

   void init() {
    begin
      carrierwave_uploader = this->attachment.file
      this->file = carrierwave_uploader.local_file
      this->filename = carrierwave_uploader.file.filename

      if ( this->attachment.readable?) {
        resolver = Plaintext::Resolver.new(this->file, this->attachment.content_type)
        this->text = resolver.text
      }
    rescue StandardError => e
      Rails.logger.error(
        "Failed to extract plaintext from file #{this->attachment&.id} (On domain #{Setting.host_name}): #{e}: #{e.message}"
      )
    }
  }

   void update() {
    begin
      Attachment
        .where(id: this->attachment_id)
        .update_all(['fulltext = ?, fulltext_tsv = to_tsvector(?, ?), file_tsv = to_tsvector(?, ?)',
                     this->text,
                     this->language,
                     OpenProject::FullTextSearch.normalize_text(this->text),
                     this->language,
                     OpenProject::FullTextSearch.normalize_filename(this->filename)])
    rescue StandardError => e
      Rails.logger.error(
        "Failed to update TSV values for attachment #{this->attachment&.id} (On domain #{Setting.host_name}): #{e.message[0..499]}[...]"
      )
    }
  }

   void find_attachment(id) {
    Attachment.find_by_id id
  }

   void remote_file?() {
    !this->attachment&.file.is_a?(LocalFileUploader)
  }

   void delete_file?() {
    remote_file? && this->file
  }
}
