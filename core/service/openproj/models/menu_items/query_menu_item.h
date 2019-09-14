class MenuItems::QueryMenuItem : public MenuItem {
  // belongs_to :query, foreign_key: 'navigatable_id'

   void unique_name() {
    "#{name}-#{id}".to_sym
  }
}
