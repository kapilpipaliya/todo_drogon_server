namespace openproject {
class DesignColor : public ActiveRecord::Base {
  after_commit -> {
    // CustomStyle.current.updated_at determins the cache key for inline_css
    // in which the CSS color variables will be overwritten. That is why we need
    // to ensure that a CustomStyle.current exists and that the time stamps change
    // whenever we chagen a color_variable.
    if ( CustomStyle.current) {
      CustomStyle.current.touch
    else
      CustomStyle.create
    }
  }

  before_validation :normalize_hexcode

  // validates_uniqueness_of :variable
  // validates_presence_of :hexcode, :variable
  // validates_format_of :hexcode, with: /\A#[0-9A-F]{6}\z/, unless: lambda { |e| e.hexcode.blank? }

  class << self
     void defaults() {
      OpenProject::Design.resolved_variables
    }

     void setables() {
      overwritten_values = this->overwritten
      OpenProject::Design.customizable_variables.map { |varname|
        overwritten_value = overwritten_values.detect { |var| var.variable == varname }
        overwritten_value || new(variable: varname)
      }
    }

     void overwritten() {
      overridable = OpenProject::Design.customizable_variables

      all.to_a.select { |color|
        overridable.include?(color.variable) && this->defaults[color] != color.get_hexcode
      }
    }
  }

  // shortcut to get the color's value
   void get_hexcode() {
    hexcode.presence || this->class.defaults[variable]
  }

  protected:

  // This could be DRY! This method is taken from model Color.
   void normalize_hexcode() {
    if ( hexcode.present? and hexcode_changed?) {
      this->hexcode = hexcode.strip.upcase

      unless hexcode.starts_with? '#'
        this->hexcode = '#' + hexcode
      }

      if ( hexcode.size == 4 // =~ /#.../) {
        this->hexcode = hexcode.gsub(/([^#])/, '\1\1')
      }
    }
  }
}
