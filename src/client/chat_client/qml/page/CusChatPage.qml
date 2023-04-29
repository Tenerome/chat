import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import "qrc:/qml/global/"
import FluentUI 1.0

Page {
    id: page
    leftPadding: 10
    rightPadding: 0
    bottomPadding: 10
    ColumnLayout {
        FluScrollablePage {
            id: textscroll
            width: page.width
            height: page.height - 300

            //            height: 1000
            Rectangle {
                id: recarea
                width: textscroll.width - 30
                height: textscroll.height
                border.color: "#a3bfc2"

                radius: 10

                //message ballon
                ListView {
                    width: parent.width
                    height: parent.height
                    add: Transition {
                        //设置增加Item时的动画 from 100,100  to不设置 就是默认在ListView
                        NumberAnimation {
                            properties: "x,y"
                            from: 100
                            duration: 100
                        }
                    }
                    id: listview
                    spacing: 50 //control the message ballon column spacing
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    delegate: Component {
                        Rectangle {
                            width: parent.width
                            height: label.height
                            opacity: 0.8
                            border.color: "#00FFFFFF"
                            color: "#00FFFFFF"
                            radius: 10
                            BorderImage {
                                //聊天气泡
                                id: qipao
                                source: "qrc:/res/icon/msg_ballon.png"
                                width: label.width + 100
                                height: label.height <= 200 ? 200 : label.height + 200
                                //  width:20
                                border.left: 10
                                border.right: 10
                                border.top: 10
                                border.bottom: 10

                                //                                anchors.bottomMargin: 30
                                x: parent.width - width

                                Text {
                                    id: label
                                    width: label.text.length <= 10 ? label.text.length * 12 : 250
                                    font.pixelSize: 20
                                    anchors.centerIn: parent
                                    anchors.leftMargin: 10
                                    wrapMode: Text.Wrap //多行文本 超过width就自动换行
                                    text: detail
                                }
                            }
                        }
                    }
                    model: ListModel {
                        id: listmodel
                        ListElement {
                            detail: ""
                        }
                    }
                }
            }
        }

        FluMultilineTextBox {
            id: multi_textbox
            Layout.preferredWidth: recarea.width
            Layout.preferredHeight: 200
        }
        RowLayout {
            Text {
                id: inner
            }

            FluFilledButton {
                id: send_btn
                text: "send"
                onClicked: {
                    listmodel.append({
                                         "detail": "You:" + multi_textbox.text
                                     })
                    multi_textbox.text = ""
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
