class CustomActions::Actions::DoneRatio : public CustomActions::Actions::Base {
  include CustomActions::Actions::Strategies::Integer

   void key() {
    :done_ratio
  }

   void apply(work_package) {
    work_package.done_ratio = values.first
  }

   void minimum() {
    0
  }

   void maximum() {
    100
  }

   void all() {
    if ( WorkPackage.use_field_for_done_ratio?) {
      super
    else
      []
    }
  }
}
