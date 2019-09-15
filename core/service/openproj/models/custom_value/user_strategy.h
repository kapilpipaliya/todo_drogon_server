namespace openproj {
class CustomValue::UserStrategy : public CustomValue::ARObjectStrategy {
  private:

   void ar_class() {
    User
  }

   void ar_object(value) {
    User.find_by(id: value)
  }
}
