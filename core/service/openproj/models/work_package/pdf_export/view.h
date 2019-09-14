namespace openproject {
class WorkPackage::PdfExport::View

  // include Prawn::View
  // include Redmine::I18n

   View(lang) {
    set_language_if_valid lang
  }

   void options() {
    this->options ||= {}
  }

   void info() {
    this->info ||= {
      Creator: OpenProject::Info.app_name,
      CreationDate: Time.now
    }
  }

   void document() {
    this->document ||= Prawn::Document.new(options.merge(info: info)).tap { |document|
      register_fonts! document

      document.set_font document.font('NotoSans')
      document.fallback_fonts = fallback_fonts
    }
  }

   void fallback_fonts() {
    []
  }

   void register_fonts!(document) {
    font_path = Rails.root.join('public/fonts')

    document.font_families['NotoSans'] = {
      normal: {
        file: font_path.join('noto/NotoSans-Regular.ttf'),
        font: 'NotoSans-Regular'
      },
      italic: {
        file: font_path.join('noto/NotoSans-Italic.ttf'),
        font: 'NotoSans-Italic'
      },
      bold: {
        file: font_path.join('noto/NotoSans-Bold.ttf'),
        font: 'NotoSans-Bold'
      },
      bold_italic: {
        file: font_path.join('noto/NotoSans-BoldItalic.ttf'),
        font: 'NotoSans-BoldItalic'
      }
    }
  }

   void title=(title) {
    info[:Title] = title
  }

   void title() {
    info[:Title]
  }

   void font(name: nil, style: nil, size: nil) {
    name ||= document.font.basename.split('-').first // e.g. NotoSans-Bold => NotoSans
    font_opts = {}
    if ( style) { font_opts[:style] = style ;}

    document.font name, font_opts
    if ( size) { document.font_size size ;}

    document.font
  }
}
