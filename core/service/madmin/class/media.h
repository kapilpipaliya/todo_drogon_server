#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <vector>
using std::string;
using std::vector;
#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
/**
 * media Interface
 *
 * This defines how the media file classes should
 * work, this lists all required functions and the expected
 * input
 */
class Media : public BaseServiceAbs {
 public:
  Media(MAdminContextPtr);
  void setupTable() override;
  /**
   * get_stream_types
   *
   * Returns an array of strings; current types are 'native'
   * and 'transcode'
   */
  virtual vector<string> get_stream_types(string player = "null") = 0;
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
  virtual void set_played(string user, string agent, string location) = 0;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // MEDIA_H
