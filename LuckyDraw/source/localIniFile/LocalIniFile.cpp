#include "localIniFile/LocalIniFile.hpp"
#include "localIniFile/IniFile.hpp"
#include "Tools/Dir.h"

using namespace DSGUI;

namespace app
{
    QVariant LocalIniFile::ReadValue(const QString &strSecName, const QString &strKey, const QString& qstrFilename)
    {
        IniFile LocalIniFile(DSDir::GetCurrentPath() + QString("/") + qstrFilename);
        return LocalIniFile.ReadValue(strSecName, strKey);
    }

    void LocalIniFile::WriteValue(const QString &strSecName, const QString &strKey, QVariant qvValue, const QString& qstrFilename)
    {
        IniFile LocalIniFile(DSDir::GetCurrentPath() + QString("/") + qstrFilename);
        LocalIniFile.WriteValue(strSecName, strKey, qvValue);
    }

}