#pragma once
// Borrows from http://gist.github.com/bf4/5320847
// without addressable requirement
// Accepts options[:allowed_protocols]
namespace openproj {
namespace validator {
class UrlValidator{// : public ActiveModel::EachValidator {
//   void validate_each(record, attribute, value) {
//    url = parse(value)

//    if ( url.nil?) {
//      record.errors.add(attribute, :invalid_url)
//    } else if ( !allowed_protocols.include?(url.scheme)) {
//      record.errors.add(attribute, :invalid_url_scheme, allowed_schemes: allowed_protocols.join(', '))
//    }
//  }

//   void parse(value) {
//    url = URI.parse(value)
//  rescue => e
//    nil
//  }
   void allowed_protocols() {
//    options.fetch(:allowed_protocols, %w(http https))
  }
};
}
}
