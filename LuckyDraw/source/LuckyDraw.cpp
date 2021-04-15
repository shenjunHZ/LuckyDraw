#include <QtGui/QDesktopServices>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include "LuckyDraw.hpp"
#include "CommonControl.hpp"
#include "ui_LuckyDraw.h"

namespace
{
    constexpr int awardLocation = 0;
    constexpr int punishmentLocation = 1;
    constexpr int rollTime = 100;
}
namespace app
{
    LuckyDraw::LuckyDraw(std::vector<std::string> awards,
        std::vector<std::string> punishments, 
        QWidget *parent)
        : QDialog(parent, Qt::FramelessWindowHint)
        , m_awards{awards}
        , m_punishments{punishments}
    {
        ui.reset(new Ui::LuckyDraw());
        ui->setupUi(this);
        setAttribute(Qt::WA_DeleteOnClose, false);
        setAttribute(Qt::WA_TranslucentBackground, true);
        initWidget();
        initConnect();

        // move to middle
        QDesktopWidget* pDeskWidget = QApplication::desktop();
        int iScreen = pDeskWidget->primaryScreen(); // use primary screen for show
        QWidget* pPrimaryScreen = pDeskWidget->screen(iScreen);

        int iWidth = pPrimaryScreen->width();
        int iHeight = pPrimaryScreen->height();
        this->move((iWidth - width()) / 2, (iHeight - height()) / 2);
        QString oemAppname = "Lucky Draw";
        this->setWindowTitle(oemAppname);

        SET_MODULE_STYLE_BY_PATH("LuckyDraw");

        this->setModal(true);
        this->activateWindow();
        ui->ParserBg->setFocus();
    }

    void LuckyDraw::initWidget()
    {
        buttonGroup = std::make_unique<QButtonGroup>(ui->groupWidget);
        buttonGroup->addButton(ui->awardRadioBtn, awardLocation);
        buttonGroup->addButton(ui->punishmentRadioBtn, punishmentLocation);
        ui->awardRadioBtn->setChecked(true);
        ui->startBtn->setChecked(false);
        ui->msgLabel->setText(tr("Lucky Draw"));
        ui->resultLine->setEnabled(false);
        ui->ParserBg->installEventFilter(this);
        ui->ParserBg->setFocus();
    }

    void LuckyDraw::initConnect()
    {
        m_timer = new QTimer(this);
        connect(m_timer,        SIGNAL(timeout()), this, SLOT(onTimeout()));
        connect(ui->startBtn,   SIGNAL(clicked()), this, SLOT(onStart()));
        connect(ui->btnQuit,    SIGNAL(clicked()), this, SLOT(onBtnQuit()));
    }

    void LuckyDraw::buttonStatus()
    {
        if (ui->startBtn->isChecked())
        {
            ui->startBtn->setText(tr("Stop"));
           // ui->awardRadioBtn->setCheckable(false);
           // ui->punishmentRadioBtn->setCheckable(false);
        }
        else
        {
            ui->startBtn->setText(tr("Start"));
            ui->awardRadioBtn->setCheckable(true);
            ui->punishmentRadioBtn->setCheckable(true);
        }
    }

    void LuckyDraw::onStart()
    {
        buttonStatus();
        if (ui->startBtn->isChecked())
        {
            m_timer->start(rollTime);
        }
        else
        {
            m_timer->stop();
        }
    }

    void LuckyDraw::onTimeout()
    {
        if (ui->awardRadioBtn->isChecked())
        {
            if (m_awards.size() < 1)
            {
                return;
            }

            std::uniform_int_distribution<int> distribution{ 0, static_cast<int>(m_awards.size() - 1) };
            const int index = distribution(randomEngine);

            ui->resultLine->setText(tr(m_awards[index].c_str()));
        }
        else
        {
            if (m_punishments.size() < 1)
            {
                return;
            }

            std::uniform_int_distribution<int> distribution{ 0, static_cast<int>(m_punishments.size() - 1) };
            const int index = distribution(randomEngine);

            ui->resultLine->setText(tr(m_punishments[index].c_str()));
        }
    }

    void LuckyDraw::onBtnQuit()
    {
        this->accept();
    }

    bool LuckyDraw::eventFilter(QObject *obj, QEvent *event)
    {
        if (obj == ui->ParserBg)
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                if (mouseEvent->button() == Qt::LeftButton)
                {
                    m_mousePos = mouseEvent->globalPos();
                    m_bmousePressed = true;
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseMove)
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                if ((mouseEvent->buttons() & Qt::LeftButton) && m_bmousePressed)
                {
                    int xDis = mouseEvent->globalPos().x() - m_mousePos.x();
                    int yDis = mouseEvent->globalPos().y() - m_mousePos.y();
                    m_mousePos = mouseEvent->globalPos();
                    QPoint pos = mapToGlobal(QPoint(0, 0));
                    move(pos.x() + xDis, pos.y() + yDis);
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseButtonRelease)
            {
                if (m_bmousePressed)
                {
                    ui->ParserBg->setFocus();
                }
                m_bmousePressed = false;

                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                if (mouseEvent->button() == Qt::LeftButton)
                {
                    return true;
                }
            }
        }

        return QDialog::eventFilter(obj, event);
    }

    void LuckyDraw::moveEvent(QMoveEvent *event)
    {
        const int margin = 20;
        QPoint pt = event->pos();
        QRect rtWnd = QApplication::desktop()->availableGeometry(pt);
        if (pt.x() + this->width() <= margin)
        {
            pt = QPoint(-this->width() + margin, pt.y());
        }
        if (pt.x() > rtWnd.right() - margin)
        {
            pt = QPoint(rtWnd.right() - margin, pt.y());
        }
        if (pt.y() + this->height() <= margin)
        {
            pt = QPoint(pt.x(), -this->height() + margin);
        }
        if (pt.y() > rtWnd.bottom() - margin)
        {
            pt = QPoint(pt.x(), rtWnd.bottom() - margin);
        }
        move(pt);
    }

    void LuckyDraw::keyPressEvent(QKeyEvent * event)
    {
        if (Qt::Key_Space == event->key())
        {
            if (ui->startBtn->isChecked())
            {
                ui->startBtn->setChecked(false);
            }
            else
            {
                ui->startBtn->setChecked(true);
            }
            onStart();
        }
    }

} // namespace app
