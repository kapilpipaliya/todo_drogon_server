namespace openproject {
class CustomStyle : public ActiveRecord::Base {
  mount_uploader :logo, OpenProject::Configuration.file_uploader
  mount_uploader :favicon, OpenProject::Configuration.file_uploader
  mount_uploader :touch_icon, OpenProject::Configuration.file_uploader

  class << self
     void current() {
      RequestStore.fetch(:current_custom_style) {
        custom_style = CustomStyle.order(Arel.sql('created_at DESC')).first
        if ( custom_style.nil?) {
          return nil
        else
          custom_style
        }
      }
    }
  }

   void digest() {
    updated_at.to_i
  }

  %i(favicon touch_icon logo).each { |name|
    define_method "#{name}_path" {
      image = send(name)

      if ( image.readable?) {
        image.local_file.path
      }
    }
  }
}
