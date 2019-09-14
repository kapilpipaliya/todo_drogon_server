#ifndef CATALOGLOCAL_H
#define CATALOGLOCAL_H
#include <vector>
#include "../../class/catalog.h"
/**
 * Local Catalog Class
 *
 * This class handles all actual work in regards to local catalogs.
 *
 */
namespace madmin {
class CatalogLocal : public Catalog {
 public:
  CatalogLocal(const std::shared_ptr<websocket::MAdminContext> &);
  void setupTable();
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  /**
   * Constructor
   *
   * Catalog class constructor, pulls catalog information
   */
  //    CatalogLocal(int catalog_id)
  //    {
  //        if (catalog_id) {
  //            id = intval(catalog_id);
  //            $info     = get_info(catalog_id);

  //            foreach ($info as $key => $value) {
  //                $key = $value;
  //            }
  //        }
  //    }

  /**
   * get_description
   * This returns the description of this catalog
   */
  std::string get_description() { return description; }  // get_description
  /**
   * get_version
   * This returns the current version
   */
  std::string get_version() { return version; }  // get_version
  /**
   * get_type
   * This returns the current catalog type
   */
  std::string get_type() { return type; }  // get_type
  /**
   * get_create_help
   * This returns hints on catalog creation
   */
  std::string get_create_help() { return ""; }  // get_create_help
  /**
   * is_installed
   * This returns true or false if local catalog is installed
   */
  bool is_installed() { return true; }  // is_installed
  /**
   * install
   * This function installs the local catalog
   */
  bool install() { return true; }  // install
  std::vector<std::string> catalog_fields();
  /**
   * get_from_path
   *
   * Try to figure out which catalog path most closely resembles this one.
   * This is useful when creating a new catalog to make sure we're not
   * doubling up here.
   */
  // bool function get_from_path(std::string path);
  /**
   * create_type
   *
   * This creates a new catalog type entry for a catalog
   * It checks to make sure its parameters is not already used before creating
   * the catalog.
   */
  // static bool function create_type(int catalog_id, std::vector<std::string>
  // data);
  /**
   * add_files
   *
   * Recurses through path and pulls out all mp3s and returns the
   * full path in an array. Passes gather_type to determine if we need to
   * check id3 information against the db.
   */
  bool add_files(std::string path, std::vector<std::string> options);

  bool add_file(std::string full_file, std::vector<std::string> options);
  /**
   * add_to_catalog
   * this function adds new files to an
   * existing catalog
   */
  // void add_to_catalog(std::vector<std::string> options = null);
  /**
   * verify_catalog_proc
   * This function compares the DB's information with the ID3 tags
   */
  // std::vector<int> verify_catalog_proc();
  /**
   * _verify_chunk
   * This verifies a chunk of the catalog, done to save
   * memory
   */
  int clean_catalog_proc();
  /**
   * _clean_chunk
   * This is the clean function, its broken into
   * said chunks to try to save a little memory
   */
  // long insert_local_video($file, $options = array())
  // bool check_local_mp3($full_file, $gather_type="");
  // std::string get_rel_path($file_path);
  /**
   * format
   *
   * This makes the object human-readable.
   */
  // public function format()
  // public function prepare_media($media)
 private:
  // int _verify_chunk($media_type, $chunk, $chunk_size);
  /**
   * clean catalog procedure
   *
   * Removes local songs that no longer exist.
   */
  // std::vector<int> _clean_chunk($media_type, $chunk, $chunk_size);
  /**
   * insert_local_song
   *
   * Insert a song that isn't already in the database.
   */
  // long insert_local_song($file, $options = array())
  /**
   * insert_local_video
   * This inserts a video file into the video file table the tag
   * information we can get is super sketchy so it's kind of a crap shoot
   * here
   */
  void sync_podcasts();
  /**
   * check_local_mp3
   * Checks the song to see if it's there already returns true if found, false
   * if not
   */

  std::string version = "000001";
  std::string type = "local";
  std::string description = "Local Catalog";

  // int count; // This cause trouble with base function count();
  std::vector<int> added_songs_to_gather;
  std::vector<int> added_videos_to_gather;
  std::string path;

  sql::Query query;
};
}  // namespace madmin
#endif  // CATALOGLOCAL_H
