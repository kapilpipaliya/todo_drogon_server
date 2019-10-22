#include "strfns.h"
#include <fstream>

// cool function:
// https://wandbox.org/permlink/ESIFJiztM76Q8KvP
// https://wandbox.org/permlink/33rgXrc1TGmNeYya
std::string read_all(std::ifstream& in) {
  in.seekg(0, std::ios::beg);
  return {std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
}
