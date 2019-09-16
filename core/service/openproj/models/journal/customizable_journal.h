#pragma once
#include "base_journal.h"
namespace openproj {
namespace JournalN {
class CustomizableJournal : public JournalN::BaseJournal {
//  this->table_name = 'customizable_journals'

  // belongs_to :custom_field, foreign_key: :custom_field_id
};
}
}

//::CustomizableJournal = JournalN::CustomizableJournal
