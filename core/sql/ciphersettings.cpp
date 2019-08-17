#include "ciphersettings.h"

CipherSettings::CipherSettings()
    : keyFormat(Passphrase),
      pageSize(0),
      kdfIterations(0)
{
}

CipherSettings::KeyFormats CipherSettings::getKeyFormat() const
{
    return keyFormat;
}

void CipherSettings::setKeyFormat(const KeyFormats &value)
{
    keyFormat = value;
}

std::string CipherSettings::getPassword() const
{
    if(keyFormat == Passphrase)
    {
        std::string tempPassword = password;

        tempPassword.replace("'", "''");

        return std::string("'%1'").arg(tempPassword);
    } else {
        // Remove the '0x' part at the beginning
        return std::string("\"x'%1'\"").arg(password.mid(2));
    }
}

void CipherSettings::setPassword(const std::string &value)
{
    password = value;
}

int CipherSettings::getPageSize() const
{
    return pageSize;
}

void CipherSettings::setPageSize(int value)
{
    pageSize = value;
}

CipherSettings::KeyFormats CipherSettings::getKeyFormat(int rawKeyFormat)
{
    return static_cast<CipherSettings::KeyFormats>(rawKeyFormat);
}
