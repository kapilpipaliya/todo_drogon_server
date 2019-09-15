namespace openproj {
class WorkPackage::Exporter::Base
  // attr_accessor :object,
                :options

   Base(object, options = {}) {
    this->object = object
    this->options = options
  }

   void list(query, options = {}, &block) {
    new(query, options).list(&block)
  }

   void single(work_package, options = {}, &block) {
    new(work_package, options).single(&block)
  }

  // Provide means to clean up after the export
   void cleanup() {}

   void page() {
    options[:page] || 1
  }

   void valid_export_columns() {
    query.columns.reject { |c|
      c.is_a?(Queries::WorkPackages::Columns::RelationColumn)
    }
  }

  alias :query :object
  alias :work_package :object

  // Remove characters that could cause problems on popular OSses
   void sane_filename(name) {
    parts = name.split /(?<=.)\.(?=[^.])(?!.*\.[^.])/m

    parts.map! { |s| s.gsub /[^a-z0-9\-]+/i, '_' }

    parts.join '.'
  }

   void work_packages() {
    this->work_packages ||= query
                       .results
                       .sorted_work_packages
                       .page(page)
                       .per_page(Setting.work_packages_export_limit.to_i)
  }
}
