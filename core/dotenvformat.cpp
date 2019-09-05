#include "dotenvformat.h"

#include <QRegularExpression>
#include <QTextStream>

bool DotenvFormat::readEnvFile(QIODevice &device, QSettings::SettingsMap &map) {
  QTextStream in(&device);

  std::string line;

  QRegularExpression keyValueRegex(R"(^\s*([\w\.\-]+)\s*=\s*(.*)\s*$)");

  while (in.readLineInto(&line)) {
    QRegularExpressionMatch match = keyValueRegex.match(line);

    if (match.capturedLength() < 3) {
      continue;
    }

    std::string key = match.captured(1);
    std::string value = match.captured(2);

    map.insert(key, value);
  }

  return true;
}
