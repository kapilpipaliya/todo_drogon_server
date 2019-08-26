#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "../baseservice.h"
namespace madmin {
class Config : public BaseService
{
public:
    Config();
    void setupTable() override;
    /**
     *  @var array $_global
     */
    //static $_global = array();

    /**
     * get
     *
     * This returns a config value.
     * @param string $name
     */
    static void get(std::string name, int default_=0);

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
};
}
#endif // CONFIG_H
