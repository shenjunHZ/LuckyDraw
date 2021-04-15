#pragma once
#include "LuckyDraw.hpp"
#include <QtCore/QSharedMemory>

namespace app
{
    class AppService : public QObject
    {
        Q_OBJECT

    public:
        AppService();
        ~AppService();

        bool isRunning();
        bool initInstance();
        void releaseShareMemory();

    private:
        void initData();

    private:
        std::unique_ptr<QSharedMemory> m_sharedMem{nullptr};
        std::unique_ptr<LuckyDraw> luckyDraw{ nullptr };
        std::vector<std::string> m_awards;
        std::vector<std::string> m_punishments;
    };
} // namespace app