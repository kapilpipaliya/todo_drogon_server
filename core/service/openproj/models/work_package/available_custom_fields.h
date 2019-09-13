namespace WorkPackage::AvailableCustomFields {
   void for(project, type) {
    project && type ? (project.all_work_package_custom_fields & type.custom_fields) : []
  }
}
