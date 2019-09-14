namespace WorkPackage::Exporter {
   void for_list(type) {
    this->for_list[type]
  }

   void register_for_list(type, exporter) {
    this->for_list ||= {}

    this->for_list[type] = exporter
  }

   void list_formats() {
    this->for_list.keys
  }

   void for_single(type) {
    this->for_single[type]
  }

   void register_for_single(type, exporter) {
    this->for_single ||= {}

    this->for_single[type] = exporter
  }

   void single_formats() {
    this->for_single.keys
  }

  register_for_list(:csv, WorkPackage::Exporter::CSV)
  register_for_list(:pdf, WorkPackage::Exporter::PDF)

  register_for_single(:pdf, WorkPackage::Exporter::PDF)
}
