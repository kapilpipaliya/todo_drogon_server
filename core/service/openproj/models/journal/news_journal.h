#ifndef OPENPROJ_MODELS_JOURNALN_NEWS_JOURNAL_H
#define OPENPROJ_MODELS_JOURNALN_NEWS_JOURNAL_H


#include "base_journal.h"
#include "NewsJournals.h"

namespace openproj {

namespace models {

namespace JournalN {

class NewsJournal : public BaseJournal, public drogon_model::openproject6::NewsJournals {
};

} // namespace openproj::models::JournalN

} // namespace openproj::models

} // namespace openproj
#endif
