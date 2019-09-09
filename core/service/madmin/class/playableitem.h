#ifndef PLAYABLEITEM_H
#define PLAYABLEITEM_H
#include <string>
#include <vector>
using std::string;
using std::vector;
/**
 * playable_item Interface
 *
 * This defines how the playable item file classes should
 * work, this lists all required functions and the expected
 * input
 */
class PlayableItem {
 public:
  PlayableItem();
  ~PlayableItem() = default;
  /**
   * format
   *
   * Creates member variables for output
   */
  virtual void format(bool details = true) = 0;

  /**
   * get_fullname
   *
   * Get the item full name.
   */
  virtual string get_fullname() = 0;

  /**
   * get_parent
   *
   * Get parent. Return parent `object_type`, `object_id` ; null otherwise.
   */
  virtual long get_parent() = 0;

  /**
   * get_childrens
   *
   * Get direct childrens. Return an array of `object_type`, `object_id`
   * childrens.
   */
  virtual long get_childrens() = 0;

  /**
   * search_childrens
   *
   * Search for direct childrens. Return an array of `object_type`, `object_id`
   * childrens matching the criteria.
   */
  virtual vector<long> search_childrens(string name) = 0;

  /*
   * get_medias
   *
   * Get all medias from all childrens. Return an array of `object_type`,
   * `object_id` medias.
   */
  virtual vector<long> get_medias(string filter_type = "null") = 0;

  /**
   * get_catalogs
   *
   * Get all catalog ids related to this item.
   * @return int[]
   */
  virtual vector<int> get_catalogs() = 0;
};

#endif  // PLAYABLEITEM_H
