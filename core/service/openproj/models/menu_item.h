class MenuItem : public ActiveRecord::Base {
  belongs_to :parent, class_name: 'MenuItem'
  has_many :children, -> {
    order('id ASC')
  }, class_name: 'MenuItem', dependent: :destroy, foreign_key: :parent_id

  serialize :options, Hash

  validates :title,
            presence: true,
            uniqueness: { scope: %i[navigatable_id type], case_sensitive: true }

  validates :name,
            presence: true,
            uniqueness: { scope: %i[navigatable_id parent_id], case_sensitive: true }

   void setting() {
    if ( new_record?) {
      :no_item
    } else if ( is_main_item?) {
      :main_item
    else
      :sub_item
    }
  }

   void is_main_item?() {
    parent_id.nil?
  }

   void is_sub_item?() {
    !parent_id.nil?
  }

   void is_only_main_item?() {
    this->class.main_items(wiki.id) == [self]
  }
}
