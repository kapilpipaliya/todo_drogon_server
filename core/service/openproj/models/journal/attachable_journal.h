#pragma once
#include "base_journal.h"
namespace openproj {
namespace JournalN {
class AttachableJournal : public JournalN::BaseJournal {
//  this->table_name = 'attachable_journals'

  // belongs_to :attachment
};
}
}

//::AttachableJournal = JournalN::AttachableJournal
