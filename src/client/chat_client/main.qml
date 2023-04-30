//==========system libs====
import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
//===========FlentUI===
import FluentUI 1.0

//============custom lib====
Window {
    id: mainWin
    Component.onCompleted: {
        FluApp.init(mainWin)
        FluApp.routes = {
            "/login": "qrc:/qml/window/CusLoginWindow.qml",
            "/logup": "qrc:/qml/window/CusLogupWindow.qml",
            "/main": "qrc:/qml/window/CusMainWindow.qml"
        }
        FluApp.initialRoute = "/login"
        FluApp.run()
    }
}
