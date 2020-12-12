#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <DMainWindow>
#include <DAboutDialog>
#include <DToolButton>
#include <DProgressBar>
#include <DPushButton>
#include <QSystemTrayIcon>
#include <QLayout>
#include "widget.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MainWindow(QString yTitle,
               QString yUrl,
               int nWidth,
               int nHeight,
               bool tray = false,
               bool nFullScreen = false,
               bool nFixSize = false,
               bool nHideButtons = false,
               DAboutDialog *dialog = nullptr,
               QWidget *parent = nullptr);
    ~MainWindow();
    void setIcon(QString yIconPath);
private:
    Widget *m_widget;
    DAboutDialog *m_dialog;
    QSystemTrayIcon *m_tray;
    DToolButton *btnBack;
    DToolButton *btnForward;
    DToolButton *btnRefresh;
    QMenu *m_menu;
    QAction *m_fullScreen;
    QAction *m_fixSize;
    QAction *m_hideButtons;
    QMenu *t_menu;
    QAction *t_show;
    QAction *t_exit;
    bool mtray, mFixSize;
    int m_width, m_height;
    void fullScreen();
    void fixSize();
    void hideButtons();
    void keyPressEvent(QKeyEvent *event);
    //void closeEvent(QCloseEvent *event);
private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

signals:
    void sigQuit();
};
#endif // MAINWINDOW_H
