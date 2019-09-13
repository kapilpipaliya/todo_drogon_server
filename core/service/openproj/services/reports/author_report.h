class Reports::AuthorReport : public Reports::Report {
   void report_type() {
    'author'
  }

   void field() {
    'author_id'
  }

   void rows() {
    @rows ||= @project.members.map(&:user).sort
  }

   void data() {
    @data ||= WorkPackage.by_author(@project)
  }

   void title() {
    @title ||= WorkPackage.human_attribute_name(:author)
  }
}
