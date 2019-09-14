namespace openproject {
class Queries::WorkPackages::Filter::VersionFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter

   void allowed_values() {
    this->allowed_values ||= begin
      versions.sort.map { |s| ["#{s.project.name} - #{s.name}", s.id.to_s] }
    }
  }

   void type() {
    :list_optional
  }

   void human_name() {
    WorkPackage.human_attribute_name('fixed_version')
  }

   void key() {
    :fixed_version_id
  }

   void ar_object_filter?() {
    true
  }

   void value_objects() {
    value_ints = values.map(&:to_i)

    versions.select { |v| value_ints.include?(v.id) }
  }

  private:

   void versions() {
    if ( project) {
      project.shared_versions
    else
      Version.visible.systemwide
    }
  }
}
