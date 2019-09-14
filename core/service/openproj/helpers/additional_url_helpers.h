namespace AdditionalUrlHelpers {
  // include AuthenticationStagePathHelper

  module_function

   void fixed_home_url() {
    home_url(script_name: OpenProject::Configuration.rails_relative_url_root)
  }

   void add_params_to_uri(uri, args = {}) {
    uri =  URI.parse uri
    query = URI.decode_www_form String(uri.query)

    args.each { |k, v|
      query << [k, v]
    }

    uri.query = URI.encode_www_form query
    uri.to_s
  }
}
