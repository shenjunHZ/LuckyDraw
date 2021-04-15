#pragma once
#include <QtWidgets/QApplication>

namespace app
{
    class AppConfiguration
    {
    public:
        AppConfiguration(QApplication& app);

    private:
        void initApp();
        void setAppStyle();
        void setAppInternational();
        void setAppNotify();

    private:
        QApplication& app;
    };
} // namespace app