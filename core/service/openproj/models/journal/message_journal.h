#ifndef OPENPROJ_MODELS_JOURNALN_MESSAGE_JOURNAL_H
#define OPENPROJ_MODELS_JOURNALN_MESSAGE_JOURNAL_H


#include "base_journal.h"
#include "MessageJournals.h"

namespace openproj {

namespace models {

namespace JournalN {

class MessageJournal : public BaseJournal, public drogon_model::openproject6::MessageJournals {
};

} // namespace openproj::models::JournalN

} // namespace openproj::models

} // namespace openproj
#endif
