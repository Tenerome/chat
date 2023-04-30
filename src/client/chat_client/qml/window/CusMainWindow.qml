import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import FluentUI 1.0
import "qrc:/qml/global/"

FluWindow {
    id: window
    title: "chat"
    width: 1200
    height: 900
    minimumWidth: 1200
    minimumHeight: 900
    maximumWidth: 1200
    maximumHeight: 900
    closeDestory: false
    //    CusClient {
    //        id: cus_client
    //        onClose_by_Dialog: {
    //            window.close()
    //        }
    //    }
    closeFunc: function (event) {
        close_app.open()
        event.accepted = false
    }
    FluAppBar {
        id: appbar
        z: 9
        width: parent.width
    }

    SystemTrayIcon {
        id: system_tray
        visible: true
        //        icon.source: "qrc:/res/image/favicon.ico"
        tooltip: "chat"
        menu: Menu {
            MenuItem {
                text: "Quit"
                onTriggered: {
                    window.destoryWindow()
                    FluApp.closeApp()
                }
            }
        }
        onActivated: {
            window.show()
            window.raise()
            window.requestActivate()
        }
    }

    FluContentDialog {
        id: close_app
        title: "Sure to Quit"
        message: "All activity won't be retained?"
        negativeText: "Minimize"
        buttonFlags: FluContentDialog.NeutralButton | FluContentDialog.NegativeButton
                     | FluContentDialog.PositiveButton
        onNegativeClicked: {
            system_tray.showMessage("Chat Notifications",
                                    "Chat has been hide in the system tray")
            window.hide()
        }
        positiveText: "Quit"
        neutralText: "Cancle"
        onPositiveClicked: {
            window.destoryWindow()
            FluApp.closeApp()
        }
    }
    CusSideMenuBar {
        id: cus_side_menu_bar
    }
    FluNavigationView {
        id: nav_view
        title: "Chat"
        anchors.fill: parent
        items: cus_side_menu_bar
        z: 11
        displayMode: FluNavigationView.Auto //MainEvent.displayMode
        //        logo: "qrc:/res/image/favicon.ico"
        Component.onCompleted: {
            cus_side_menu_bar.navigationView = nav_view //selected scrollpage
            nav_view.setCurrentIndex(0)
        }
    }
}
