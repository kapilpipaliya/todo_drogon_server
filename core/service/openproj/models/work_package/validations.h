namespace WorkPackage::Validations {
  extend ActiveSupport::Concern

  included {
    validates_presence_of :subject, :priority, :project, :type, :author, :status

    validates_length_of :subject, maximum: 255
    validates_inclusion_of :done_ratio, in: 0..100
    validates_numericality_of :estimated_hours, allow_nil: true

    validates :due_date, date: { allow_blank: true }
    validates :start_date, date: { allow_blank: true }

    scope :eager_load_for_validation, -> {
      includes({ project: %i(enabled_modules work_package_custom_fields versions) },
               { parent: :type },
               :custom_values,
               { type: :custom_fields },
               :priority,
               :status,
               :author,
               :category,
               :fixed_version)
    }
  }
}
