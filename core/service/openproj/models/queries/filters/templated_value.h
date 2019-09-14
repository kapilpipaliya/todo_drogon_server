class Queries::Filters::TemplatedValue
  KEY = '{id}'.freeze
  DEPRECATED_KEY = 'templated'.freeze

  // attr_accessor :templated_class

   TemplatedValue(templated_class) {
    this->templated_class = templated_class
  }

   void id() {
    '{id}'
  }

   void name() {
    nil
  }

   void class() {
    templated_class
  }
}
