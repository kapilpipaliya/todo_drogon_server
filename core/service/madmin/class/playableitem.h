#ifndef PLAYABLEITEM_H
#define PLAYABLEITEM_H
#include <string>
#include <vector>

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
  virtual std::string get_fullname() = 0;

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
  virtual std::vector<long> search_childrens(std::string name) = 0;

  /*
   * get_medias
   *
   * Get all medias from all childrens. Return an array of `object_type`,
   * `object_id` medias.
   */
  virtual std::vector<long> get_medias(std::string filter_type = "null") = 0;

  /**
   * get_catalogs
   *
   * Get all catalog ids related to this item.
   * @return int[]
   */
  virtual std::vector<int> get_catalogs() = 0;
};

#endif  // PLAYABLEITEM_H
