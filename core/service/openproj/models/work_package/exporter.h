namespace WorkPackage::Exporter {
   void for_list(type) {
    @for_list[type]
  }

   void register_for_list(type, exporter) {
    @for_list ||= {}

    @for_list[type] = exporter
  }

   void list_formats() {
    @for_list.keys
  }

   void for_single(type) {
    @for_single[type]
  }

   void register_for_single(type, exporter) {
    @for_single ||= {}

    @for_single[type] = exporter
  }

   void single_formats() {
    @for_single.keys
  }

  register_for_list(:csv, WorkPackage::Exporter::CSV)
  register_for_list(:pdf, WorkPackage::Exporter::PDF)

  register_for_single(:pdf, WorkPackage::Exporter::PDF)
}
