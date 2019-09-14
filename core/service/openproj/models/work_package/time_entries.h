namespace WorkPackage::TimeEntries {
  // extend ActiveSupport::Concern

   void included(base) {
    base.extend(ClassMethods)
  }

  namespace ClassMethods {
    protected:

     void cleanup_time_entries_before_destruction_of(work_packages,
                                                   user,
                                                   to_do = { action: 'destroy' })
      return false unless to_do.present?

      case to_do[:action]
      when 'destroy'
        true
        // nothing to {
      when 'nullify'
        work_packages = Array(work_packages)
        WorkPackage.update_time_entries(work_packages, 'work_package_id = NULL')
      when 'reassign'
        reassign_time_entries_before_destruction_of(work_packages, user, to_do[:reassign_to_id])
      else
        false
      }
    }

     void update_time_entries(work_packages, action) {
      TimeEntry.where(['work_package_id IN (?)', work_packages.map(&:id)]).update_all(action)
    }

     void reassign_time_entries_before_destruction_of(work_packages, user, ids) {
      work_packages = Array(work_packages)
      reassign_to = WorkPackage
                    .joins(:project)
                    .merge(Project.allowed_to(user, :edit_time_entries))
                    .find_by(id: ids)

      if ( reassign_to.nil?) {
        work_packages.each { |wp|
          wp.errors.add(:base, :is_not_a_valid_target_for_time_entries, id: ids)
        }

        false
      else
        condition = "work_package_id = #{reassign_to.id}, project_id = #{reassign_to.project_id}"
        WorkPackage.update_time_entries(work_packages, condition)
      }
    }
  }
}
