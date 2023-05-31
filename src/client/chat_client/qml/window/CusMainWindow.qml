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
    signal name_ready_S
    signal tap_contact_S(string contact)
    signal edit_contact_S(string contact)
    id: window
    title: lang.chat
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
        title: appInfo.lang.objectName === "En" ? "Sure to quit?" : "确定要退出吗？"
        message: appInfo.lang.objectName
                 === "En" ? "All activity won't be retained" : "所有的活动都不会被保留！"
        negativeText: lang.mini
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
                     | FluContentDialog.NeutralButton
        onPositiveClicked: {
            window.destoryWindow()
            FluApp.closeApp()
        }
        onNegativeClicked: {
            system_tray.showMessage(
                        appInfo.lang.objectName === "En" ? "Chat Notifications" : "聊通知：",
                        appInfo.lang.objectName
                        === "En" ? "Chat has been hide in the system tray" : "聊已经隐藏到系统托盘")
            window.hide()
        }
        positiveText: lang.confirm
        neutralText: lang.cancel
    }

    FluAppBar {
        id: appbar
        z: 9
        width: parent.width
    }

    SystemTrayIcon {
        id: system_tray
        visible: true
        icon.source: "qrc:/res/icon/w_menu.png"
        tooltip: Define.account
        menu: Menu {
            MenuItem {
                text: lang.quit
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
        var account
        var contact
        var message
        var message_flag
        switch (flag) {
        case Define.CLIENT_ACCOUNT_NOT_REGISTED:
            showError(lang.account_not_exist)
            break
        case Define.CLIENT_ACCOUNT_ONLINE:
            showSuccess(appInfo.lang.objectName === "En" ? "Send add request" : "已发送添加申请")
            break
        case Define.CLIENT_BUFFER_ADD_CONTACT:
            showSuccess(appInfo.lang.objectName === "En" ? "Send add request" : "已发送添加申请")
            break
        case Define.CLIENT_ADD_CONTACT_REQUEST:
            contact = recv_json["contact"]
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
        case Define.CLIENT_MESSAGE:
            account = recv_json["account"]
            contact = recv_json["contact"]
            message = recv_json["message"]
            message_flag = Number(recv_json["message_flag"])
            if (account === Define.account) {
                Define.contact_map[contact].append({
                                                       "detail": message,
                                                       "type": message_flag === Define.CLIENT_TEXT_MESSAGE ? 0 : 1,
                                                       "position": 0
                                                   })
                //                system_tray.showMessage(contact, message)
            } else {
                Define.contact_map[account].append({
                                                       "detail": message,
                                                       "type": message_flag === Define.CLIENT_TEXT_MESSAGE ? 0 : 1,
                                                       "position": 1
                                                   })
                //                system_tray.showMessage(account, message)
            }
            break
        case Define.SOCKET_GET_PROFILE:
            Define.uid = recv_json["uid"]
            Define.name = recv_json["name"]
            name_ready_S()
            break
        case Define.CLIENT_GROUP_MESSAGE:
            contact = recv_json["contact"]
            message = recv_json["message"]
            message_flag = Number(recv_json["message_flag"])
            if (contact === Define.account) {
                Define.chatroom_model.append({
                                                 "detail": message,
                                                 "position": 0,
                                                 "type": message_flag
                                                         === Define.CLIENT_TEXT_MESSAGE ? 0 : 1
                                             })
                //            system_tray.showMessage("chatroom:" + contact, message)
            } else {
                Define.chatroom_model.append({
                                                 "detail": message_flag === Define.CLIENT_TEXT_MESSAGE ? (contact + ":\n" + message) : message,
                                                 "position": 1,
                                                 "contacts": contact,
                                                 "type": message_flag
                                                         === Define.CLIENT_TEXT_MESSAGE ? 0 : 1
                                             })
                //            system_tray.showMessage("chatroom:" + contact, message)
            }

            break
        }
    }
    //==========================when start=======================
    Component.onCompleted: {
        showSuccess(appInfo.lang.objectName === "En" ? "log succeed" : "登陆成功")
        //create add listmodel
        Define.add_page_listmodel = Qt.createQmlObject(
                    "import QtQuick 2.9;ListModel{ListElement{contact:'';flag:''}}",
                    window)
        Define.add_page_listmodel.clear()
        //create chatroom model
        Define.chatroom_model = Qt.createQmlObject(
                    "import QtQuick 2.5;ListModel{ListElement{detail:'';position:0;type:0;contacts:''}}",
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
        anchors.fill: parent
        items: cus_side_menu_bar
        footerItems: footer
        z: 11
        displayMode: FluNavigationView.Open
        logo: FluTheme.darkMode
              === FluDarkMode.Dark ? "qrc:/res/icon/w_menu.png" : "qrc:/res/icon/b_menu.png"
        Component.onCompleted: {
            nav_view.setCurrentIndex(0)
        }
    }
    Connections {
        target: window
        function onName_ready_S() {
            nav_view.title = Define.name + lang.online
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
                color: FluTheme.darkMode === FluDarkMode.Dark ? "#454545" : "white"
                FluTooltip {
                    id: tool_tip
                }
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
                    color: FluTheme.darkMode === FluDarkMode.Dark ? "white" : "#454545"
                    focus: true
                    validator: RegExpValidator {
                        regExp: /([A-Za-z]{5,10})/
                    }
                    onTextChanged: {
                        tool_tip.show(lang.name_format, 2000)
                    }
                    onFocusChanged: {
                        if (!activeFocus) {
                            tool_tip.hide()
                        }
                    }
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
                text: lang.confirm
                height: 50
                onClicked: {
                    var send_json = '{"flag":"' + Define.SOCKET_EDIT_CONTACT
                            + '","edit_flag":"' + Define.CLIENT_EDIT_NICKNAME
                            + '","account":"' + Define.account + '","contact":"'
                            + Define.load_model["contact"] + '","nickname":"' + text_box.text + '"}'
                    if (text_box.text.length < 5) {
                        showError(lang.name_short)
                    } else {
                        $Client.sendMessage(send_json)
                        text_box.text = ""
                        edit_window.visible = false
                        showSuccess(appInfo.lang.objectName
                                    === "En" ? "Modify Succeed!" : "修改成功，请刷新")
                    }
                }
            }
            FluFilledButton {
                id: cancel_btn
                text: lang.cancel
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
        title: appInfo.lang.objectName === "En" ? "Sure to delete your friend?" : "确定删除该好友?"
        message: appInfo.lang.objectName === "En" ? "Please think over before operation" : "请慎重考虑"
        negativeText: lang.cancel
        positiveText: lang.confirm
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
        onPositiveClicked: {
            var send_json = '{"flag":"' + Define.SOCKET_EDIT_CONTACT + '","edit_flag":"'
                    + Define.CLIENT_DELETE_CONTACT + '","account":"' + Define.account
                    + '","contact":"' + Define.load_model["contact"] + '"}'
            $Client.sendMessage(send_json)
            del_contact.close()
            showSuccess(appInfo.lang.objectName === "En" ? "Delete Contact Succeed" : "删除成功
")
        }
        onNegativeClicked: {
            del_contact.close()
        }
    }
    FluContentDialog {
        id: clear_message_history
        title: appInfo.lang.objectName === "En" ? "Sure to clear all message history?" : "确定清空聊天记录?"
        message: appInfo.lang.objectName === "En" ? "Please think over before operation" : "请慎重考虑"
        negativeText: lang.cancel
        positiveText: lang.confirm
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
        onPositiveClicked: {
            var send_json = '{"flag":"' + Define.SOCKET_CLEAR_MESSAGE_HISTORY
                    + '","account":"' + Define.account + '"}'
            $Client.sendMessage(send_json)
            del_contact.close()
            showSuccess(lang.clear_message_history)
        }
        onNegativeClicked: {
            del_contact.close()
        }
    }
    FluMenu {
        id: pop_menu
        FluMenuItem {
            text: lang.cancel
        }
        FluMenuItem {
            text: lang.edit_nickname
            onClicked: {
                edit_window.visible = true
            }
        }
        //        FluMenuItem {
        //            text: lang.clear_history
        //            onClicked: {
        //                clear_message_history.open()
        //            }
        //        }
        FluMenuItem {
            text: "account number"
            onClicked: {
                account_number_window.visible = true
                account_number_label.text = Define.load_model["contact"]
            }
        }
        FluMenuItem {
            text: lang.delete_contact
            onClicked: {
                del_contact.open()
            }
        }
    }
    FluWindow {
        id: account_number_window
        width: 400
        height: 55
        flags: account_number_window | Qt.FramelessWindowHint
        color: "#BD29B6F7"
        RowLayout {
            spacing: 10
            Rectangle {
                property alias text: new_nickname.text
                //                border.color: "gray"
                radius: 10
                width: 300
                height: 45
                color: FluTheme.darkMode === FluDarkMode.Dark ? "#454545" : "white"
                TextInput {
                    id: account_number_label
                    anchors.fill: parent
                    verticalAlignment: TextEdit.AlignVCenter
                    leftPadding: 2
                    selectByMouse: true
                    selectionColor: "#66B3FF"
                    color: FluTheme.darkMode === FluDarkMode.Dark ? "white" : "#454545"
                    focus: true
                    readOnly: true
                    text: ""
                }
            }
            FluFilledButton {
                text: "Back"
                onClicked: {
                    account_number_window.visible = false
                }
            }
        }
    }

    FluObject {
        id: cus_side_menu_bar
        FluPaneItem {
            title: lang.profile
            cusIcon: Image {
                source: FluTheme.darkMode === FluDarkMode.Dark ? "qrc:/res/icon/w_profile.png" : "qrc:/res/icon/b_profile.png"
                width: 20
                height: 20
            }
            onTap: {
                nav_view.push("qrc:/qml/page/CusProfile.qml")
            }
        }
        FluPaneItem {
            title: lang.add_contact
            cusIcon: Image {
                source: FluTheme.darkMode
                        === FluDarkMode.Dark ? "qrc:/res/icon/w_add.png" : "qrc:/res/icon/b_add.png"
                width: 20
                height: 20
            }
            onTap: {
                nav_view.push("qrc:/qml/page/CusAddContactPage.qml")
            }
        }
        FluPaneItemExpander {
            id: inner_expander
            title: lang.contacts
            icon: FluentIcons.ContactSolid
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
                                newPane.title = "     " + Define.contact_json[key]
                                inner_expander.children.push(newPane)
                                //fill contact_map
                                Define.contact_map[key] = Qt.createQmlObject(
                                            "import QtQuick 2.5;ListModel{ListElement{detail:'';type:0;position:0}}",
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
            title: lang.chatroom
            cusIcon: Image {
                source: FluTheme.darkMode === FluDarkMode.Dark ? "qrc:/res/icon/w_chatroom.png" : "qrc:/res/icon/b_chatroom.png"
                width: 20
                height: 20
            }
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
            title: lang.settings
            cusIcon: Image {
                source: FluTheme.darkMode === FluDarkMode.Dark ? "qrc:/res/icon/w_setting.png" : "qrc:/res/icon/b_setting.png"
                width: 20
                height: 20
            }
            onTap: {
                nav_view.push("qrc:/qml/page/CusSetting.qml")
            }
        }
        FluPaneItem {
            title: lang.flush
            cusIcon: Image {
                source: FluTheme.darkMode === FluDarkMode.Dark ? "qrc:/res/icon/w_flush.png" : "qrc:/res/icon/b_flush.png"
                width: 20
                height: 20
            }
            onTap: {
                flush_dialog.open()
            }
        }
    }
    FluContentDialog {
        id: flush_dialog
        title: appInfo.lang.objectName === "En" ? "Sure to flush?" : "确定要刷新？"
        message: appInfo.lang.objectName
                 === "En" ? "Make sure you backup the message" : "确保消息记录已经备份！"
        negativeText: lang.cancel
        positiveText: lang.confirm
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
        onPositiveClicked: {
            inner_expander.children = []
            var send_json = '{"flag":"' + Define.SOCKET_SELECT_WHEN_START
                    + '","account":"' + Define.account + '"}'
            $Client.sendMessage(send_json)
        }
        onNegativeClicked: {
            flush_dialog.close()
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
