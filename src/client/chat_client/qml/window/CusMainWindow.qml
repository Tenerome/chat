import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import FluentUI 1.0
import "qrc:/qml/global/"
import "../global/Define.js" as Define

FluWindow {
    //================signal and property===============
    signal contact_ready_S
    signal tap_contact_S(string contact)
    signal edit_contact_S(string contact)
    property var contact_map

    id: window
    title: "chat"
    width: 1200
    height: 900
    minimumWidth: 1200
    minimumHeight: 900
    maximumWidth: 1200
    maximumHeight: 900
    //close event
    closeDestory: false
    closeFunc: function (event) {
        close_app.open()
        event.accepted = false
    }
    //========================system tray,bar,dialog================
    FluContentDialog {
        id: close_app
        title: "Sure to Quit?"
        message: "All activity won't be retained"
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

    FluAppBar {
        id: appbar
        z: 9
        width: parent.width
    }

    SystemTrayIcon {
        id: system_tray
        visible: true
        //TODO icon
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
    //===========================client socket,parse socket===================
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
        var contact
        var message
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
            contact = recv_json["contact"]
            console.log(contact)
            Define.add_page_listmodel.append({
                                                 "contact": contact,
                                                 "flag": "0"
                                             })
            break
        case Define.CLIENT_ANSWER_YES:
            contact = recv_json["contact"]
            Define.add_page_listmodel.append({
                                                 "contact": contact,
                                                 "flag": "1"
                                             })
            break
        case Define.CLIENT_ANSWER_NO:
            contact = recv_json["contact"]
            Define.add_page_listmodel.append({
                                                 "contact": contact,
                                                 "flag": "2"
                                             })
            break
        case Define.CLIENT_CONTACT_LIST:
            Define.contact_json = recv_json
            contact_ready_S()
            break
        case Define.CLIENT_TEXT_MESSAGE:
            contact = recv_json["contact"]
            message = recv_json["message"]
            contact_map[contact].append({
                                            "detail": message,
                                            "position": 1
                                        })
            system_tray.showMessage(contact, message)
            break
        }
    }
    //==========================when start=======================
    Component.onCompleted: {
        //create add listmodel
        Define.add_page_listmodel = Qt.createQmlObject(
                    "import QtQuick 2.9;ListModel{ListElement{contact:'';flag:''}}",
                    window)
        Define.add_page_listmodel.clear()
        //select when start
        var send_json = '{"flag":"' + Define.SOCKET_SELECT_WHEN_START
                + '","account":"' + Define.account + '"}'
        $Client.sendMessage(send_json)
    }
    //==========================FluNavigationView==================
    FluNavigationView {
        id: nav_view
        title: Define.account + " online"
        anchors.fill: parent
        items: cus_side_menu_bar
        z: 11
        displayMode: FluNavigationView.Open
        //TODO icon
        logo: "qrc:/res/icon/msg_ballon.png"
        Component.onCompleted: {
            nav_view.setCurrentIndex(0)
        }
    }

    FluWindow {
        id: edit_window
        width: 520
        height: 55
        flags: edit_window | Qt.FramelessWindowHint
        color: "#BD29B6F7"
        RowLayout {
            spacing: 10
            Rectangle {
                border.color: "gray"
                radius: 10
                width: 350
                height: 45
                TextEdit {
                    id: new_nickname
                    anchors.fill: parent
                    Layout.preferredHeight: 45
                    Layout.preferredWidth: 350
                    verticalAlignment: TextEdit.AlignVCenter
                    leftPadding: 2
                    selectByMouse: true
                    cursorVisible: true
                    selectionColor: "#66B3FF"
                }
            }
            FluFilledButton {
                text: "edit"
                height: 50
            }
            FluFilledButton {
                text: "cancel"
                height: 50
                onClicked: {
                    edit_window.visible = false
                }
            }
        }
    }

    FluMenu {
        id: pop_menu
        FluMenuItem {
            text: "cancel"
        }
        FluMenuItem {
            text: "edit nickname"
            onClicked: {
                edit_window.visible = true
            }
        }
        FluMenuItem {
            text: "delete contact"
            onClicked: {

            }
        }
    }

    FluObject {
        id: cus_side_menu_bar
        FluPaneItem {
            title: "Add Contact"
            onTap: {
                nav_view.push("qrc:/qml/page/CusAddContactPage.qml")
            }
        }
        FluPaneItemExpander {
            id: inner_expander
            title: "Contact"
            Connections {
                property var parent
                property var idx
                target: window
                function onContact_ready_S() {
                    contact_map = Define.contact_json
                    for (let key in Define.contact_json) {
                        var newCompnt = Qt.createComponent(
                                    "qrc:/qml/global/cusFluPaneItem.qml")
                        if (newCompnt.status === Component.Ready) {
                            var newPane = newCompnt.createObject(inner_expander)
                        }
                        if (key !== "flag") {
                            //spawn FluPaneItem by contacts
                            newPane.temp_id = key
                            newPane.title = Define.contact_json[key]
                            inner_expander.children.push(newPane)
                            //fill contact_map
                            contact_map[key] = Qt.createQmlObject(
                                        "import QtQuick 2.5;ListModel{ListElement{detail:'';position:0}}",
                                        parent)
                            contact_map[key].clear()
                        }
                    }
                }
            }
            //tap contact
            Connections {
                property var parent
                property var idx
                target: window
                function onTap_contact_S(contact) {
                    Define.load_model = {
                        "contact": contact,
                        "Model": contact_map[contact]
                    }
                    nav_view.push("qrc:/qml/page/CusChatPage.qml")
                    pop_menu.close()
                }
            }
            //double click contact
            Connections {
                property var parent
                property var idx
                target: window
                function onEdit_contact_S(contact) {
                    pop_menu.popup()
                }
            }
        }
    }
}
