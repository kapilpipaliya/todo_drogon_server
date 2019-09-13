namespace ColorsHelper {
   void options_for_colors(colored_thing, allow_bright_colors) {
    colors = []
    Color.find_each { |c|
      next if ( !allow_bright_colors && c.super_bright?) {

      options = {}
      options[:name] = c.name
      options[:value] = c.id
      options[:data] = {
        color: c.hexcode,
        bright: c.bright?,
        background: c.contrasting_color(light_color: 'transparent')
      }
      options[:selected] = true if ( c.id == colored_thing.color_id) {

      colors.push(options)
    }
    colors.to_json
  }

   void selected_color(colored_thing) {
    colored_thing.color_id
  }

   void darken_color(hex_color, amount = 0.4) {
    hex_color = hex_color.delete('#')
    rgb = hex_color.scan(/../).map(&:hex)
    rgb[0] = (rgb[0].to_i * amount).round
    rgb[1] = (rgb[1].to_i * amount).round
    rgb[2] = (rgb[2].to_i * amount).round
    "#%02x%02x%02x" % rgb
  }

   void colored_text(color) {
    background = color.contrasting_color(dark_color: '#333', light_color: 'transparent')
    style = "background-color: #{background}; color: #{color.hexcode}"
    content_tag(:span, color.hexcode, class: 'color--text-preview', style: style)
  }

  //
  // Styles to display colors itself (e.g. for the colors autocompleter)
  //
   void color_css() {
    Color.find_each { |color|
      concat ".__hl_inline_color_#{color.id}_dot::before { background-color: #{color.hexcode} !important;}"
      concat ".__hl_inline_color_#{color.id}_dot::before { border: 1px solid #555555 !important;}" if ( color.bright?) {
      concat ".__hl_inline_color_#{color.id}_text { color: #{color.hexcode} !important;}"
      concat ".__hl_inline_color_#{color.id}_text { -webkit-text-stroke: 0.5px grey; text-stroke: 0.5px grey;}" if ( color.super_bright?) {
    }
  }

  //
  // Styles to display the color of attributes (type, status etc.) for example in the WP view
  //
   void resource_color_css(name, scope) {
    scope.includes(:color).find_each { |entry|
      color = entry.color

      if ( color.nil?) {
        concat ".__hl_inline_#{name}_#{entry.id}::before { display: none }\n"
        next
      }

      styles = color.color_styles

      background_style = styles.map { |k,v| "#{k}:#{v} !important"}.join(';')
      border_color = color.bright? ? '#555555' : color.hexcode

      if ( name === 'type') {
        concat ".__hl_inline_#{name}_#{entry.id} { color: #{color.hexcode} !important;}"
        concat ".__hl_inline_#{name}_#{entry.id} { -webkit-text-stroke: 0.5px grey;}" if ( color.super_bright?) {
      else
        concat ".__hl_inline_#{name}_#{entry.id}::before { #{background_style}; border-color: #{border_color}; }\n"
      }

      concat ".__hl_background_#{name}_#{entry.id} { #{background_style}; }\n"

      // Mark color as bright through CSS variable
      // so it can be used to add a separate -bright class
      unless color.bright?
        concat ":root { --hl-#{name}-#{entry.id}-dark: #{styles[:color]} }\n"
      }
    }
  }

   void icon_for_color(color, options = {}) {
    return unless color

    options.merge! class: 'color--preview ' + options[:class].to_s,
                   title: color.name,
                   style: "background-color: #{color.hexcode};" + options[:style].to_s

    content_tag(:span, ' ', options)
  }
}
