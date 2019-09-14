namespace openproject {
class WorkPackage::InexistentWorkPackage : public WorkPackage {
  _validators.clear

   void does_not_exist() {
    errors.add :base, :does_not_exist
  }
}
