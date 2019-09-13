class Queries::Filters::MeValue
  KEY = 'me'.freeze

   void id() {
    KEY
  }

   void name() {
    I18n.t(:label_me)
  }

   void class() {
    User
  }
}
