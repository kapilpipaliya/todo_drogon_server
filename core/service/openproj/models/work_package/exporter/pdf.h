namespace openproject {
class WorkPackage::Exporter::PDF : public WorkPackage::Exporter::Base {
  // Returns a PDF string of a list of work_packages
   void list() {
    yield ::WorkPackage::PdfExport::WorkPackageListToPdf
      .new(query,
           options)
      .render!
  }

  // Returns a PDF string of a single work_package
   void single() {
    yield ::WorkPackage::PdfExport::WorkPackageToPdf
      .new(work_package)
      .render!
  }
}
