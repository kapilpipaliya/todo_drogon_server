#ifndef CATALOGLOCAL_H
#define CATALOGLOCAL_H
#include "../../class/catalog.h"
#include <vector>
/**
 * Local Catalog Class
 *
 * This class handles all actual work in regards to local catalogs.
 *
 */
namespace madmin {
class CatalogLocal : public Catalog
{
    string version        = "000001";
    string type           = "local";
    string description    = "Local Catalog";

    //int count; // This cause trouble with base function count();
    std::vector<int> added_songs_to_gather;
    std::vector<int> added_videos_to_gather;
public:
    CatalogLocal(const MAdminContextPtr &);
    void setupTable() override;
    json handleEvent(json event, unsigned long next, json args) override;
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
    string path;
        /**
         * get_description
         * This returns the description of this catalog
         */
        string get_description()
        {
            return description;
        } // get_description
        /**
         * get_version
         * This returns the current version
         */
        string get_version()
        {
            return version;
        } // get_version
        /**
         * get_type
         * This returns the current catalog type
         */
        string get_type()
        {
            return type;
        } // get_type
        /**
         * get_create_help
         * This returns hints on catalog creation
         */
        string get_create_help()
        {
            return "";
        } // get_create_help
        /**
         * is_installed
         * This returns true or false if local catalog is installed
         */
        bool is_installed()
        {
        } // is_installed
        /**
         * install
         * This function installs the local catalog
         */
        bool install()
        {
        } // install
        std::vector<string> catalog_fields();
        /**
         * get_from_path
         *
         * Try to figure out which catalog path most closely resembles this one.
         * This is useful when creating a new catalog to make sure we're not
         * doubling up here.
         */
        //bool function get_from_path(string path);
        /**
         * create_type
         *
         * This creates a new catalog type entry for a catalog
         * It checks to make sure its parameters is not already used before creating
         * the catalog.
         */
        //static bool function create_type(int catalog_id, std::vector<string> data);
        /**
         * add_files
         *
         * Recurses through path and pulls out all mp3s and returns the
         * full path in an array. Passes gather_type to determine if we need to
         * check id3 information against the db.
         */
        bool add_files(string path, std::vector<string> options);

        bool add_file(string full_file, std::vector<string> options);
        /**
         * add_to_catalog
         * this function adds new files to an
         * existing catalog
         */
        //void add_to_catalog(std::vector<string> options = null);
        /**
         * verify_catalog_proc
         * This function compares the DB's information with the ID3 tags
         */
        //std::vector<int> verify_catalog_proc();
        /**
         * _verify_chunk
         * This verifies a chunk of the catalog, done to save
         * memory
         */
private:
        //int _verify_chunk($media_type, $chunk, $chunk_size);
        /**
         * clean catalog procedure
         *
         * Removes local songs that no longer exist.
         */
public:
        int clean_catalog_proc();
        /**
         * _clean_chunk
         * This is the clean function, its broken into
         * said chunks to try to save a little memory
         */
private:
        //std::vector<int> _clean_chunk($media_type, $chunk, $chunk_size);
        /**
         * insert_local_song
         *
         * Insert a song that isn't already in the database.
         */
        //long insert_local_song($file, $options = array())
        /**
         * insert_local_video
         * This inserts a video file into the video file table the tag
         * information we can get is super sketchy so it's kind of a crap shoot
         * here
         */
public:
        //long insert_local_video($file, $options = array())
private:
        void sync_podcasts();
        /**
         * check_local_mp3
         * Checks the song to see if it's there already returns true if found, false if not
         */
public:
        //bool check_local_mp3($full_file, $gather_type="");
        //string get_rel_path($file_path);
        /**
         * format
         *
         * This makes the object human-readable.
         */
        //public function format()
        //public function prepare_media($media)
};
}
#endif // CATALOGLOCAL_H
