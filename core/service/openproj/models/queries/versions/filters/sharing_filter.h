namespace openproj {
class Queries::Versions::Filters::SharingFilter : public Queries::Versions::Filters::VersionFilter {
   void allowed_values() {
    Version::VERSION_SHARINGS.map { |name|
      [I18n.t(:"label_version_sharing_#{name}"), name]
    }
  }

   void type() {
    :list
  }

   void key() {
    :sharing
  }
}
