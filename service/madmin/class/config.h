#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "../../../../wscontroller/context/madmincontext.h"

#include "sql/query.h"

namespace music {
namespace service {
class Config {
 public:
  Config(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();
  /**
   *  @var array $_global
   */
  // static $_global = array();

  /**
   * get
   *
   * This returns a config value.
   * @param string $name
   */
  static void get(std::string name, int default_ = 0);

  /**
   * get_all
   *
   * This returns all of the current config variables as an array.
   * @return array
   */
  static void get_all();

  /**
   * set
   *
   * This sets config values.
   * @param string $name
   * @param boolean $clobber
   */
  static void set(std::string name, std::string value, bool clobber = false);

  /**
   * set_by_array
   *
   * This is the same as the set function except it takes an array as
   * input.
   * @param array $array
   * @param boolean $clobber
   */
  static void set_by_array(int array, bool clobber = false);

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
#endif  // CONFIG_H
