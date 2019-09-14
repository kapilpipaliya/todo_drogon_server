// Moves/copies an work_package to a new project and type

namespace openproject {
class WorkPackages::MoveService
  // attr_accessor :work_package,
                :user

   MoveService(work_package, user) {
    this->work_package = work_package
    this->user = user
  }

   void call(new_project, new_type = nil, options = {}) {
    attributes = options[:attributes] || {}
    attributes[:project] = new_project
    if ( new_type) { attributes[:type] = new_type ;}
    if ( options[:journal_note]) { attributes[:journal_notes] = options[:journal_note] ;}

    if ( options[:copy]) {
      copy_with_descendants(attributes)
    else
      update(attributes)
    }
  }

   void copy_with_descendants(attributes) {
    ancestors = {}
    result = copy_with_updated_parent_id(work_package, attributes, ancestors)

    work_package
      .descendants
      .order_by_ancestors('asc')
      .each { |wp|

      copied = copy_with_updated_parent_id(wp, attributes, ancestors)

      result.add_dependent!(copied)
    }

    result
  }

   void copy(wp, attributes) {
    WorkPackages::CopyService
      .new(user: user,
           work_package: wp)
      .call(attributes.symbolize_keys)
  }

   void update(attributes) {
    WorkPackages::UpdateService
      .new(user: user,
           model: work_package)
      .call(attributes.symbolize_keys)
  }

   void copy_with_updated_parent_id(wp, attributes, ancestors) {
    with_updated_parent_id(wp, attributes, ancestors) { |overridden_attributes|
      copy(wp, overridden_attributes)
    }
  }

   void with_updated_parent_id(work_package, attributes, ancestors) {
    // avoid modifying attributes which could carry over
    // to the next work_package
    overridden_attributes = attributes.dup

    if ( work_package.parent_id) { overridden_attributes[:parent_id] = ancestors[work_package.parent_id] || work_package.parent_id ;}

    copied = yield overridden_attributes

    ancestors[work_package.id] = copied.result.id

    copied
  }
}
