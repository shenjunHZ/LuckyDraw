#pragma once
#include <QtWidgets/QDialog>
#include <QtWidgets/QButtonGroup>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <random>

namespace Ui
{
    class LuckyDraw;
} // namespace Ui
namespace app
{
    class LuckyDraw : public QDialog
    {
        Q_OBJECT

    public:
        LuckyDraw(std::vector<std::string> awards,
            std::vector<std::string> punishments,
            QWidget *parent = Q_NULLPTR);

    private:
        void initWidget();
        void initConnect();
        void buttonStatus();

    protected:
        virtual bool eventFilter(QObject *obj, QEvent *event);
        virtual void moveEvent(QMoveEvent *event);
        virtual void keyPressEvent(QKeyEvent * event);

    private slots:
        void onStart();
        void onTimeout();
        void onBtnQuit();

    private:
        std::vector<std::string> m_awards;
        std::vector<std::string> m_punishments;
        std::default_random_engine randomEngine;

        std::unique_ptr<Ui::LuckyDraw> ui{nullptr};
        std::unique_ptr<QButtonGroup> buttonGroup{nullptr};
        QTimer* m_timer{nullptr};
        QPoint m_mousePos;
        bool m_bmousePressed;
    };
} // namespace app
