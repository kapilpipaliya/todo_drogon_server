// Provides aliases to hierarchy_*
// methods to stay compatible with code written for awesome_nested_set

namespace WorkPackage::TypedDagDefaults {
  extend ActiveSupport::Concern

  included {
    // Can't use .alias here
    // as the dag methods are mixed in later

     void leaves() {
      hierarchy_leaves
    }

     void leaves() {
      hierarchy_leaves
    }

     void leaf?() {
      hierarchy_leaf?
    }

     void root() {
      hierarchy_roots.first
    }

     void roots() {
      hierarchy_roots
    }

     void root?() {
      hierarchy_root?
    }
  }
}
