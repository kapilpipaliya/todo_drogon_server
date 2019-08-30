#include "catalog.h"
#include "dba.h"
using namespace  madmin;
Catalog::Catalog(const MAdminContextPtr &context_): BaseService(context_)
{

}

void Catalog::setupTable()
{

}

void Catalog::clean_empty_albums()
{
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

bool Catalog::delet(long catalog_id, string type)
{
    // Large catalog deletion can take time
    //set_time_limit(0);

    // First remove the songs in this catalog
    string sql1 =  "DELETE FROM music.song WHERE catalog_id = $1";
    auto db_results = Dba::write(sql1, catalog_id);

    // Only if the previous one works do we go on
    //if (!db_results) {
       // return false;
    //}
    clean_empty_albums();

    string sql2 =  "DELETE FROM music.video WHERE catalog_id = $1";
    auto db_results2 = Dba::write(sql2, catalog_id);

    //if (!db_results) {
   //     return false;
    //}
    //auto catalog = self::create_from_id(catalog_id);

    //if (!catalog->id) {
     //   return false;
   // }

    //string sql3 =  'DELETE FROM music.catalog_' . catalog->get_type() . ' WHERE catalog_id = $';
    string sql3 = "DELETE FROM music.catalog_" + type +" WHERE catalog_id = $1";
    auto db_results3 = Dba::write(sql3, catalog_id);

    //if (!db_results) {
       // return false;
    //}

    // Next Remove the Catalog Entry it's self
    auto sql4 = "DELETE FROM music.catalog WHERE id = $1";
    Dba::write(sql4, catalog_id);

    return true;
}
