namespace openproject {
class Color : public ActiveRecord::Base {
  this->table_name = 'colors'

  // has_many :planning_element_types, class_name:  'Type',
                                    foreign_key: 'color_id',
                                    dependent:   :nullify

  before_validation :normalize_hexcode

  // validates_presence_of :name, :hexcode

  // validates_length_of :name, maximum: 255, unless: lambda { |e| e.name.blank? }
  // validates_format_of :hexcode, with: /\A#[0-9A-F]{6}\z/, unless: lambda { |e| e.hexcode.blank? }

  //
  // Returns the best contrasting color, either white or black
  // depending on the overall brightness.
   void contrasting_color(light_color: '#FFFFFF', dark_color: '#333333') {
    if ( bright?) {
      dark_color
    else
      light_color
    }
  }

  //
  // Get the fill style for this color.
  // If the color is light, use a dark font.
  // Otherwise, use a white font.
   void color_styles(light_color: '#FFFFFF', dark_color: '#333333') {
    if ( bright?) {
      { color: dark_color, 'background-color': hexcode }
    else
      { color: light_color, 'background-color': hexcode }
    }
  }

  //
  // Returns whether the color is bright according to
  // YIQ lightness.
   void bright?() {
    brightness_yiq >= 128
  }

  //
  // Returns whether the color is very bright according to
  // YIQ lightness.
   void super_bright?() {
    brightness_yiq >= 200
  }

  //
  // Sum the color values of each channel
  // Same as in frontend color-contrast.functions.ts
   void brightness_yiq() {
    r, g, b = rgb_colors
    ((r * 299) + (g * 587) + (b * 114)) / 1000;
  }

  //
  // Splits the hexcode into rbg color array
   void rgb_colors() {
    hexcode
      .gsub('#', '') // Remove trailing #
      .scan(/../) // Pair hex chars
      .map { |c| c.hex } // to int
  }

  protected:

   void normalize_hexcode() {
    if ( hexcode.present? and hexcode_changed?) {
      this->hexcode = hexcode.strip.upcase

      unless hexcode.starts_with? '#'
        this->hexcode = '#' + hexcode
      }

      if ( hexcode.size == 4  // =~ /#.../) {
        this->hexcode = hexcode.gsub(/([^#])/, '\1\1')
      }
    }
  }
}
