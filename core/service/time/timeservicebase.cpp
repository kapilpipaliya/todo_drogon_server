#include "timeservicebase.h"

TimeServiceBase::TimeServiceBase() {
  dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
}
