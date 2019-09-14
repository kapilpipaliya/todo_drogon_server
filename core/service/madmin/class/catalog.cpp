#include "catalog.h"

#include <utility>
#include "../../../sql/dba.h"

madmin::Catalog::Catalog(std::shared_ptr<websocket::MAdminContext> context_)
    : context(std::move(context_)) {
  setupTable();
}

nlohmann::json madmin::Catalog::handleEvent(nlohmann::json event,
                                            unsigned long next,
                                            nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return query.allData(event, args);
  }
  if (event_cmp == "header") {
    return query.headerData(event, args);
  } else if (event_cmp == "ins") {
    return query.ins(event, args);
  } else if (event_cmp == "upd") {
    return query.upd(event, args);
  } else if (event_cmp == "del") {
    return query.del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

void madmin::Catalog::setupTable() {}

void madmin::Catalog::clean_empty_albums() {
  /*
  auto sql = "SELECT id FROM music.album WHERE NOT EXISTS "
      "(SELECT id FROM song WHERE song.album = album.id)";
  auto db_results = Dba::read(sql);
  while (albumid = Dba::fetch_assoc($db_results)) {
      $id          = $albumid['id'];
      $sql         = "DELETE FROM album WHERE id = ?";
      $db_results  = Dba::write($sql, array($id));
  }*/
}

bool madmin::Catalog::delet(long catalog_id, const std::string& type) {
  // Large catalog deletion can take time
  // set_time_limit(0);

  // First remove the songs in this catalog
  std::string sql1 = "DELETE FROM music.song WHERE catalog_id = $1";
  auto db_results = Dba::write(sql1, catalog_id);

  // Only if the previous one works do we go on
  // if (!db_results) {
  // return false;
  //}
  clean_empty_albums();

  std::string sql2 = "DELETE FROM music.video WHERE catalog_id = $1";
  auto db_results2 = Dba::write(sql2, catalog_id);

  // if (!db_results) {
  //     return false;
  //}
  // auto catalog = self::create_from_id(catalog_id);

  // if (!catalog->id) {
  //   return false;
  // }

  // std::string sql3 =  'DELETE FROM music.catalog_' . catalog->get_type() . '
  // WHERE catalog_id = $';
  std::string sql3 =
      "DELETE FROM music.catalog_" + type + " WHERE catalog_id = $1";
  auto db_results3 = Dba::write(sql3, catalog_id);

  // if (!db_results) {
  // return false;
  //}

  // Next Remove the Catalog Entry it's self
  auto sql4 = "DELETE FROM music.catalog WHERE id = $1";
  Dba::write(sql4, catalog_id);

  return true;
}
