import QtQuick 2.9
import FluentUI 1.0
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Page {
    width: 500
    height: 500
    id: page
    ColumnLayout {

        ListView {
            id: listview
            anchors.top: page.top
            anchors.bottom: bottomrect.top
            anchors.left: page.left
            anchors.right: page.right
            //anchors的对象要么是兄弟结点（提供id）
            //要么就是子节点（parent）
            delegate: Component {
                //这里delegate:后面必须是Component
                Rectangle {
                    width: 550
                    height: label1.height + 20
                    opacity: 0.8
                    // color:"black"
                    BorderImage {
                        //聊天气泡
                        id: qipao
                        //                            source: "pao.png"
                        width: label1.width + 30
                        height: label1.height <= 30 ? 30 : label1.height + 5
                        //  width:20
                        border.left: 10
                        border.right: 10
                        border.top: 10
                        border.bottom: 10
                        x: parent.width - width
                        Text {
                            id: label1


                            /*************
                                                     此处为可变大小的聊天气泡的重点
                                                     根据获取值的长度 和每个字占的像素
                                                    *************/
                            width: label1.text.length <= 10 ? label1.text.length * 12 : 120
                            font.pixelSize: 12
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
                    detail: "This is Client."
                }
            }
        }

        //右侧
        Rectangle {
            id: message3

            //            border.color: "black"
            anchors.right: parent.right
            anchors.top: window.top
            height: 510
            width: 0
        }

        Label {
            id: label2
            text: "value"
            anchors.top: message3.top
            x: 570
        }
        //底部
        Rectangle {
            height: 40
            width: 550
            anchors.bottom: parent.bottom
            id: bottomrect
            Row {
                TextField {
                    id: textfield
                    placeholderText: "输入内容"
                    height: bottomrect.height
                    width: window.width * 0.7
                }
            }
            Button {
                id: button1
                text: "Send"
                x: 560
                anchors.top: message3.bottom
                onClicked: {
                    listmodel.append({
                                         "detail": textfield.text
                                     })

                    textfield.text = ''
                }
            }
            Button {
                id: button2
                text: "Connect"
                anchors.left: button1.right
                onClicked: {
                    label2.text = client.mystring
                    client.connect_server()
                    //client.communication();
                }
                //连接信号 到qml
            }
        }

        ListView {
            width: 200
            height: 550
            add: Transition {
                //设置增加Item时的动画 from 100,100  to不设置 就是默认在ListView
                NumberAnimation {
                    properties: "x,y"
                    from: 100
                    duration: 1000
                }
            }
            id: listview2
            anchors.top: parent.top
            anchors.bottom: bottomrect.top
            anchors.left: parent.left
            anchors.right: parent.right
            //anchors的对象要么是兄弟结点（提供id）
            //要么就是子节点（parent）
            delegate: Component {
                //这里delegate:后面必须是Component
                Rectangle {
                    width: 200
                    height: label3.height
                    opacity: 0.8
                    BorderImage {
                        //聊天气泡
                        id: qipao
                        //                        source: "pao.png"
                        width: label3.width + 30
                        height: label3.height <= 30 ? 30 : label3.height + 5
                        //  width:20
                        border.left: 10
                        border.right: 10
                        border.top: 10
                        border.bottom: 10
                        x: parent.width - width
                        Text {
                            id: label3


                            /*************
                                     此处为可变大小的聊天气泡的重点
                                     根据获取值的长度和每个字占的像素
                                     *************/
                            width: label3.text.length <= 10 ? label3.text.length * 12 : 120
                            font.pixelSize: 12
                            anchors.centerIn: parent
                            anchors.leftMargin: 10
                            wrapMode: Text.Wrap //多行文本 超过width就自动换行
                            text: detail
                        }
                    }
                }
            }
            model: ListModel {
                id: listmodel2
                ListElement {
                    detail: ""
                }
            }
        }
        Rectangle {
            anchors.top: parent.top
            id: bottomrect2
            Row {
                Text {
                    id: textfield2
                    height: bottomrect2.height
                    width: window.width * 0.7
                    // anchors.top : ListView.top
                }
            }
        }
        Button {
            id: button4
            text: "recvmsg"
            x: 720
            y: 510
            onClicked: {
                listmodel2.append({
                                      "detail": textfield2.text
                                  })
                textfield2.text = "client message"
            }
        }
    }
}
