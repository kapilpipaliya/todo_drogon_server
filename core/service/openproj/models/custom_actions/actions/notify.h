class CustomActions::Actions::Notify : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

   void apply(work_package) {
    comment = principals.where(id: values).map { |p|
      prefix = if ( p.is_a?(User)) {
                 'user'
               else
                 'group'
               }

      "#{prefix}##{p.id}"
    }.join(', ')

    work_package.journal_notes = comment
  }

   void associated() {
    principals
      .map { |u| [u.id, u.name] }
  }

   void key() {
    :notify
  }

   void multi_value?() {
    true
  }

  private:

   void principals() {
    Principal
      .active_or_registered
      .select(:id, :firstname, :lastname, :type)
      .order_by_name
  }
}
