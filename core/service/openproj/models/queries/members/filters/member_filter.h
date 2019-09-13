class Queries::Members::Filters::MemberFilter : public Queries::Filters::Base {
  this->model = Member

   void human_name() {
    Member.human_attribute_name(name)
  }
}
