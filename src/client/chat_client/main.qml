import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import FluentUI 1.0

Window {
    id: mainWin
    Component.onCompleted: {
        FluApp.init(mainWin)
        FluApp.routes = {
            "/test": "qrc:/test.qml",
            "/login": "qrc:/qml/window/CusLoginWindow.qml",
            "/logup": "qrc:/qml/window/CusLogupWindow.qml",
            "/main": "qrc:/qml/window/CusMainWindow.qml"
        }
        FluApp.initialRoute = "/login"
        FluApp.run()
    }
}
