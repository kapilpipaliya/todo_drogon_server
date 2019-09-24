#ifndef OPENPROJ_MODELS_WIKI_REDIRECT_H
#define OPENPROJ_MODELS_WIKI_REDIRECT_H


#include "activerecord.h"
#include "WikiRedirects.h"
#include <drogon/drogon.h>
namespace openproj {

namespace models {

class WikiRedirect : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::WikiRedirects {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::WikiRedirects> mapper_wiki_redirects(clientPtr);
    drogon_model::openproject6::WikiRedirects* wiki_redirects = this;
    mapper_wiki_redirects.insert(*wiki_redirects);
  }
  // belongs_to :wiki

  // validates_presence_of :title, :redirects_to
  // validates_length_of :title, :redirects_to, maximum: 255

};

} // namespace openproj::models

} // namespace openproj
#endif
