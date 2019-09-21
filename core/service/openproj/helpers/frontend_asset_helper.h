namespace openproj {
namespace helper {
namespace FrontendAssetHelper {
//  CLI_DEFAULT_PROXY = "http://localhost:4200".freeze

   bool assets_proxied() {
//    !Rails.env.production? && cli_proxy?
  }

//   void cli_proxy() {
//    ENV.fetch("OPENPROJECT_CLI_PROXY", CLI_DEFAULT_PROXY)
//  }

   bool cli_proxy() {
//    cli_proxy.present?
  }

  //
  // Include angular CLI frontend assets by either referencing a prod build,
  // or referencing the running CLI proxy that hosts the assets in memory.
   void include_frontend_assets() {
//    capture {
//      %w(vendor.js polyfills.js runtime.js main.js).each { |file|
//        concat javascript_include_tag variable_asset_path(file)
//      }

//      if ( FrontendAssetHelper.assets_proxied?) {
//        concat javascript_include_tag variable_asset_path("styles.js")
//      else
//        concat stylesheet_link_tag variable_asset_path("styles.css")
//      }
//    }
  }

//  private:

//   void angular_cli_asset(path) {
//    URI.join(FrontendAssetHelper.cli_proxy, "assets/frontend/#{path}")
//  }

//   void frontend_asset_path(unhashed, options = {}) {
//    file_name = ::OpenProject::Assets.lookup_asset unhashed

//    asset_path "assets/frontend/#{file_name}", options.merge(skip_pipeline: true)
//  }

//   void variable_asset_path(path) {
//    if ( FrontendAssetHelper.assets_proxied?) {
//      angular_cli_asset(path)
//    else
//      frontend_asset_path(path)
//    }
//  }
}
}
}
