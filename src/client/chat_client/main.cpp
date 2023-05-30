#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>
#include "src/Socket/Socket.h"
#include "src/md5/useMD5.h"
#include "src/info/AppInfo.h"
#include "src/info/lang/Lang.h"
#include "src/ftp/ftp.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext *context=engine.rootContext();
    //events before engine load url
    //Client object
    Client the_Client;
    the_Client.connect("127.0.0.1",8888);
    context->setContextProperty("$Client",&the_Client);
    //MD5
    useMD5 usemd5;
    context->setContextProperty("$UseMD5",&usemd5);
    //appinfo
    AppInfo* appInfo = new AppInfo();
    //lang
    Lang* lang = appInfo->lang();
    context->setContextProperty("lang",lang);
    QObject::connect(appInfo,&AppInfo::langChanged,&app,[context,appInfo]{
        context->setContextProperty("lang",appInfo->lang());
    });
    context->setContextProperty("appInfo",appInfo);
    //locale auto obtain
    QLocale locale;
    if(locale.language()==QLocale::English){
        appInfo->changeLang("En");
    }else{
        appInfo->changeLang("Zh");
    }
    //ftp
    FtpClient ftpclient;
    context->setContextProperty("$ftp",&ftpclient);
    //Pictures dir
    context->setContextProperty("$PicturesLocation",QStandardPaths::PicturesLocation);
    //engine load
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
