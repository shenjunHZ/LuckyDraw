#include "AppService.hpp"
#include "localIniFile/LocalIniFile.hpp"

namespace app
{
    AppService::AppService() 
    {
        initData();
    }

    AppService::~AppService()
    {

    }

    void AppService::initData()
    {
        m_sharedMem = std::make_unique<QSharedMemory>("Lucky Draw Application");

        std::unique_ptr<LocalIniFile> pLocalIniFile = std::make_unique<LocalIniFile>();
        QVariant var = pLocalIniFile->ReadValue("Awards", "award", "Localcfg.ini");
        QString value = var.toString();
        QStringList awards = value.split(",");
        for (int index = 0; index < awards.size(); ++index)
        {
            QString award = awards.at(index);
            m_awards.push_back(award.toStdString());
        }

        var = pLocalIniFile->ReadValue("Punishments", "punishment", "Localcfg.ini");
        value = var.toString();
        QStringList punishments = value.split(",");
        for (int index = 0; index < punishments.size(); ++index)
        {
            QString punishment = punishments.at(index);
            m_punishments.push_back(punishment.toStdString());
        }
    }

    void AppService::releaseShareMemory()
    {
        if (m_sharedMem && m_sharedMem->isAttached())
        {
            m_sharedMem->detach();
        }

    }

    bool AppService::isRunning()
    {
        volatile int i = 2;
        while (i--)
        {
            if (m_sharedMem->attach(QSharedMemory::ReadOnly))
            {
                m_sharedMem->detach();
            }
        }

        if (!m_sharedMem->create(1))
        {
            return true;
        }
        return false;
    }

    bool AppService::initInstance()
    {
        if (nullptr == luckyDraw)
        {
            luckyDraw = std::make_unique<LuckyDraw>(m_awards, m_punishments);
        }

        luckyDraw->exec();
        return true;
    }
}