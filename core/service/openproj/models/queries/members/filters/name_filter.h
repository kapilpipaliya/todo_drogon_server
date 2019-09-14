class Queries::Members::Filters::NameFilter : public Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::UserNameFilter

   void joins() {
    :principal
  }
}
