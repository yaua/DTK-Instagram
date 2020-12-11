#include "mainwindow.h"
#include <DMainWindow>
#include <DWidgetUtil>
#include <DTitlebar>
#include <DMessageManager>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>
#include <QCloseEvent>
#include <QDebug>
#include "webenginepage.h"

MainWindow::MainWindow(QString yTitle,
                       QString yUrl,
                       int nWidth,
                       int nHeight,
                       bool tray,
                       bool nHideButtons,
                       DAboutDialog *dialog,
                       QWidget *parent)
    : DMainWindow(parent)
    , m_widget(new Widget(yUrl))
    , m_dialog(dialog)
    , m_tray(new QSystemTrayIcon)
    , btnBack(new DToolButton(titlebar()))
    , btnForward(new DToolButton(titlebar()))
    , btnRefresh(new DToolButton(titlebar()))
    , m_menu(new QMenu)
    , m_fullScreen(new QAction(tr("Full Screen")))
    , m_fixSize(new QAction(tr("Fix Size")))
    , m_hideButtons(new QAction(tr("Hide Buttons")))
    , t_menu(new QMenu)
    , t_show(new QAction(tr("Open Instagram")))
    , t_exit(new QAction(tr("Exit")))
    , mtray(tray)
    , m_width(nWidth)
    , m_height(nHeight)
{
    setCentralWidget(m_widget);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    resize(m_width, m_height);
    moveToCenter(this);
    setWindowIcon(QIcon(":/images/instagram.svg"));
    titlebar()->setTitle(yTitle);
    titlebar()->setIcon(QIcon(":/images/instagram.svg"));
    btnBack->setIcon(QIcon(":/images/go-previous-24.svg"));
    btnBack->setIconSize(QSize(20, 20));
    btnForward->setIcon(QIcon(":/images/go-next-24.svg"));
    btnForward->setIconSize(QSize(20, 20));
    btnRefresh->setIcon(QIcon(":/images/view-refresh.svg"));
    btnRefresh->setIconSize(QSize(20, 20));
    titlebar()->addWidget(btnBack, Qt::AlignLeft);
    titlebar()->addWidget(btnForward, Qt::AlignLeft);
    titlebar()->addWidget(btnRefresh, Qt::AlignLeft);
    m_fullScreen->setCheckable(true);
    m_fixSize->setCheckable(true);
    m_hideButtons->setCheckable(true);
    m_hideButtons->setChecked(nHideButtons);
    m_hideButtons->setDisabled(nHideButtons);
    if(!nHideButtons)
    {
        m_menu->addAction(m_hideButtons);
    }
    titlebar()->setMenu(m_menu);
    titlebar()->setAutoHideOnFullscreen(true);
    hideButtons();
    /* TrayIcon */
    t_menu->addAction(t_show);
    t_menu->addAction(t_exit);
    m_tray->setContextMenu(t_menu);
    m_tray->setToolTip(yTitle);
    m_tray->setIcon(QIcon(":/images/instagram.svg"));
    if(tray)
    {
        m_tray->show(); // Show when tray is enabled
    }
    connect(btnBack, &DToolButton::clicked, this, [&]()
    {
        m_widget->goBack();
    });
    connect(btnForward, &DToolButton::clicked, this, [&]()
    {
        m_widget->goForward();
    });
    connect(btnRefresh, &DToolButton::clicked, this, [&]()
    {
        m_widget->refresh();
    });
    connect(m_hideButtons, &QAction::triggered, this, [=]()
    {
        hideButtons();
    });
    connect(t_exit, &QAction::triggered, this, [=]()
    {
        exit(0);
    });
    connect(m_tray, &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);
}
MainWindow::~MainWindow()
{
    emit sigQuit();
    delete m_widget;
    delete m_dialog;
    delete m_tray;
}

void MainWindow::setIcon(QString yIconPath)
{
    QFileInfo fi(yIconPath);
    if (fi.exists())
    {
        titlebar()->setIcon(QIcon(yIconPath));
        setWindowIcon(QIcon(yIconPath));
        m_tray->setIcon(QIcon(yIconPath));
        qDebug() << yIconPath << "is Set!";
    }
    else
    {
        qDebug() << yIconPath << "is Not Exists!";
    }
}
void MainWindow::hideButtons()
{
    if(m_hideButtons->isChecked())
    {
        btnBack->hide();
        btnForward->hide();
        btnRefresh->hide();
    }
    else
    {
        btnBack->show();
        btnForward->show();
        btnRefresh->show();
    }
}
void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {   case QSystemTrayIcon::Trigger:
            this->activateWindow();
            break;
        default:
            break;
    }
}
