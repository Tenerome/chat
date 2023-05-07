import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import "qrc:/qml/global/"
import FluentUI 1.0

//TODEL
FluContentPage {
    id: page
    width: parent.width
    height: parent.height
    visible: true
    CusClient {
        id: cus_client
        onClose_by_Dialog: {
            window.close()
        }
        onRecvOneMessage: recv => {
                              if (recv !== "")
                              listmodel.append({
                                                   "detail": recv,
                                                   "position": 1
                                               })
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
                //                color: "#00FFFFFF"
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
                            color: "#4D10CCEE"
                            radius: 20
                            x: position < 1 ? listview.width
                                              - width : 0 //control the position of message ballon
                            Text {
                                id: label
                                width: label.text.length <= 10 ? label.text.length * 12 : 250
                                font.pixelSize: 20
                                anchors.centerIn: parent
                                //                                anchors.leftMargin: 10
                                wrapMode: Text.Wrap //多行文本 超过width就自动换行
                                text: detail
                            }
                        }
                    }
                    model: ListModel {
                        id: listmodel
                        ListElement {
                            detail: "==Your chat start here=="
                            position: 0
                        }
                    }
                }
            }
        }

        FluMultilineTextBox {
            id: multi_textbox
            Layout.preferredWidth: recarea.width
            Layout.preferredHeight: 150
        }
        RowLayout {
            FluFilledButton {
                id: send_btn
                text: "send"
                Component.onCompleted: {
                    //clear the init detail
                    listmodel.clear()
                }

                onClicked: {
                    if (multi_textbox.text !== "") {
                        listmodel.append({
                                             "detail": Qt.formatDateTime(
                                                           new Date(),
                                                           "MM.dd HH:mm:ss") + " You:\n"
                                                       + multi_textbox.text,
                                             "position": 0
                                         })
                        $Client.sendMessage(multi_textbox.text)
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
