#ifndef MAINACTORTYPE_H
#define MAINACTORTYPE_H

#include "caf/all.hpp"
namespace superactor {
namespace system {
enum MainActorType { JAdmin, JUser, MAdmin, TODO };
using run_atom = caf::atom_constant<caf::atom("run")>;
using exit_atom = caf::atom_constant<caf::atom("exit")>;
}  // namespace system
}  // namespace superactor
#endif  // MAINACTORTYPE_H
