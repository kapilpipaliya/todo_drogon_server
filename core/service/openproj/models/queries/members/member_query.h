class Queries::Members::MemberQuery : public Queries::BaseQuery {
   void model() {
    Member
  }

   void default_scope() {
    Member.visible(User.current)
  }
}
