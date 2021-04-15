#include "AppConfiguration.hpp"
#include "CommonControl.hpp"
#include <MessageNotify/MessageNotify.h>
#include <Tools/Dir.h>
#include <Tools/File.h>
#include <DSGuiGlobalData.h>
#include <QtGui/QIcon>
#include <QtGui/QFont>
#include <QtGui/QScreen>
#include <QtCore/QFile>
#include <QtCore/QTranslator>
#include <QtCore/QDir>

namespace
{
    void SetTranslator(const QString strPath)
    {
        if (strPath.isEmpty())
        {
            return;
        }
        QTranslator * pTrans = new QTranslator();
        if (pTrans->load(strPath))
        {
            QApplication::installTranslator(pTrans);
        }
        else
        {
            delete pTrans;
            pTrans = NULL;
        }
    }

    void SearchQmFile(const QString & strPath)
    {
        QDir dir(strPath);
        if (!dir.exists())
        {
            return;
        }
        dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
        dir.setSorting(QDir::DirsFirst);

        QFileInfoList list = dir.entryInfoList();
        if (list.size() < 1)
        {
            return;
        }
        int i = 0;
        do
        {
            QFileInfo fileInfo = list.at(i);
            QString tt = fileInfo.fileName();
            bool bisDir = fileInfo.isDir();
            if (bisDir)
            {
                SearchQmFile(fileInfo.filePath());
            }
            else
            {
                bool bQm = fileInfo.fileName().endsWith(".qm");
                SetTranslator(fileInfo.filePath());
            }
            i++;
        } while (i < list.size());
    }

}// namespace

namespace app
{
    AppConfiguration::AppConfiguration(QApplication& app)
        : app{app}
    {
        initApp();
    }

    void AppConfiguration::initApp()
    {
        // app set
        app.setWindowIcon(QIcon("./LuckyDraw.ico"));
        QString strAppName = "Lucky Draw ";
        QString strAppVer = "1.0";
        QString strWindowTitle = strAppName + strAppVer;
        app.setOrganizationName(strAppName);
        app.setApplicationName(strWindowTitle);

        // font set
        QScreen* screen = app.primaryScreen();
        qreal dpi = screen->logicalDotsPerInch() / 96;
        QFont chnFont("Microsoft YaHei");
        chnFont.setPixelSize(14 * dpi);
        app.setFont(chnFont);

        // style set
        setAppStyle();
        // international set
        setAppInternational();
        // notify set
        setAppNotify();
    }

    void AppConfiguration::setAppStyle()
    {
        // load style
        QString strStyle = "";
        QFile fpStyle(common::GetSkinPath("public", "style.qss"));
        if (fpStyle.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            strStyle = fpStyle.readAll();
            fpStyle.close();
        }
        QString strCSSFilePath = common::GetSkinPath("") + QString("/DSGUI/CSS/");
        QStringList strList;
        strList.push_back("*.CSS");
        QStringList strFileList = QDir(strCSSFilePath).entryList(strList, QDir::Files);
        qApp->setStyleSheet(strStyle + DSGUI::DSFile::ReadAll(strFileList, strCSSFilePath));
    }

    void AppConfiguration::setAppInternational()
    {
        SearchQmFile(DSGUI::DSDir::GetCurrentPath() + "/Language/Language_zh/");
    }

    void AppConfiguration::setAppNotify()
    {
        QString strNotifyQmPath = QCoreApplication::applicationDirPath().append("/Language/Language_zh/DSMessageNotify_zh.qm");
        QString strLang = "Chinese";
        DSGUI::DSMessageNotify::Instance().SetParam(QStringList() << strNotifyQmPath, QStringList() << DSGUI::GetSkinVersion(), strLang);
        DSGUI::DSMessageNotify::Instance().StartMessageProcess();
        DSGUI::DSMessageNotify::Instance().SetMessageNotifyTitle(QObject::tr("Notify"));
    }

} // namespace app