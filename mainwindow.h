#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <DMainWindow>
#include <DAboutDialog>
#include <DToolButton>
#include <DProgressBar>
#include <DPushButton>
#include <DFloatingMessage>
#include <QSystemTrayIcon>
#include <QLayout>
#include <QProcess>
#include <QMutex>
#include "widget.h"
#include "main.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MainWindow(QString yTitle = DEFAULT_TITLE,
               QString yUrl = DEFAULT_URL,
               int nWidth = DEFAULT_WIDTH,
               int nHeight = DEFAULT_HEIGHT,
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
    QWidget *downloadProgressBar;
    DProgressBar *bar;
    DPushButton *pause;
    DPushButton *resume;
    DPushButton *cancel;
    QHBoxLayout *progress;
    DFloatingMessage *message;
    QProcess *process;
    QMutex mutex;       // not allowed to download multiple files
    bool isCanceled;    // Determine whether to cancel the download
    bool mtray, mFixSize;
    int m_width, m_height;
    void fullScreen();
    void fixSize();
    void hideButtons();
    QString saveAs(QString fileName);
    void keyPressEvent(QKeyEvent *event);
   // void closeEvent(QCloseEvent *event);
private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_downloadStart(QWebEngineDownloadItem *item);
    void on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void on_downloadFinish(QString filePath);
    void on_downloadPause(QWebEngineDownloadItem *item);
    void on_downloadResume(QWebEngineDownloadItem *item);
    void on_downloadCancel(QWebEngineDownloadItem *item);
signals:
    void sigQuit();
};
#endif // MAINWINDOW_H
