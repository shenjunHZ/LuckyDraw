#include "localIniFile/IniFile.hpp"
#include <QtCore/QStringList>

#define INDEX(SEC,KEY) QString("%1/%2").arg(SEC).arg(KEY)

namespace app
{

    IniFile::IniFile(const QString &strIniFilePath)
    {
        m_settings = std::make_unique<QSettings>(strIniFilePath, QSettings::IniFormat);
        m_settings->setIniCodec("UTF-8");
    }

    IniFile::~IniFile(void)
    {

    }

    QVariant IniFile::ReadValue(const QString &strSecName, const QString &strKey)
    {
        int total = m_settings->value(INDEX(strSecName, "total")).toInt();
        QString strRet = "";
        for (int index = 1; index <= total; ++index)
        {
            if (!strRet.isEmpty())
            {
                strRet += ",";
            }
            QVariant ret = m_settings->value(INDEX(strSecName, index));
            strRet += ret.toString();
        }

        return QVariant(strRet);
    }

    void IniFile::WriteValue(const QString &strSecName, const QString &strKey, const QVariant& qvValue)
    {
        m_settings->setValue(INDEX(strSecName, strKey), qvValue);
        m_settings->sync();
    }
}