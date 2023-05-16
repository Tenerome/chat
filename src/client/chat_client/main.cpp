#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/Socket/Socket.h"
#include "src/md5/useMD5.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    //events before engine load url
    //Client object
    Client the_Client;
    the_Client.connect("127.0.0.1",8888);
    engine.rootContext()->setContextProperty("$Client",&the_Client);
    useMD5 usemd5;
    engine.rootContext()->setContextProperty("$UseMD5",&usemd5);
    engine.load(url);
    return app.exec();
}
