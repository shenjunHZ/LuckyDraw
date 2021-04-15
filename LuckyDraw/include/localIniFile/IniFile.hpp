#pragma once
#include <QtCore/QString>
#include <QtCore/QSettings>
#include <QtCore/QVariant>

namespace app
{
	class IniFile
	{
	public:
        IniFile(const QString &strIniFilePath);
		~IniFile(void);
		QVariant ReadValue(const QString &strSecName, const QString &strKey);
		void WriteValue(const QString &strSecName, const QString &strKey, const QVariant& qvValue);

	private:
        std::unique_ptr<QSettings> m_settings{nullptr};
	};

} // namespace app