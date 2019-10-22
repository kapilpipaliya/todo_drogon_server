#include "type.h"
namespace dgraph {
namespace grpcclient {
/* moved
std::string errorToString(error err) {
  switch (err) {
    case ERR_NO_CLIENTS:
      return "No clients provided in DgraphClient constructor";
    case ERR_FINISHED:
      return "Transaction has already been committed or discarded";
    case ERR_ABORTED:
      return "Transaction has been aborted. Please retry";
    case ERR_BEST_EFFORT_REQUIRED_READ_ONLY:
      return "Best effort only works for read-only queries";
    case ERR_READ_ONLY:
      return "Readonly transaction cannot run mutations or be committed";
    case ERR_REFRESH_JWT_EMPTY:
      return "refresh jwt should not be empty";
  }
}*/

}  // namespace grpcclient
}  // namespace dgraph
