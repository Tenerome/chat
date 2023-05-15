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
    id: window
    title: "chat"
    width: 1200
    height: 900
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
            Define.contact_map[contact].append({
                                                   "detail": "====" + contact + "====\n" + message,
                                                   "position": 1
                                               })
            system_tray.showMessage(contact, message)
            break
        case Define.SOCKET_GET_PROFILE:
            Define.uid = recv_json["uid"]
            Define.name = recv_json["name"]
            break
        case Define.CLIENT_GROUP_MESSAGE:
            contact = recv_json["contact"]
            message = recv_json["message"]
            Define.chatroom_model.append({
                                             "detail": "====" + contact + "====\n" + message,
                                             "position": contact === Define.account ? 0 : 1
                                         })
            //            system_tray.showMessage("chatroom:" + contact, message)
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
        //create chatroom model
        Define.chatroom_model = Qt.createQmlObject(
                    "import QtQuick 2.5;ListModel{ListElement{detail:'';position:0}}",
                    window)
        Define.chatroom_model.clear()
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
        footerItems: footer
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
                id: text_box
                property alias text: new_nickname.text
                border.color: "gray"
                radius: 10
                width: 350
                height: 45
                color: FluTheme.darkMode === FluDarkMode.Dark ? "black" : "white"
                TextInput {
                    id: new_nickname
                    anchors.fill: parent
                    Layout.preferredHeight: 45
                    Layout.preferredWidth: 350
                    verticalAlignment: TextEdit.AlignVCenter
                    leftPadding: 2
                    selectByMouse: true
                    cursorVisible: true
                    selectionColor: "#66B3FF"
                    color: FluTheme.darkMode === FluDarkMode.Dark ? "white" : "black"
                    focus: true
                    Keys.enabled: true
                    Keys.onPressed: {
                        if (event.key === Qt.Key_Enter - 1) {
                            confirm_btn.clicked()
                        }
                        if (event.key === Qt.Key_Escape) {
                            cancel_btn.clicked()
                        }
                    }
                }
            }
            FluFilledButton {
                id: confirm_btn
                text: "confirm"
                height: 50
                onClicked: {
                    var send_json = '{"flag":"' + Define.SOCKET_EDIT_CONTACT
                            + '","edit_flag":"' + Define.CLIENT_EDIT_NICKNAME
                            + '","account":"' + Define.account + '","contact":"'
                            + Define.load_model["contact"] + '","nickname":"' + text_box.text + '"}'
                    $Client.sendMessage(send_json)
                    text_box.text = ""
                    edit_window.visible = false
                    showSuccess("Modify Succeed!")
                }
            }
            FluFilledButton {
                id: cancel_btn
                text: "cancel"
                height: 50
                onClicked: {
                    text_box.text = ""
                    edit_window.visible = false
                }
            }
        }
    }

    FluContentDialog {
        id: del_contact
        title: "Sure to delete your friend?"
        message: "Please think over before operation"
        negativeText: "Cancel"
        positiveText: "Confirm"
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
        onPositiveClicked: {
            var send_json = '{"flag":"' + Define.SOCKET_EDIT_CONTACT + '","edit_flag":"'
                    + Define.CLIENT_DELETE_CONTACT + '","account":"' + Define.account
                    + '","contact":"' + Define.load_model["contact"] + '"}'
            $Client.sendMessage(send_json)
            del_contact.close()
            showSuccess("Delete Contact Succeed")
        }
        onNegativeClicked: {
            del_contact.close()
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
                del_contact.open()
            }
        }
    }

    FluObject {
        id: cus_side_menu_bar
        FluPaneItem {
            title: "Profile"
            onTap: {
                nav_view.push("qrc:/qml/page/CusProfile.qml")
            }
        }
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
                    //format contact_map
                    Define.contact_map = Define.contact_json
                    //spawn flupaneitem
                    for (let key in Define.contact_json) {
                        var newCompnt = Qt.createComponent(
                                    "qrc:/qml/global/cusFluPaneItem.qml")
                        if (newCompnt.status === Component.Ready) {
                            var newPane = newCompnt.createObject(inner_expander)
                            if (key !== "flag") {
                                //spawn FluPaneItem by contacts
                                newPane.temp_id = key
                                newPane.title = Define.contact_json[key]
                                inner_expander.children.push(newPane)
                                //fill contact_map
                                Define.contact_map[key] = Qt.createQmlObject(
                                            "import QtQuick 2.5;ListModel{ListElement{detail:'';position:0}}",
                                            parent)
                                Define.contact_map[key].clear()
                            }
                        }
                    }
                }
            }
            //tap contact
            Connections {
                property var parent
                property var idx
                target: window
                function onTap_contact_S(temp_id) {
                    Define.load_model = {
                        "contact": temp_id,
                        "Model": Define.contact_map[temp_id]
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
        FluPaneItem {
            temp_id: "$chatroom"
            title: "Chat Room"
            onTap: {
                Define.load_model = {
                    "contact": temp_id,
                    "Model": Define.chatroom_model
                }
                nav_view.push("qrc:/qml/page/CusChatPage.qml")
            }
        }
    }
    FluObject {
        id: footer
        FluPaneItemSeparator {}
        FluPaneItem {
            title: "Settings"
            onTap: {
                nav_view.push("qrc:/qml/page/CusSetting.qml")
            }
        }
        FluPaneItem {
            title: "Flush"
            onTap: {
                window.closeDestory = true
                window.closeFunc = function (event) {
                    event.accepted = true
                }
                window.destoryWindow()
                FluApp.navigate("/main")
            }
        }
    }
    //flush progress ring
    FluProgressRing {
        //progress ring
        id: progress_ring
        z: 999
        anchors.centerIn: parent
        Layout.alignment: Qt.AlignHCenter
        Timer {
            interval: 1000
            repeat: false
            running: true
            onTriggered: {
                progress_ring.destroy()
            }
        }
    }
}
