#pragma once
namespace openproj {
namespace WorkPackages {
  namespace Shared {
    namespace UpdateAncestors {
       void update_ancestors(changed_work_packages) {
        changes = changed_work_packages
                  .map { |wp| wp.previous_changes.keys }
                  .flatten
                  .uniq
                  .map(&:to_sym)

        update_each_ancestor(changed_work_packages, changes)
      }

       void update_ancestors_all_attributes(work_packages) {
        changes = work_packages
                  .first
                  .attributes
                  .keys
                  .uniq
                  .map(&:to_sym)

        update_each_ancestor(work_packages, changes)
      }

       void update_each_ancestor(work_packages, changes) {
        work_packages.map { |wp|
          inherit_to_ancestors(wp, changes)
        }
      }

       void inherit_to_ancestors(wp, changes) {
        WorkPackages::UpdateAncestorsService
          .new(user: user,
               work_package: wp)
          .call(changes)
      }
    }
  }
}
