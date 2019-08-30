#ifndef SONG_H
#define SONG_H

#include <vector>
#include <string>
using std::string;
using std::vector;

#include "../baseservice.h"
namespace madmin {
class Song : public BaseService
{
public:
  // class Song extends database_object implements media, library_item  {
  //   use \Lib\Metadata\Metadata;
    Song(const MAdminContextPtr &);
    void setupTable() override;
    json handleEvent(json event, unsigned long next, json args) override;
    json handleBinaryEvent(json event, unsigned long next, std::string &message);


    /* Variables from DB */

//    int id;
//    string file;
//    int album;
//    int artist;
//    string title;
//    int year;
//    int bitrate;
//    int rate;
//    string mode;
//    int size;
//    int time;
//    int track;
//    string album_mbid;
//    string artist_mbid;
//    string albumartist_mbid;
//    string type;
//    string mime;
//    bool played;
//    bool enabled;
//    int addition_time;
//    int update_time;
//    string mbid; // MusicBrainz ID
//    int catalog;
//    int waveform; // int|null
//    int user_upload;// int|null
//    int license;// int|null
//    string composer;
//    string catalog_number;
//    int channels;
//    vector<string> tags;
//    string label;
//    string language;
//    string comment;
//    string lyrics;
//    float replaygain_track_gain;
//    float replaygain_track_peak;
//    float replaygain_album_gain;
//    float replaygain_album_peak;
//    string f_title;
//    string f_artist;
//    string f_album;
//    string f_artist_full;
//    int albumartist;
//    string f_albumartist_full;
//    string f_album_full;
//    string f_time;
//    string f_time_h;
//    string f_track;
//    string f_bitrate;
//    string link;
//    string f_file;
//    string f_title_full;
//    string f_link;
//    string f_album_link;
//    string f_artist_link;
//    string f_albumartist_link;
//    string f_tags;
//    string f_size;
//    string f_lyrics;
//    string f_pattern;
//    int count;
//    string f_publisher;
//    string f_composer;
//    string f_license;

    /* Setting Variables */
//    bool _fake = false; // If this is a 'construct_from_array' object

    /**
     * Aliases used in insert function
     */
//    public static $aliases = array(
//        'mb_trackid','mbid','mb_albumid','mb_albumid_group','mb_artistid','mb_albumartistid','genre','publisher'
//    );

    /**
     * Constructor
     *
     * Song class, for modifing a song.
     * @param int|null $id
     */
    //Song(int id = null, $limit_threshold = '')

    /**
     * insert
     *
     * This inserts the song described by the passed array
     * @param array $results
     * @return int|boolean
     */
    //static long insert(array $results);

    /**
     * gc
     *
     * Cleans up the song_data table
     */
    //static void function gc();

    /**
     * build_cache
     *
     * This attempts to reduce queries by asking for everything in the
     * browse all at once and storing it in the cache, this can help if the
     * db connection is the slow point.
     * @param int[] $song_ids
     * @return boolean
     */
    //static bool build_cache($song_ids, $limit_threshold = '')

    /**
     * _get_info
     * @return array|boolean
     */
private:
    //bool function _get_info($limit_threshold = '');
public:
    /**
      * _get_ext_info
     * This function gathers information from the song_ext_info table and adds it to the
     * current object
     * @return array
     */
    //public function _get_ext_info()

    /**
      * fill_ext_info
     * This calls the _get_ext_info and then sets the correct vars
     */
    //public function fill_ext_info()

    /**
     * type_to_mime
     *
     * Returns the mime type for the specified file extension/type
     * @param string $type
     * @return string
     */
    //static string type_to_mime(string type);
    /**
     * get_disabled
     *
     * Gets a list of the disabled songs for and returns an array of Songs
     * @param int $count
     * @return int[]
     */
    //static vector<int> function get_disabled(int count = 0);
    /**
     * find_duplicates
     *
     * This function takes a search type and returns a list of probable
     * duplicates
     * @param string $search_type
     * @return array
     */
    //public static function find_duplicates(string search_type)
    //static int find(vector<string> data);

    /**
     * Get duplicate information.
     * @param array $dupe
     * @param string $search_type
     * @return int[]
     */
    //public static function get_duplicate_info($dupe, string search_type)
    /**
     * get_album_name
     * gets the name of $this->album, allows passing of id
     * @param int $album_id
     * @return string
     */
    //public function get_album_name($album_id=0)
    /**
     * get_artist_name
     * gets the name of $this->artist, allows passing of id
     * @param int $artist_id
     * @return string
     */
    //public function get_artist_name($artist_id=0)
    /**
     * get_album_artist_name
     * gets the name of $this->albumartist, allows passing of id
     * @param int $album_artist_id
     * @return string
     */
    //public function get_album_artist_name($album_artist_id=0)
    /**
     * set_played
     * this checks to see if the current object has been played
     * if not then it sets it to played. In any case it updates stats.
     * @param int $user
     * @param string $agent
     * @param array $location
     * @return boolean
     */
    //public function set_played($user, $agent, $location)
    /**
     * compare_song_information
     * this compares the new ID3 tags of a file against
     * the ones in the database to see if they have changed
     * it returns false if nothing has changes, or the true
     * if they have. Static because it doesn't need this
     * @param \Song $song
     * @param \Song $new_song
     * @return array
     */
    //public static function compare_song_information(Song $song, Song $new_song)
    //public static function compare_media_information($media, $new_media, $string_array, $skip_array)
    //private static function clean_string_field_value($value)
    /**
     * update
     * This takes a key'd array of data does any cleaning it needs to
     * do and then calls the helper functions as needed.
     * @param array $data
     * @return int
     */
    //public function update(array $data)
    /**
     * write_id3
     * Write the current song id3 metadata to the file
     */
    //public function write_id3()
    /**
     * write_id3_for_song
     * Write id3 metadata to the file for the excepted song id
     * @param int $song_id
     */
    //public static function write_id3_for_song($song_id)
    /**
     * update_song
     * this is the main updater for a song it actually
     * calls a whole bunch of mini functions to update
     * each little part of the song... lastly it updates
     * the "update_time" of the song
     * @param int $song_id
     * @param \Song $new_song
     */
    //public static function update_song($song_id, Song $new_song)
    /**
     * update_year
     * update the year tag
     * @param int $new_year
     * @param int $song_id
     */
    //public static function update_year($new_year, $song_id)
    /**
     * update_label
     * This updates the label tag of the song
     * @param string $new_value
     * @param int $song_id
     */
    //public static function update_label($new_value, $song_id)
    /**
     * update_language
     * This updates the language tag of the song
     * @param string $new_lang
     * @param int $song_id
     */
    //public static function update_language($new_lang, $song_id)
    /**
     * update_comment
     * updates the comment field
     * @param string $new_comment
     * @param int $song_id
     */
    //public static function update_comment($new_comment, $song_id)
    /**
     * update_lyrics
     * updates the lyrics field
     * @param string $new_lyrics
     * @param int $song_id
     */
    //public static function update_lyrics($new_lyrics, $song_id)
    /**
     * update_title
     * updates the title field
     * @param string $new_title
     * @param int $song_id
     */
    //public static function update_title($new_title, $song_id)
    /**
     * update_composer
     * updates the composer field
     * @param string $new_value
     * @param int $song_id
     */
    //public static function update_composer($new_value, $song_id)
    /**
     * update_publisher
     * updates the publisher field
     * @param string $new_value
     * @param int $song_id
     */
    //public static function update_publisher($new_value, $song_id)
    /**
     * update_bitrate
     * updates the bitrate field
     * @param int $new_bitrate
     * @param int $song_id
     */
    //public static function update_bitrate($new_bitrate, $song_id)
    /**
     * update_rate
     * updates the rate field
     * @param int $new_rate
     * @param int $song_id
     */
    //public static function update_rate($new_rate, $song_id)
    /**
     * update_mode
     * updates the mode field
     * @param string $new_mode
     * @param int $song_id
     */
    //public static function update_mode($new_mode, $song_id)
    /**
     * update_size
     * updates the size field
     * @param int $new_size
     * @param int $song_id
     */
    //public static function update_size($new_size, $song_id)
    /**
     * update_time
     * updates the time field
     * @param int $new_time
     * @param int $song_id
     */
    //public static function update_time($new_time, $song_id)
    /**
     * update_track
     * this updates the track field
     * @param int $new_track
     * @param int $song_id
     */
    //public static function update_track($new_track, $song_id)
    /**
     * update_mbid
     * updates mbid field
     * @param string $new_mbid
     * @param int $song_id
     */
    //public static function update_mbid($new_mbid, $song_id)
    /**
     * update_license
     * updates license field
     * @param string $new_license
     * @param int $song_id
     */
    //public static function update_license($new_license, $song_id)
    /**
     * update_artist
     * updates the artist field
     * @param int $new_artist
     * @param int $song_id
     */
    //public static function update_artist($new_artist, $song_id)
    /**
     * update_album
     * updates the album field
     * @param int $new_album
     * @param int $song_id
     */
    //public static function update_album($new_album, $song_id)
    /**
     * update_utime
     * sets a new update time
     * @param int $song_id
     * @param int $time
     */
    //public static function update_utime($song_id, $time=0)
    /**
     * update_played
     * sets the played flag
     * @param boolean $new_played
     * @param int $song_id
     */
    //public static function update_played($new_played, $song_id)
    /**
     * update_enabled
     * sets the enabled flag
     * @param boolean $new_enabled
     * @param int $song_id
     */
    //public static function update_enabled($new_enabled, $song_id)
    /**
     * _update_item
     * This is a private function that should only be called from within the song class.
     * It takes a field, value song id and level. first and foremost it checks the level
     * against $GLOBALS['user'] to make sure they are allowed to update this record
     * it then updates it and sets $this->{$field} to the new value
     * @param string $field
     * @param mixed $value
     * @param int $song_id
     * @param int $level
     * @param boolean $check_owner
     * @return boolean
     */
    //private static function _update_item($field, $value, $song_id, $level, $check_owner = false)
    /**
     * _update_ext_item
     * This updates a song record that is housed in the song_ext_info table
     * These are items that aren't used normally, and often large/informational only
     * @param string $field
     * @param mixed $value
     * @param int $song_id
     * @param int $level
     * @param boolean $check_owner
     * @return boolean
     */
    //private static function _update_ext_item($field, $value, $song_id, $level, $check_owner = false)
    /**
     * format
     * This takes the current song object
     * and does a ton of formating on it creating f_??? variables on the current
     * object
     */
    //public function format($details = true)
    /**
     * Get item keywords for metadata searches.
     * @return array
     */
    //public function get_keywords()
    /**
     * Get item fullname.
     * @return string
     */
    //public function get_fullname()
    /**
     * Get parent item description.
     * @return array|null
     */
    //public function get_parent()
    /**
     * Get item childrens.
     * @return array
     */
    //public function get_childrens()
    /**
     * Search for item childrens.
     * @param string $name
     * @return array
     */
    //public function search_childrens($name)
    /**
     * Get all childrens and sub-childrens medias.
     * @param string $filter_type
     * @return array
     */
    //public function get_medias($filter_type = null)
    /**
     * get_catalogs
     *
     * Get all catalog ids related to this item.
     * @return int[]
     */
    //public function get_catalogs()
    /**
     * Get item's owner.
     * @return int|null
     */
    //public function get_user_owner()
    /**
     * Get default art kind for this item.
     * @return string
     */
    //public function get_default_art_kind()
    //public function get_description()
    //public function display_art($thumb = 2, $force = false)
    /**
     * get_fields
     * This returns all of the 'data' fields for this object, we need to filter out some that we don't
     * want to present to a user, and add some that don't exist directly on the object but are related
     * @return array
     */
    //public static function get_fields()
    /**
     * get_from_path
     * This returns all of the songs that exist under the specified path
     * @param string $path
     * @return int[]
     */
    //public static function get_from_path($path)
    /**
     * @function    get_rel_path
     * @discussion    returns the path of the song file stripped of the catalog path
     *        used for mpd playback
     * @param string $file_path
     * @param int $catalog_id
     * @return string
     */
    //public function get_rel_path($file_path=null, $catalog_id=0)
    /**
     * Generate generic play url.
     * @param string $object_type
     * @param int $object_id
     * @param string $additional_params
     * @param boolean $local
     * @return string
     */
    //public static function generic_play_url($object_type, $object_id, $additional_params, $player=null, $local=false)
    /**
     * play_url
     * This function takes all the song information and correctly formats a
     * a stream URL taking into account the downsmapling mojo and everything
     * else, this is the true function
     * @param int $oid
     * @param string $additional_params
     * @param boolean $local
     * @return string
     */
    //public static function play_url($oid, $additional_params='', $player=null, $local=false)
    /**
     * Get stream name.
     * @return string
     */
    //public function get_stream_name()
    /**
     * get_recently_played
     * This function returns the last X songs that have been played
     * it uses the popular threshold to figure out how many to pull
     * it will only return unique object
     * @param int $user_id
     * @return array
     */
    //public static function get_recently_played($user_id=0)
    /**
     * Get stream types.
     * @return array
     */
    //public function get_stream_types($player = null)
    /**
     * Get stream types for media type.
     * @param string $type
     * @return string
     */
    //public static function get_stream_types_for_type($type, $player = null)
    /**
     * Get transcode settings for media.
     * @param string $source
     * @param string $target
     * @param string $media_type
     * @param array $options
     * @return array|boolean
     */
    //public static function get_transcode_settings_for_media($source, $target = null, $player = null, $media_type = 'song', $options=array())
    /**
     * Get transcode settings.
     * @param string $target
     * @param array $options
     * @return array|boolean
     */
    //public function get_transcode_settings($target = null, $player = null, $options=array())
    /**
     * Get lyrics.
     * @return array
     */
    //public function get_lyrics()
    /**
     * Run custom play action.
     * @param int $action_index
     * @param string $codec
     * @return array
     */
    //public function run_custom_play_action($action_index, $codec='')
    /**
     * Show custom play actions.
     */
    //public function show_custom_play_actions()
    /**
     * Get custom play actions.
     * @return array
     */
    //public static function get_custom_play_actions()
    /*
     * get_metadata
     * Get an array of song metadata
     * @return array
     */
    //public function get_metadata()
    //public function getId()
    /**
     * Update Metadata from array
     * @param array $value
     */
    //public function updateMetadata($value)
    /**
     * Remove the song from disk.
     */
    //public function remove_from_disk()
private:
    //Binary functin:
    json save_song_binary(json event, std::string &message);
};
}
#endif // SONG_H
