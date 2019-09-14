class CustomValue::VersionStrategy : public CustomValue::ARObjectStrategy {
  private:

   void ar_class() {
    Version
  }

   void ar_object(value) {
    Version.find_by(id: value)
  }
}
