#ifndef CATALOG_H
#define CATALOG_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "sql/query.h"

namespace music {
namespace service {
class Catalog {
 public:
  Catalog(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  virtual ~Catalog() = default;
  void setupTable();

  /**
   * Catalog Class
   *
   * This class handles all actual work in regards to the catalog,
   * it contains functions for creating/listing/updated the catalogs.
   *
   */
 protected:
  /*
   * This is a private var that's used during catalog builds
   * @var array $_playlists
   */
  // protected $_playlists = array();

  /*
   * Cache all files in catalog for quick lookup during add
   * @var array $_filecache
   */
  // protected $_filecache = array();

  // Used in functions
  /**
   * @var array $albums
   */
  // protected static $albums    = array();
  /**
   * @var array $artists
   */
  // protected static $artists    = array();
  /**
   * @var array $tags
   */
  // protected static $tags    = array();
 public:
  // virtual std::string get_type() = 0;
  // virtual std::string get_description() = 0;
  // virtual std::string get_version() = 0;
  // virtual std::string get_create_help() = 0;
  // virtual bool is_installed() = 0;
  // virtual bool install() = 0;
  // virtual std::string add_to_catalog($options = null) = 0; // fix return
  // virtual std::string verify_catalog_proc() = 0; // fix return
  // virtual std::string clean_catalog_proc() = 0; // fix return
  /**
   * @return array
   */
  // virtual std::string catalog_fields() = 0;
  // virtual std::string get_rel_path($file_path) = 0;
  /**
   * @return media|null
   */
  // virtual std::string prepare_media($media) = 0;

  /**
   * Check if the catalog is ready to perform actions (configuration completed,
   * ...)
   */
  bool isReady() { return true; }

  /**
   * Show a message to make the catalog ready.
   */
  void show_ready_process() { /* Do nothing.*/
  }

  /**
   * Perform the last step process to make the catalog ready.
   */
  void perform_ready() { /* Do nothing.*/
  }

  /**
   * uninstall
   * This removes the remote catalog
   * @return boolean
   */
  bool uninstall();
  /**
   * Create a catalog from its id.
   * @param int $id
   * @return Catalog|null
   */
  static void create_from_id(int id);
  /**
   * create_catalog_type
   * This function attempts to create a catalog type
   * all Catalog modules should be located in
   * /modules/catalog/<name>/<name>.class.php
   * @param std::string $type
   * @param int $id
   * @return Catalog|null
   */
  static void create_catalog_type(std::string type, int id = 0);
  /**
   * Show dropdown catalog types.
   * @param std::string $divback
   */
  // static void show_catalog_types($divback = 'catalog_type_fields');
  /**
   * get_catalog_types
   * This returns the catalog types that are available
   * @return std::string[]
   */
  static void get_catalog_types();
  /**
   * Check if a file is an audio.
   * @param std::string $file
   * @return boolean
   */
  static void is_audio_file(std::string file);
  /**
   * Check if a file is a video.
   * @param std::string $file
   * @return boolean
   */
  static void is_video_file(std::string file);
  /**
   * Check if a file is a playlist.
   * @param std::string $file
   * @return boolean
   */
  static void is_playlist_file(std::string file);
  /**
   * Get catalog info from table.
   * @param int $id
   * @param std::string $table
   * @return array
   */
  // public function get_info(int id, $table = 'catalog');
  /**
   * Get enable sql filter;
   * @param std::string $type
   * @param int $id
   * @return std::string
   */
  // static void get_enable_filter($type, int id);
  /**
   * _create_filecache
   *
   * This populates an array which is used to speed up the add process.
   * @return boolean
   */
  // protected function _create_filecache();
  /**
   * update_enabled
   * sets the enabled flag
   * @param boolean $new_enabled
   * @param int $catalog_id
   */
  // static void update_enabled($new_enabled, int catalog_id);
  /**
   * _update_item
   * This is a private function that should only be called from within the
   * catalog class. It takes a field, value, catalog id and level. first and
   * foremost it checks the level against $GLOBALS['user'] to make sure they are
   * allowed to update this record it then updates it and sets $this->{$field}
   * to the new value
   * @param std::string $field
   * @param mixed $value
   * @param int $catalog_id
   * @param int $level
   * @return boolean
   */
  // private static function _update_item($field, $value, long catalog_id,
  // $level);
  /**
   * format
   *
   * This makes the object human-readable.
   */
  // public function format();
  /**
   * get_catalogs
   *
   * Pull all the current catalogs and return an array of ids
   * of what you find
   * @return int[]
   */
  // static void get_catalogs($filter_type="");
  /**
   * Get last catalogs update.
   * @param int[]|null $catalogs
   * @return int
   */
  // static void getLastUpdate($catalogs = null);
  /**
   * get_stats
   *
   * This returns an hash with the #'s for the different
   * objects that are associated with this catalog. This is used
   * to build the stats box, it also calculates time.
   * @param int|null $catalog_id
   * @return array
   */
  // static void get_stats(int catalog_id = null);
  /**
   * create
   *
   * This creates a new catalog entry and associate it to current instance
   * @param array $data
   * @return int
   */
  // static void create($data);
  /**
   * count_tags
   *
   * This returns the current number of unique tags in the database.
   * @return int
   */
  // static void count_tags();
  /**
   * count_medias
   *
   * This returns the current number of songs, videos, albums, and artists
   * in this catalog.
   * @param int|null $catalog_id
   * @return array
   */
  // static void count_medias(int catalog_id = null);
  /**
   *
   * @param std::string $type
   * @param int|null $user_id
   * @return std::string
   */
  // static void get_uploads_sql($type, $user_id=null);
  /**
   * get_album_ids
   *
   * This returns an array of ids of albums that have songs in this
   * catalog
   * @return int[]
   */
  // public function get_album_ids();
  /**
   * get_video_ids
   *
   * This returns an array of ids of videos in this catalog
   * @param std::string $type
   * @return int[]
   */
  // public function get_video_ids($type = "");
  /**
   *
   * @param int[]|null $catalogs
   * @param std::string $type
   * @return \Video[]
   */
  // static void get_videos($catalogs = null, $type = "");
  /**
   *
   * @param int|null $catalog_id
   * @param std::string $type
   * @return int
   */
  // static int get_videos_count(int catalog_id = null, $type = "");
  /**
   * get_tvshow_ids
   *
   * This returns an array of ids of tvshows in this catalog
   * @return int[]
   */
  // public function get_tvshow_ids();
  /**
   *
   * @param int[]|null $catalogs
   * @return \TVShow[]
   */
  // static void get_tvshows($catalogs = null);
  /**
   * get_artist_ids
   *
   * This returns an array of ids of artist that have songs in this
   * catalog
   * @return int[]
   */
  // public function get_artist_ids();
  /**
   * get_artists
   *
   * This returns an array of artists that have songs in the catalogs parameter
   * @param array|null $catalogs
   * @return \Artist[]
   */
  // static void get_artists($catalogs = null, $size = 0, $offset = 0);
  // static void search_childrens($name, int catalog_id = 0);
  /**
   * get_albums
   *
   * Returns an array of ids of albums that have songs in the catalogs parameter
   * @param int $size
   * @param int $offset
   * @param int[]|null $catalogs
   * @return int[]
   */
  // static void get_albums($size = 0, $offset = 0, $catalogs = null);
  /**
   * get_albums_by_artist
   *
   * Returns an array of ids of albums that have songs in the catalogs
   * parameter, grouped by artist
   * @param int $size
   * @oaram int $offset
   * @param int[]|null $catalogs
   * @return int[]
   */
  // static void get_albums_by_artist($size = 0, $offset = 0, $catalogs = null);
  /**
   * get_podcast_ids
   *
   * This returns an array of ids of podcasts in this catalog
   * @return int[]
   */
  // public function get_podcast_ids();
  /**
   *
   * @param int[]|null $catalogs
   * @return \Podcast[]
   */
  // static void get_podcasts($catalogs = null);
  /**
   * get_newest_podcasts_ids
   *
   * This returns an array of ids of latest podcast episodes in this catalog
   * @return int[]
   */
  // public function get_newest_podcasts_ids();
  /**
   *
   * @param int[]|null $catalogs
   * @return \Podcast_Episode[]
   */
  // static void get_newest_podcasts($catalogs = null);
  /**
   *
   * @param std::string $type
   * @param int $id
   */
  // public function gather_art_item($type, int id);
  /**
   * gather_art
   *
   * This runs through all of the albums and finds art for them
   * This runs through all of the needs art albums and trys
   * to find the art for them from the mp3s
   * @param int[]|null $songs
   * @param int[]|null $videos
   */
  // public function gather_art($songs = null, $videos = null);
  /**
   * get_songs
   *
   * Returns an array of song objects.
   * @return \Song[]
   */
  // public function get_songs();
  /**
   * dump_album_art
   *
   * This runs through all of the albums and tries to dump the
   * art for them into the 'folder.jpg' file in the appropriate dir.
   * @param array $methods
   */
  // public function dump_album_art($methods = array(););
  /**
   * update_last_update
   * updates the last_update of the catalog
   */
  // protected function update_last_update();
  /**
   * update_last_add
   * updates the last_add of the catalog
   */
  // public function update_last_add();
  /**
   * update_last_clean
   * This updates the last clean information
   */
  // public function update_last_clean();
  /**
   * update_settings
   * This function updates the basic setting of the catalog
   * @param array $data
   * @return boolean
   */
  // static void update_settings($data);
  /**
   * update_single_item
   * updates a single album,artist,song from the tag data
   * this can be done by 75+
   * @param std::string $type
   * @param int $id
   */
  // static void update_single_item($type, int id);
  /**
   * update_media_from_tags
   * This is a 'wrapper' function calls the update function for the media
   * type in question
   * @param \media $media
   * @param std::string $sort_pattern
   * @param std::string $rename_pattern
   * @return array
   */
  // static void update_media_from_tags($media, $gather_types = array('music');,
  // $sort_pattern="", $rename_pattern="");
  /**
   * update_song_from_tags
   * Updates the song info based on tags; this is called from a bunch of
   * different places and passes in a full fledged song object, so it's a
   * static function.
   * FIXME: This is an ugly mess, this really needs to be consolidated and
   * cleaned up.
   * @param array $results
   * @param \Song $song
   * @return array
   */
  // static void update_song_from_tags($results, Song $song);
  // static void update_video_from_tags($results, Video $video);
  /**
   * Get rid of all tags found in the libraryItem
   * @param library_item $libraryItem
   * @param array $metadata
   * @return array
   */
  // private static function get_clean_metadata(library_item $libraryItem,
  // $metadata);
  /**
   *
   * @param library_item $libraryItem
   * @param type $metadata
   */
  // static void add_metadata(library_item $libraryItem, $metadata);
  // public function get_media_tags($media, $gather_types, $sort_pattern,
  // $rename_pattern);
  /**
   *
   * @param std::string $media_type
   * @return array
   */
  // public function get_gather_types($media_type = "");
  static void clean_empty_albums();
  /**
   * clean_catalog
   *
   * Cleans the catalog of files that no longer exist.
   */
  // public function clean_catalog();
  /**
   * verify_catalog
   * This function verify the catalog
   */
  // public function verify_catalog();
  /**
   * gc
   *
   * This is a wrapper function for all of the different cleaning
   * functions, it runs them in an order that resembles correctness.
   */
  // static void gc();
  /**
   * trim_prefix
   * Splits the prefix from the std::string
   * @param std::string $std::string
   * @return array
   */
  // static void trim_prefix($std::string);
  // static void normalize_year($year);
  /**
   * trim_slashed_list
   * Return only the first item from / separated list
   * @param std::string $std::string
   * @return std::string
   */
  // static void trim_slashed_list($std::string);
  /**
   * trim_featuring
   * Splits artists featuring from the std::string
   * @param std::string $std::string
   * @return array
   */
  // static void trim_featuring($std::string);
  /**
   * check_title
   * this checks to make sure something is
   * set on the title, if it isn't it looks at the
   * filename and trys to set the title based on that
   * @param std::string $title
   * @param std::string $file
   */
  // static void check_title($title, std::string file="");
  /**
   * playlist_import
   * Attempts to create a Public Playlist based on the playlist file
   * @param std::string $playlist
   * @return array
   */
  // static void import_playlist($playlist);
  /**
   * parse_m3u
   * this takes m3u filename and then attempts to found song filenames listed in
   * the m3u
   * @param std::string $data
   * @return array
   */
  // static void parse_m3u($data);
  /**
   * parse_pls
   * this takes pls filename and then attempts to found song filenames listed in
   * the pls
   * @param std::string $data
   * @return array
   */
  // static void parse_pls($data);
  /**
   * parse_asx
   * this takes asx filename and then attempts to found song filenames listed in
   * the asx
   * @param std::string $data
   * @return array
   */
  // static void parse_asx($data);
  /**
   * parse_xspf
   * this takes xspf filename and then attempts to found song filenames listed
   * in the xspf
   * @param std::string $data
   * @return array
   */
  // static void parse_xspf($data);
  /**
   * delete
   * Deletes the catalog and everything associated with it
   * it takes the catalog id
   * @param int $catalog_id
   */
  static bool delet(long catalog_id, const std::string& type);
  /**
   * exports the catalog
   * it exports all songs in the database to the given export type.
   * @param std::string $type
   * @param int|null $catalog_id
   */
  // static void export($type, int catalog_id =null);
  /**
   * Updates album tags from given song
   * @param Song $song
   */
  // protected static function updateAlbumTags(Song $song);
  /**
   * Updates artist tags from given song
   * @param Song $song
   */
  // protected static function updateArtistTags(Song $song);
  /**
   * Get all tags from all Songs from [type] (artist, album, ...);
   * @param std::string $type
   * @param integer $id
   * @return array
   */
  // protected static function getSongTags($type, int id);
  // static void can_remove($libitem, $user = null);
  // static void process_action($action, $catalogs, $options = null);
  std::shared_ptr<websocket::music::MAdminContext>& getContext() {
    return context;
  }

 private:
  int $id{};
  std::string name;
  int last_update{};
  int last_add{};
  int last_clean{};
  std::string key;
  std::string rename_pattern;
  std::string sort_pattern;
  std::string catalog_type;
  std::string gather_types;
  std::string f_name;
  std::string link;
  std::string f_link;
  std::string f_update;
  std::string f_add;
  std::string f_clean;

  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
#endif  // CATALOG_H
