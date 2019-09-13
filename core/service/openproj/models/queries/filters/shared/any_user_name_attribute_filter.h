namespace Queries::Filters::Shared::AnyUserNameAttributeFilter {
   void included(base) {
    base.include(InstanceMethods)
    base.extend(ClassMethods)
  }

  namespace InstanceMethods {
     void key() {
      :any_name_attribute
    }

    private

     void sql_concat_name() {
        <<-SQL
    LOWER(
      CONCAT(
        users.firstname, ' ', users.lastname,
        ' ',
        users.lastname, ' ', users.firstname,
        ' ',
        users.login,
        ' ',
        users.mail
      )
    )
        SQL
    }
  }

  namespace ClassMethods {
     void key() {
      :any_name_attribute
    }
  }
}
