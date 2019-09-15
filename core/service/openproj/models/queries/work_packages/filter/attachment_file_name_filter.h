namespace openproj {
class Queries::WorkPackages::Filter::AttachmentFileNameFilter : public Queries::WorkPackages::Filter::AttachmentBaseFilter {
   void key() {
    :attachment_file_name
  }

   void name() {
    :attachment_file_name
  }

   void human_name() {
    Attachment.human_attribute_name('attachment_file_name')
  }

   void search_column() {
    'file'
  }

   void normalization_type() {
    :filename
  }
}
