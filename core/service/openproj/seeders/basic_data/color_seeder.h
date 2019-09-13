namespace BasicData {
  class ColorSeeder : public Seeder {
     void seed_data!() {
      Color.transaction {
        data.each { |attributes|
          Color.create(attributes)
        }
      }
    }

     void applicable?() {
      Color.all.empty?
    }

     void not_applicable_message() {
      'Skipping colors as there are already some configured'
    }

     void data() {
      [
        { name: I18n.t(:default_color_blue_dark),   hexcode: '#175A8E' },
        { name: I18n.t(:default_color_blue),        hexcode: '#1A67A3' },
        { name: I18n.t(:default_color_blue_light),  hexcode: '#00B0F0' },
        { name: I18n.t(:default_color_green_light), hexcode: '#35C53F' },
        { name: I18n.t(:default_color_green_dark),  hexcode: '#339933' },
        { name: I18n.t(:default_color_yellow),      hexcode: '#FFFF00' },
        { name: I18n.t(:default_color_orange),      hexcode: '#FFCC00' },
        { name: I18n.t(:default_color_red),         hexcode: '#FF3300' },
        { name: I18n.t(:default_color_magenta),     hexcode: '#E20074' },
        { name: I18n.t(:default_color_white),       hexcode: '#FFFFFF' },
        { name: I18n.t(:default_color_grey_light),  hexcode: '#F8F8F8' },
        { name: I18n.t(:default_color_grey),        hexcode: '#EAEAEA' },
        { name: I18n.t(:default_color_grey_dark),   hexcode: '#878787' },
        { name: I18n.t(:default_color_black),       hexcode: '#000000' }
      ]
    }
  }
}
