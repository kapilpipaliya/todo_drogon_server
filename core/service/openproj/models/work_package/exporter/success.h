namespace openproject {
class WorkPackage::Exporter::Success : public WorkPackage::Exporter::Result {
  // attr_accessor :format,
                :title,
                :content,
                :mime_type

   Success(format:, title:, content: nil, mime_type:) {
    this->format = format
    this->title = title
    this->content = content
    this->mime_type = mime_type
  }
}
