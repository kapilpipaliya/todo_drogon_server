class Queries::Members::Filters::BlockedFilter : public Queries::Members::Filters::MemberFilter {
  include Queries::Filters::Shared::UserBlockedFilter

   void joins() {
    :principal
  }
}
