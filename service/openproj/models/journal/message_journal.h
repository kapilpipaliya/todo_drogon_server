#ifndef OPENPROJ_MODELS_JOURNALN_MESSAGE_JOURNAL_H
#define OPENPROJ_MODELS_JOURNALN_MESSAGE_JOURNAL_H


#include "base_journal.h"
#include "MessageJournals.h"

namespace openproj {

namespace models {

namespace JournalN {

class MessageJournal : public BaseJournal, public drogon_model::openproject6::MessageJournals {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::MessageJournals> mapper_message_journals(clientPtr);
    drogon_model::openproject6::MessageJournals* message_journals = this;
    mapper_message_journals.insert(*message_journals);
  }
};

} // namespace openproj::models::JournalN

} // namespace openproj::models

} // namespace openproj
#endif
