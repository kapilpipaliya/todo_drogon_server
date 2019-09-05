#include "strfns.h"
#include <fstream>
/*
QString rtrimChar(const QString& s, QChar c)
{
    QString r = s.trimmed();
    while(r.endsWith(c))
        r.chop(1);
    return r;
}
*/
std::string rtrimChar(const std::string& s, char c) {
  auto r = trim_copy(s);
  if (r.at(r.size() - 1) == c) {
    r.pop_back();
  }
  return s;
}

// cool function:
// https://wandbox.org/permlink/ESIFJiztM76Q8KvP
// https://wandbox.org/permlink/33rgXrc1TGmNeYya
std::string read_all(std::ifstream& in) {
  in.seekg(0, std::ios::beg);
  return {std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
}
