#pragma once
namespace openproj {
namespace models {
namespace Queries::Filters::Shared::UserNameFilter {
//   void included(base) {
//    base.include(InstanceMethods)
//    base.extend(ClassMethods)
//  }

  namespace InstanceMethods {
     void type() {
//      :string
    }

     void key() {
//      :name
    }

     void where() {
//      case operator
//      when '='
//        ["#{sql_concat_name} IN (?)", sql_value]
//      when '!'
//        ["#{sql_concat_name} NOT IN (?)", sql_value]
//      when '~'
//        ["#{sql_concat_name} LIKE ?", "%#{sql_value}%"]
//      when '!~'
//        ["#{sql_concat_name} NOT LIKE ?", "%#{sql_value}%"]
//      }
    }

//    private:

//     void sql_value() {
//      case operator
//      when '=', '!'
//        values.map { |val| this->class.connection.quote_string(val.downcase) }.join(',')
//      when '~', '!~'
//        values.first.downcase
//      }
//    }

//     void sql_concat_name() {
//      case Setting.user_format
//      when :firstname_lastname, :lastname_coma_firstname
//        "LOWER(CONCAT(users.firstname, CONCAT(' ', users.lastname)))"
//      when :firstname
//        'LOWER(users.firstname)'
//      when :lastname_firstname
//        "LOWER(CONCAT(users.lastname, CONCAT(' ', users.firstname)))"
//      when :username
//        "LOWER(users.login)"
//      }
//    }
  }

  namespace ClassMethods {
     void key() {
//      :name
    }
  }
}
}
}