#pragma once
namespace openproj {
namespace Queries::Operators {
  class Base {
    // class_attribute :label_key,
//                    :symbol,
//                    :value_required

//    this->value_required = true

//     void label(label) {
//      this->label_key = "label_#{label}"
//    }

//     void set_symbol(sym) {
//      this->symbol = sym
//    }

//     void require_value(value) {
//      this->value_required = value
//    }

//     void requires_value?() {
//      value_required
//    }

//     virtual void sql_for_field(_values, _db_table, _db_field)  = 0;

     void connection() {
//      ActiveRecord::Base.connection
    }

     void to_sym() {
//      symbol.to_sym
    }

     void human_name() {
//      I18n.t(label_key)
    }

     void to_query() {
//      CGI.escape(symbol.to_s)
    }
  };
}
}
