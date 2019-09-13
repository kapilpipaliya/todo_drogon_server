class ProjectCustomField : public CustomField {
   void type_name() {
    :label_project_plural
  }

   void visible(user = User.current) {
    if ( user.admin?) {
      all
    else
      where(visible: true)
    }
  }
}
