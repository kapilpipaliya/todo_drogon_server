namespace Versions {
  class SetAttributesService : public ::BaseServices::SetAttributes {
    private:

     void set_default_attributes() {
      return unless model.new_record?

      model.sharing ||= 'none'
      model.status ||= 'open'
    }
  }
}
