#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

/**
 * library_item Interface
 *
 * This defines how the media file classes should
 * work, this lists all required functions and the expected
 * input
 */
// interface library_item extends playable_item
class LibraryItem {
 public:
  LibraryItem();
  virtual ~LibraryItem() = default;

  //  virtual void get_keywords() = 0;
  //  virtual void get_user_owner() = 0;
  //  virtual void get_default_art_kind() = 0;
  //  virtual void get_description() = 0;
  //  virtual void display_art($thumb, bool force = false) = 0;
  //  virtual void update(array $data) = 0;
  //  public static function gc() = 0;
};

#endif  // LIBRARYITEM_H
