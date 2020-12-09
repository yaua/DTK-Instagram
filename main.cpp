#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>
#include <DAboutDialog>
#include <DMainWindow>
#include <QTranslator>
#include <QFileInfo>
#include <QSettings>
#include "main.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    DAboutDialog *dialog = new DAboutDialog;
    a.setAboutDialog(dialog);
    dialog->setProductIcon(QIcon(":/images/logo.svg"));
    QString yDefaultDesc = QString("<span style=' font-size:8pt; font-weight:600;'>This is the simple app with dtk lib and WebApp Runtime. Customize by yaua</span>");
    dialog->setDescription(yDefaultDesc);
    dialog->setVersion(DApplication::buildVersion(QString("%1 %2").arg(QObject::tr("Version")).arg("1.1")));
    dialog->setLicense(QObject::tr("This program is open source under GPLv3"));

    QString yTitle = DEFAULT_TITLE;
    QString yUrl = DEFAULT_URL;
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    bool tray = true;
    bool fullScreen = false;
    bool fixSize = false;
    bool hideButtons = false;
    QString yIcon = DEFAULT_ICON;
    QString yDesc = DEFAULT_DESC;
    if(fixSize)
    {
        fullScreen = false;
    }
    a.setQuitOnLastWindowClosed(!tray);
    MainWindow w(yTitle, yUrl, width, height, tray, fullScreen, fixSize, hideButtons);
    if (!yIcon.isEmpty())
    {
        dialog->setWindowIcon(QIcon(yIcon));
        dialog->setProductIcon(QIcon(yIcon));
        w.setIcon(yIcon);
    }
    if (!yDesc.isEmpty())
    {
        dialog->setDescription(yDesc);
    }
    w.show();
    return a.exec();
}
