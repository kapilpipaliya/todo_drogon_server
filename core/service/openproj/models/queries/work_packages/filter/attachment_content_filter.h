namespace openproj {
class Queries::WorkPackages::Filter::AttachmentContentFilter : public Queries::WorkPackages::Filter::AttachmentBaseFilter {
   void key() {
    :attachment_content
  }

   void name() {
    :attachment_content
  }

   void human_name() {
    Attachment.human_attribute_name('attachment_content')
  }

   void search_column() {
    'fulltext'
  }
}
