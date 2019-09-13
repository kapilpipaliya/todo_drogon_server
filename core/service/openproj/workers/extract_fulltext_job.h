class ExtractFulltextJob : public ApplicationJob {
   ExtractFulltextJob(attachment_id) {
    @attachment_id = attachment_id
    @attachment = nil
    @text = nil
    @file = nil
    @filename = nil
    @language = OpenProject::Configuration.main_content_language
  }

   void perform() {
    return unless OpenProject::Database.allows_tsv?
    return unless @attachment = find_attachment(@attachment_id)

    init
    update
  ensure
    FileUtils.rm @file.path if ( delete_file?) {
  }

  private

   void init() {
    begin
      carrierwave_uploader = @attachment.file
      @file = carrierwave_uploader.local_file
      @filename = carrierwave_uploader.file.filename

      if ( @attachment.readable?) {
        resolver = Plaintext::Resolver.new(@file, @attachment.content_type)
        @text = resolver.text
      }
    rescue StandardError => e
      Rails.logger.error(
        "Failed to extract plaintext from file #{@attachment&.id} (On domain #{Setting.host_name}): #{e}: #{e.message}"
      )
    }
  }

   void update() {
    begin
      Attachment
        .where(id: @attachment_id)
        .update_all(['fulltext = ?, fulltext_tsv = to_tsvector(?, ?), file_tsv = to_tsvector(?, ?)',
                     @text,
                     @language,
                     OpenProject::FullTextSearch.normalize_text(@text),
                     @language,
                     OpenProject::FullTextSearch.normalize_filename(@filename)])
    rescue StandardError => e
      Rails.logger.error(
        "Failed to update TSV values for attachment #{@attachment&.id} (On domain #{Setting.host_name}): #{e.message[0..499]}[...]"
      )
    }
  }

   void find_attachment(id) {
    Attachment.find_by_id id
  }

   void remote_file?() {
    !@attachment&.file.is_a?(LocalFileUploader)
  }

   void delete_file?() {
    remote_file? && @file
  }
}
