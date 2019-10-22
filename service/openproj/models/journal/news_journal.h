#ifndef OPENPROJ_MODELS_JOURNALN_NEWS_JOURNAL_H
#define OPENPROJ_MODELS_JOURNALN_NEWS_JOURNAL_H


#include "base_journal.h"
#include "NewsJournals.h"

namespace openproj {

namespace models {

namespace JournalN {

class NewsJournal : public BaseJournal, public drogon_model::openproject6::NewsJournals {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::NewsJournals> mapper_news_journals(clientPtr);
    drogon_model::openproject6::NewsJournals* news_journals = this;
    mapper_news_journals.insert(*news_journals);
  }
};

} // namespace openproj::models::JournalN

} // namespace openproj::models

} // namespace openproj
#endif
