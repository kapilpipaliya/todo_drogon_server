#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <vector>

#include "../../../../wscontroller/context/madmincontext.h"

#include "sql/query.h"

namespace music {
namespace service {
/**
 * media Interface
 *
 * This defines how the media file classes should
 * work, this lists all required functions and the expected
 * input
 */
class Media {
 public:
  Media(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  virtual ~Media() = default;
  void setupTable();
  /**
   * get_stream_types
   *
   * Returns an array of strings; current types are 'native'
   * and 'transcode'
   */
  virtual std::vector<std::string> get_stream_types(
      std::string player = "null") = 0;
  /**
   * play_url
   *
   * Returns the url to stream the specified object
   *
   */
  // virtual static function play_url($oid, $additional_params='', $player=null,
  // $local=false) = 0;
  /**
   * get_transcode_settings
   *
   * Should only be called if 'transcode' was returned by get_stream_types
   * Returns a raw transcode command for this item; the optional target
   * parameter can be used to request a specific format instead of the
   * default from the configuration file.
   */
  // virtual void get_transcode_settings($target = null, $player = null,
  // $options=array()) = 0;
  /**
   * get_stream_name
   * Get the complete name to display for the stream.
   */
  virtual void get_stream_name() = 0;
  virtual void set_played(std::string user, std::string agent,
                          std::string location) = 0;

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
#endif  // MEDIA_H
