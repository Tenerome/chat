//==========system libs====
import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
//===========FlentUI===
import FluentUI 1.0
//============custom lib====
import "./qml/global"

Window {
    id: mainWin
    CusClient {
        id: cus_client
        onClose_by_Dialog: {
            window.close()
        }
        onRecvOneMessage: recv => {
                              if (recv !== "") {
                                  showInfo(recv)
                              }
                          }
    }
    Component.onCompleted: {
        var cuscli = CusClient
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
