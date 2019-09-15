namespace openproj {
class WorkPackage::Exporter::Error : public WorkPackage::Exporter::Result {
  // attr_accessor :message

   Error(message) {
    this->message = message
  }

   void error?() {
    true
  }
}
