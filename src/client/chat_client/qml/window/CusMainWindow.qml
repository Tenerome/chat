import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import FluentUI 1.0
import "qrc:/qml/global/"
import "../global/Define.js" as Define

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
    closeFunc: function (event) {
        close_app.open()
        event.accepted = false
    }
    Timer {
        id: select_timer
        running: false
        interval: 3000
        repeat: false
        onTriggered: {
            console.log("delay 3s")
            var send_json = '{"flag":"' + Define.SOCKET_SELECT_WHEN_START
                    + '","account":"' + Define.account + '"}'
            $Client.sendMessage(send_json)
        }
    }
    Component.onCompleted: {
        select_timer.start()
    }
    FluAppBar {
        id: appbar
        z: 9
        width: parent.width
    }
    CusClient {
        id: cus_client
        onClose_by_Dialog: {
            window.close()
        }
        onRecvOneMessage: recv => {
                              if (recv !== "") {
                                  parseJson(recv)
                              }
                          }
    }
    function parseJson(recv) {
        var recv_json = JSON.parse(recv)
        var flag = recv_json["flag"]
        var contact = recv_json["contact"]
        switch (flag) {
        case Define.CLIENT_ACCOUNT_NOT_REGISTED:
            showError("This account does not exist")
            break
        case Define.CLIENT_ACCOUNT_ONLINE:
            showSuccess("Send add request")
            break
        case Define.CLIENT_BUFFER_ADD_CONTACT:
            showSuccess("Send add request")
            break
        case Define.CLIENT_ADD_CONTACT_REQUEST:
            console.log(contact)
            Define.add_page_listmodel.append({
                                                 "contact": contact,
                                                 "flag": "0"
                                             })
            break
        case Define.CLIENT_ANSWER_YES:
            Define.add_page_listmodel.append({
                                                 "contact": contact,
                                                 "flag": "1"
                                             })
            break
        case Define.CLIENT_ANSWER_NO:
            Define.add_page_listmodel.append({
                                                 "contact": contact,
                                                 "flag": "2"
                                             })
            break
        }
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
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
                     | FluContentDialog.NeutralButton
        onPositiveClicked: {
            window.destoryWindow()
            FluApp.closeApp()
        }
        onNegativeClicked: {
            system_tray.showMessage("Chat Notifications",
                                    "Chat has been hide in the system tray")
            window.hide()
        }
        positiveText: "Quit"
        neutralText: "Cancle"
    }
    CusSideMenuBar {
        id: cus_side_menu_bar
    }
    FluNavigationView {
        id: nav_view
        title: Define.account + " online"
        anchors.fill: parent
        items: cus_side_menu_bar
        z: 11
        displayMode: FluNavigationView.Open
        //MainEvent.displayMode
        //        logo: "qrc:/res/image/favicon.ico"
        Component.onCompleted: {
            cus_side_menu_bar.navigationView = nav_view //selected scrollpage
            nav_view.setCurrentIndex(0)
        }
    }
}
