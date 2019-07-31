#ifndef POSTQUERY_H
#define POSTQUERY_H
#include "core/tables/Table.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

void query_post(Table &t);

void query_tag(Table &t);

#endif // POSTQUERY_H
