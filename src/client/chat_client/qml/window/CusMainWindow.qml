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
    //close event
    closeDestory: false
    closeFunc: function (event) {
        close_app.open()
        event.accepted = false
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
    //appbar and system tray
    FluAppBar {
        id: appbar
        z: 9
        width: parent.width
    }
    //client socket
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
    signal contact_ready
    function parseJson(recv) {
        var recv_json = JSON.parse(recv)
        var flag = recv_json["flag"]
        var contact
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
            Define.contact_string = recv
            contact_ready()
            break
        }
    }

    property ListModel add_model: ListModel {
        ListElement {
            contact: ""
            flag: ""
        }
    }
    property ListModel chat_model: ListModel {
        ListElement {
            detail: ""
            position: 0
        }
    }

    //start
    Component.onCompleted: {
        //clear listmodel
        //        contact_list.clear()
        add_model.clear()
        chat_model.clear()
        //set listmodel
        Define.add_page_listmodel = add_model
        Define.chat_page_listmodel = chat_model
        //select when start
        var send_json = '{"flag":"' + Define.SOCKET_SELECT_WHEN_START
                + '","account":"' + Define.account + '"}'
        $Client.sendMessage(send_json)
    }
    //pack FluPaneItem as an Item
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
            FluPaneItem {
                id: guest
                title: "GST"
                onTap: {
                    nav_view.push("qrc:/qml/page/CusChatPage.qml")
                }
            }
            FluPaneItem {
                id: chaos
                title: "CHS"
                onTap: {
                    nav_view.push("qrc:/qml/page/CusChatPage.qml")
                }
            }
            Connections {
                property var parent
                property var idx
                target: window
                function onContact_ready() {
                    var con_json = JSON.parse(Define.contact_string)
                    for (let i in con_json) {
                        var newPane = Qt.createQmlObject(
                                    "import FluentUI 1.0; FluPaneItem{temp_id:'del';title:'del'}",
                                    inner_expander)
                        if (i !== "flag") {
                            newPane.temp_id = i
                            newPane.title = con_json[i]
                            inner_expander.children.push(newPane)
                        }
                    }
                }
            }
            Component.onCompleted: {

                //                for (let key in contact_json) {
                //                    var newPane = Qt.createQmlObject(
                //                                "import FluentUI 1.0; FluPaneItem{id:'';title:'';}",
                //                                inner_expander)
                //                    if (key !== "") {
                //                        newPane.id = key
                //                        newPane.title = contact_json[key]
                //                        inner_expander.children.push(newPane)
                //                    }
                //                }
            }
        }
        //                    FluPaneItem {
        //                        title: "Chat"
        //                //        icon: FluentIcons.Home
        //                //        cusIcon: Image {
        //                //            anchors.centerIn: parent
        //                //            //            source:
        //                //            sourceSize: Qt.size(30, 30)
        //                //            width: 18
        //                //            height: 18
        //                //        }
        //                onTap: {
        //                    console.log(contact_list)
        //                }
        //            }
        //        }
    }
    FluNavigationView {
        id: nav_view
        title: Define.account + " online"
        anchors.fill: parent
        items: cus_side_menu_bar
        z: 11
        displayMode: FluNavigationView.Open
        logo: "qrc:/res/icon/msg_ballon.png"
        Component.onCompleted: {
            nav_view.setCurrentIndex(0)
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
}
