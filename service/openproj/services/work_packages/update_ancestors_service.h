#pragma once
namespace openproj {
namespace service {
namespace WorkPackages{
class UpdateAncestorsService {
public:
  // attr_accessor :user,
//                :work_package

//   UpdateAncestorsService(user:, work_package:) {
//    this->user = user
//    this->work_package = work_package
//  }

//   void call(attributes) {
//    modified = update_ancestors(attributes)
//    modified += update_former_ancestors(attributes)

//    set_journal_note(modified)

//    // do not send notification for parent updates
//    success = JournalManager.with_send_notifications(false) {
//      modified.all? { |wp| wp.save(validate: false) }
//    }

//    result = ServiceResult.new(success: success, result: work_package)

//    modified.each { |wp|
//      result.add_dependent!(ServiceResult.new(success: !wp.changed?, result: wp))
//    }

//    result
//  }

  private:

//   void update_ancestors(attributes) {
//    work_package.ancestors.includes(:status).select { |ancestor|
//      inherit_attributes(ancestor, attributes)

//      ancestor.changed?
//    }
//  }

//   void update_former_ancestors(attributes) {
//    return [] unless (%i(parent_id parent) & attributes).any? && previous_parent_id

//    parent = WorkPackage.find(previous_parent_id)

//    ([parent] + parent.ancestors).each { |ancestor|
//      // pass :parent to force update of all inherited attributes
//      inherit_attributes(ancestor, %i(parent))
//    }.select(&:changed?)
//  }

//   void inherit_attributes(ancestor, attributes) {
//    return unless attributes_justify_inheritance?(attributes)

//    leaves = leaves_for_ancestor ancestor

//    inherit_from_leaves ancestor: ancestor, leaves: leaves, attributes: attributes
//  }

//   void leaves_for_ancestor(ancestor) {
//    ancestor
//      .leaves
//      .select(selected_leaf_attributes)
//      .distinct(true) // Be explicit that this is a distinct (wrt ID) query
//      .includes(:status).to_a
//  }

//   void inherit_from_leaves(ancestor:, leaves:, attributes:) {
//    if ( inherit? attributes, :done_ratio) { inherit_done_ratio ancestor, leaves ;}
//    if ( inherit? attributes, :estimated_hours) { derive_estimated_hours ancestor, leaves ;}
//  }

//   void inherit?(attributes, attribute) {
//    [attribute, :parent].any? { |attr| attributes.include? attr }
//  }

//   void set_journal_note(work_packages) {
//    work_packages.each { |wp|
//      wp.journal_notes = I18n.t("work_package.updated_automatically_by_child_changes", child: "##{work_package.id}")
//    }
//  }

//   void inherit_done_ratio(ancestor, leaves) {
//    if ( WorkPackage.done_ratio_disabled?) { return ;}

//    if ( WorkPackage.use_status_for_done_ratio? && ancestor.status && ancestor.status.default_done_ratio) { return ;}

//    // done ratio = weighted average ratio of leaves
//    ratio = aggregate_done_ratio(leaves)

//    if ( ratio) {
//      ancestor.done_ratio = ratio.round
//    }
//  }

  //
  // done ratio = weighted average ratio of leaves
//   void aggregate_done_ratio(leaves) {
//    leaves_count = leaves.size

//    if ( leaves_count > 0) {
//      average = average_estimated_hours(leaves)
//      progress = done_ratio_sum(leaves, average) / (average * leaves_count)

//      progress.round(2)
//    }
//  }

//   void average_estimated_hours(leaves) {
//    // 0 and nil shall be considered the same for estimated hours
//    sum = all_estimated_hours(leaves).sum.to_f
//    count = all_estimated_hours(leaves).count

//    if ( count.zero?) { count = 1 ;}

//    average = sum / count

//    average.zero? ? 1 : average
//  }

//   void done_ratio_sum(leaves, average_estimated_hours) {
//    // do not take into account estimated_hours when it is either nil or set to 0.0
//    summands = leaves.map { |leaf|
//      estimated_hours = if ( leaf.estimated_hours.to_f > 0) {
//                          leaf.estimated_hours
//                        else
//                          average_estimated_hours
//                        }

//      done_ratio = if ( leaf.closed?) {
//                     100
//                   else
//                     leaf.done_ratio || 0
//                   }

//      estimated_hours * done_ratio
//    }

//    summands.sum
//  }

//   void derive_estimated_hours(ancestor, leaves) {
//    ancestor.derived_estimated_hours = not_zero all_estimated_hours(leaves, derived: true).sum.to_f
//  }

//   void not_zero(value) {
//    value unless value.zero?
//  }

//   void all_estimated_hours(work_packages, derived: false) {
//    work_packages
//      .map { |wp| (derived && wp.derived_estimated_hours) || wp.estimated_hours }
//      .reject { |hours| hours.to_f.zero? }
//  }

  //
  // Get the previous parent ID
  // This could either be +parent_id_was+ if ( parent was changed) {
  // (when work_package was saved/destroyed)
  // Or the set parent before saving
//   void previous_parent_id() {
//    if ( work_package.parent_id.nil? && work_package.parent_id_was) {
//      work_package.parent_id_was
//    else
//      previous_change_parent_id
//    }
//  }

//   void previous_change_parent_id() {
//    previous = work_package.previous_changes

//    previous_parent_changes = (previous[:parent_id] || previous[:parent])

//    previous_parent_changes ? previous_parent_changes.first : nil
//  }

//   void attributes_justify_inheritance?(attributes) {
//    (%i(estimated_hours done_ratio parent parent_id status status_id) & attributes).any?
//  }

//   void selected_leaf_attributes() {
//    %i(id done_ratio derived_estimated_hours estimated_hours status_id)
//  }
};
}
}
}
