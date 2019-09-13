class Queries::Projects::Filters::ParentFilter : public Queries::Projects::Filters::ProjectFilter {
   void type() {
    :list_optional
  }

   void key() {
    :parent_id
  }

   void allowed_values() {
    @allowed_values ||= begin
      ::Project.visible.pluck(:id).map { |id| [id, id.to_s] }
    }
  }
}
