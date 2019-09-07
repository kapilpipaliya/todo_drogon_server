#ifndef UI_H
#define UI_H
#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"
using MAdminContextPtr = std::shared_ptr<MAdminContext>;
#include <fmt/format.h>
#include "json.hpp"
#include "spdlogfix.h"
using nlohmann::json;

// A collection of methods related to the user interface
namespace madmin {
class UI : public BaseServiceAbs {
  MAdminContextPtr context;

 public:
  UI(MAdminContextPtr);
  void setupTable() override;
  json handleEvent(json event, unsigned long next, json args) override;

  json getMenuData();
  std::string getPageTitle();
  std::string getUserAccountType();
  json getUserTypeData();
  json getCatalogFilterData();

  // static classes_;
  // static ticker_;
  // static icon_cache_;
  /**
   * find_template
   *
   * Return the path to the template file wanted. The file can be overwriten
   * by the theme if it's not a php file, or if it is and if option
   * allow_php_themes is set to true.
   */
  // static void find_template($template);
  /**
   * access_denied
   *
   * Throw an error when they try to do something naughty.
   */
  // static void access_denied($error = 'Access Denied');
  /**
   * ajax_include
   *
   * Does some trickery with the output buffer to return the output of a
   * template.
   */
  // static void ajax_include($template);
  /**
   * check_iconv
   *
   * Checks to see whether iconv is available;
   */
  // static void check_iconv();
  /**
   * check_ticker
   *
   * Stupid little cutesie thing to ratelimit output of long-running
   * operations.
   */
  // static void check_ticker();
  /**
   * clean_utf8
   *
   * Removes characters that aren't valid in XML (which is a subset of valid
   * UTF-8, but close enough for our purposes.)
   * See http://www.w3.org/TR/2006/REC-xml-20060816/#charsets
   */
  // static void clean_utf8($string);
  /**
   * flip_class
   *
   * First initialised with an array of two class names. Subsequent calls
   * reverse the array then return the first element.
   */
  // static void flip_class($classes = null);
  /**
   * format_bytes
   *
   * Turns a size in bytes into the best human-readable value
   */
  // static void format_bytes($value, $precision = 2);
  /**
   * unformat_bytes
   *
   * Parses a human-readable size
   */
  // static void unformat_bytes($value);
  /**
   * get_icon
   *
   * Returns an <img> tag for the specified icon
   */
  // static void get_icon($name, $title = null, $id = null);
  /**
   * _find_icon
   *
   * Does the finding icon thing
   */
  // static void _find_icon($name);
  /**
   * show_header
   *
   * For now this just shows the header template
   */
  // static void show_header();
  /**
   * show_footer
   *
   * Shows the footer template and possibly profiling info.
   */
  // static void show_footer();
  /**
   * show_box_top
   *
   * This shows the top of the box.
   */
  // static void show_box_top($title = '', $class = '');
  /**
   * show_box_bottom
   *
   * This shows the bottom of the box
   */
  // static void show_box_bottom();
  // static void show_custom_style();
  /**
   * update_text
   *
   * Convenience function that, if the output is going to a browser,
   * blarfs JS to do a fancy update.  Otherwise it just outputs the text.
   */
  // static void update_text($field, $value);
  // static void get_logo_url();
  // static void is_grid_view($type);
};
}  // namespace madmin
#endif  // UI_H
