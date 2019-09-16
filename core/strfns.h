#ifndef STRFNS_H
#define STRFNS_H

#include <algorithm>
#include <string>

static inline void ReplaceAll2(std::string &str, const std::string &from,
                               const std::string &to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos +=
        to.length();  // Handles case where 'to' is a substring of 'from'
  }
}

std::string read_all(std::ifstream &in);
#endif  // STRFNS_H
