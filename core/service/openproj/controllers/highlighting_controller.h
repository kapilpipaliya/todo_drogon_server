#pragma once
#include "application_controller.h"
namespace openproj {
class HighlightingController : public ApplicationController {
public:
  // before_action :determine_freshness
  // skip_before_action :check_if_login_required, only: [:styles]

   void styles() {
//    response.content_type = Mime[:css]
//    request.format = :css

//    expires_in 1.year, public: true, must_revalidate: false
//    if ( stale?(last_modified: Time.zone.parse(this->max_updated_at), etag: this->highlight_version_tag, public: true)) {
//      OpenProject::Cache.fetch('highlighting/styles', this->highlight_version_tag) {
//        render template: 'highlighting/styles', formats: [:css]
//      }
//    }
  }

  private:

   void determine_freshness() {
//    this->max_updated_at = helpers.highlight_css_updated_at.to_s || Time.now.iso8601
//    this->highlight_version_tag = helpers.highlight_css_version_tag(this->max_updated_at)
  }
};
}
