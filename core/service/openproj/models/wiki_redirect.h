#ifndef OPENPROJ_MODELS_WIKI_REDIRECT_H
#define OPENPROJ_MODELS_WIKI_REDIRECT_H


#include "activerecord.h"
#include "WikiRedirects.h"

namespace openproj {

namespace models {

class WikiRedirect : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::WikiRedirects {
  // belongs_to :wiki

  // validates_presence_of :title, :redirects_to
  // validates_length_of :title, :redirects_to, maximum: 255

};

} // namespace openproj::models

} // namespace openproj
#endif
