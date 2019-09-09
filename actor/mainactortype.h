#ifndef MAINACTORTYPE_H
#define MAINACTORTYPE_H

#include "caf/all.hpp"

enum MainActorType { JAdmin, JUser, MAdmin };

using run_atom = caf::atom_constant<caf::atom("run")>;
using exit_atom = caf::atom_constant<caf::atom("exit")>;

#endif  // MAINACTORTYPE_H
