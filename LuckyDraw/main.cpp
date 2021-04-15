/*
@tool    use for son play lucky draw
@author  sj
@data    2020-1-7
@version 1.0
*/
#include "AppService.hpp"
#include "AppConfiguration.hpp"
#include <Tools/Dir.h>
#include <GlobalDataCenter/GlobalDataCenter.h>
#include <MessageBox/MessageBox.h>
#include <QtWidgets/QApplication>
#include <QtCore/QDir>

namespace
{

} // namespace

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);
    // set current path for this application 
    QString strCurPath = QCoreApplication::applicationDirPath();
    QDir::setCurrent(strCurPath);
    DSGUI::DSDir::SetCurrentPath(strCurPath);

    // global common component
    Common::CGlobalDataCenter::GetInstance().SetCurrentDirPath_UTF8(strCurPath.toUtf8().data());
    Common::CGlobalDataCenter::GetInstance().SetCurrentDirPath(strCurPath.toLocal8Bit().data());

    app::AppConfiguration appConfig(app);
    app::AppService appService;
    if (appService.isRunning())
    {
        DSGUI::DSMessageBox::ShowInformation(NULL, QObject::tr("Notice"), QObject::tr("Application have running!"), DSGUI::DSMessageBox::Ok);
        return 0;
    }

    appService.initInstance();
    appService.releaseShareMemory();

    return 0;
}
