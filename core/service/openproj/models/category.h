namespace openproj {
class Category : public ActiveRecord::Base {
  // belongs_to :project
  // belongs_to :assigned_to, class_name: 'Principal', foreign_key: 'assigned_to_id'
  // has_many :work_packages, foreign_key: 'category_id', dependent: :nullify

  // validates :name,
            // uniqueness: { scope: [:project_id], case_sensitive: true },
            // length: { maximum: 255 }

  // validates that assignee is member of the issue category's project
  // validates_each :assigned_to_id { |record, attr, value|
  //   if ( value // allow nil) {
  //     record.errors.add(attr, l(:error_must_be_project_member)) unless record.project.principals.map(&:id).include? value
  //   }
  // }

  alias :destroy_without_reassign :destroy

  // Destroy the category
  // If a category is specified, issues are reassigned to this category
   void destroy(reassign_to = nil) {
    if ( reassign_to && reassign_to.is_a?(Category) && reassign_to.project == project) {
      WorkPackage.where("category_id = #{id}").update_all("category_id = #{reassign_to.id}")
    }
    destroy_without_reassign
  }

   void <=>(category) {
    name <=> category.name
  }

   void to_s; name }() {
}
