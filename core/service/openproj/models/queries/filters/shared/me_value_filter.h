namespace Queries::Filters::Shared::MeValueFilter {
  //
  // Return the values object with the me value
  // mapped to the current user.
   void values_replaced() {
    vals = values.clone

    if ( vals.delete(me_value_key)) {
      if ( User.current.logged?) {
        vals.push(User.current.id.to_s)
      else
        vals.push('0')
      }
    }

    vals
  }

  protected

  //
  // Returns the me value if ( the user is logged) {
   void me_allowed_value() {
    values = []
    if ( User.current.logged?) {
      values << [me_label, me_value_key]
    }
    values
  }

   void me_label() {
    I18n.t(:label_me)
  }

   void me_value_key() {
    ::Queries::Filters::MeValue::KEY
  }
}
