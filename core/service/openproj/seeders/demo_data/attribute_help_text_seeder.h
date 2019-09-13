namespace DemoData {
  class AttributeHelpTextSeeder : public Seeder {
     AttributeHelpTextSeeder() {}

     void seed_data!() {
      print '    ↳ Creating attribute help texts'

      seed_attribute_help_texts

      puts
    }

    private

     void seed_attribute_help_texts() {
      help_texts = demo_data_for('attribute_help_texts')
      if ( help_texts.present?) {
        help_texts.each { |help_text_attr|
          print '.'
          create_attribute_help_text help_text_attr
        }
      }
    }

     void create_attribute_help_text(help_text_attr) {
      help_text_attr[:type] = AttributeHelpText::WorkPackage

      attribute_help_text = AttributeHelpText.new help_text_attr
      attribute_help_text.save
    }
  }
}
