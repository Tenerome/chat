import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import FluentUI 1.0
import "../global/Define.js" as Define

FluContentPage {
    id: page
    width: parent.width
    height: parent.height
    visible: true
    property var contact
    property var chat_model
    Component.onCompleted: {
        for (let key in Define.load_model) {
            if (key === "contact")
                contact = Define.load_model[key]
            else
                chat_model = Define.load_model[key]
        }
    }
    ColumnLayout {
        FluScrollablePage {
            id: textscroll
            width: page.width - 50
            height: page.height - 300
            Rectangle {
                id: recarea
                width: textscroll.width
                height: textscroll.height
                border.color: "#a3bfc2"
                radius: 10

                //message ballon
                ListView {
                    id: listview
                    width: parent.width
                    height: parent.height
                    add: Transition {
                        //add animation
                        NumberAnimation {
                            properties: "x,y"
                            from: 100
                            duration: 100
                        }
                    }
                    spacing: 30 //control the message ballon column spacing
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    delegate: Component {
                        Rectangle {
                            id: ballon
                            width: label.width + 50
                            height: label.height <= 120 ? 120 : label.height + 20
                            color: position < 1 ? "#4D10CCEE" : "#4D7B7D7D"
                            radius: 20
                            x: position < 1 ? listview.width
                                              - width : 0 //control the position of message ballon

                            Text {
                                id: label
                                width: label.text.length <= 10 ? label.text.length * 12 : 250
                                font.pixelSize: 20
                                anchors.centerIn: parent
                                //                                anchors.leftMargin: 10
                                wrapMode: Text.Wrap
                                text: detail
                            }
                        }
                    }
                    model: chat_model
                }
            }
        }

        FluMultilineTextBox {
            id: multi_textbox
            Layout.preferredWidth: recarea.width
            Layout.preferredHeight: 150
            Keys.enabled: true
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter - 1) {
                    send_btn.clicked()
                }
            }
        }
        RowLayout {
            FluFilledButton {
                id: send_btn
                text: "send"
                onClicked: {
                    if (multi_textbox.text !== "") {
                        chat_model.append({
                                              "detail": Qt.formatDateTime(
                                                            new Date(),
                                                            "MM.dd HH:mm:ss") + " You:\n"
                                                        + multi_textbox.text,
                                              "position": 0
                                          })

                        var send_json = '{"flag":"' + Define.SOCKET_MESSAGE + '","message_flag":"'
                                + Define.CLIENT_TEXT_MESSAGE + '","account":"'
                                + Define.account + '","contact":"' + contact
                                + '","message":"' + multi_textbox.text + '"}'
                        $Client.sendMessage(send_json)
                        multi_textbox.text = ""
                    }
                }
            }
            spacing: 50
            FluFilledButton {
                id: image_btn
                text: "image"
            }
        }
    }
}
