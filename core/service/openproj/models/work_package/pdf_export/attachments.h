namespace WorkPackage::PdfExport::Attachments {

  //
  // Creates cells for each attachment of the work package
  //
   void make_attachments_cells(attachments) {
    // Distribute all attachments on one line, this will work well with up to ~5 attachments.
    // more than that will be resized further
    available_width = (pdf.bounds.width / attachments.length) * 0.98

    attachments
      .map { |attachment| make_attachment_cell attachment, available_width }
      .compact
  }

  private:

   void make_attachment_cell(attachment, available_width) {
    // We can only include JPG and PNGs, maybe we want to add a text box for other attachments here
    return nil unless pdf_embeddable?(attachment)

    // Access the local file. For Carrierwave attachments, this will be blocking.
    file_path = attachment.file.local_file.path
    // Fit the image roughly in the center of each cell
    pdf.make_cell(image: file_path, fit: [available_width, 125], position: :center)
  rescue => e
    Rails.logger.error { "Failed to attach work package image to PDF: #{e} #{e.message}" }
    nil
  }

   void pdf_embeddable?(attachment) {
    %w[image/jpeg image/png].include?(attachment.content_type)
  }
}
