import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1
import FluentUI 1.0
import "../global/Define.js" as Define

FluContentPage {
    id: page
    width: parent.width
    height: parent.height
    visible: true
    property var contact
    property var chat_model
    property var downloading_image
    //shared variable
    Component.onCompleted: {
        for (let key in Define.load_model) {
            if (key === "contact")
                contact = Define.load_model[key]
            else
                chat_model = Define.load_model[key]
        }
    }
    ColumnLayout {
        spacing: 10
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
                color: FluTheme.darkMode === FluDarkMode.Dark ? "#454545" : "white"
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
                            property alias label: label
                            property alias image_display: image_display
                            states: [
                                State {
                                    name: "txtme"
                                    PropertyChanges {
                                        target: ballon
                                        color: "#4D10CCEE"
                                        width: label.width + 20
                                        height: label.height <= 120 ? 120 : label.height + 20
                                        x: listview.width - ballon.width
                                        label.visible: true
                                        label.anchors.centerIn: ballon
                                        image_display.visible: false
                                    }
                                },
                                State {
                                    name: "txtother"
                                    PropertyChanges {
                                        target: ballon
                                        x: 0
                                        color: "#4D7B7D7D"
                                        width: label.width + 20
                                        height: label.height <= 120 ? 120 : label.height + 20
                                        label.visible: true
                                        label.anchors.centerIn: ballon
                                        image_display.visible: false
                                    }
                                },
                                State {
                                    name: "imageme"
                                    PropertyChanges {
                                        target: ballon
                                        color: "#4D10CCEE"
                                        x: listview.width - ballon.width
                                        width: image_display.width + 20
                                        height: image_display.height + 20
                                        label.visible: false
                                        image_display.visible: true
                                    }
                                },
                                State {
                                    name: "imageother"
                                    PropertyChanges {
                                        target: ballon
                                        color: "#4D7B7D7D"
                                        x: 0
                                        width: image_display.width + 50
                                        height: image_display.height + 50
                                        label.visible: contact === "$chatroom" ? true : false
                                        label.text: contact === "$chatroom" ? (contacts + ":") : ""
                                        label.z: 999
                                        label.x: 10
                                        label.width: ballon.width
                                        label.anchors {
                                            top: ballon.top
                                        }
                                        image_display.visible: true
                                    }
                                }
                            ]
                            state: type === 0 ? (position === 0 ? "txtme" : "txtother") : (position === 0 ? "imageme" : "imageother")
                            radius: 20
                            TextEdit {
                                id: label
                                width: label.text.length <= 20 ? label.text.length * 12 : 250
                                font.pixelSize: 20
                                color: FluTheme.darkMode === FluDarkMode.Dark ? "white" : "black"
                                wrapMode: Text.Wrap
                                readOnly: true
                                selectByMouse: true
                                selectedTextColor: Qt.rgba(51, 153, 255, 1)
                                text: detail
                            }
                            Image {
                                id: image_display
                                anchors.centerIn: parent
                                visible: false
                                source: image_display.visible
                                        === true ? ("ftp://127.0.0.1" + detail) : ""
                                fillMode: Image.PreserveAspectFit //keep the width:height
                                //                                sourceSize.width: sourceSize.width < 500 ? sourceSize.width : 500
                                width: sourceSize.width < 500 ? sourceSize.width : 500
                                MouseArea {
                                    anchors.fill: parent
                                    acceptedButtons: Qt.RightButton
                                    onClicked: {
                                        popmenu.popup()
                                        downloading_image = detail
                                    }
                                }
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
            //max length control
            onTextChanged: {
                if (text.length > 2047) {
                    text = text.substring(0, 2047)
                }
            }
            Keys.enabled: true
            Keys.onReturnPressed: {
                if (multi_textbox.text !== "") {
                    chat_model.append({
                                          "detail": multi_textbox.text,
                                          "type": 0,
                                          "position": 0
                                      })

                    var send_json = '{"flag":"' + Define.SOCKET_MESSAGE
                            + '","message_flag":"' + Define.CLIENT_TEXT_MESSAGE
                            + '","account":"' + Define.account + '","contact":"'
                            + contact + '","message":"' + multi_textbox.text + '"}'
                    $Client.sendMessage(send_json)
                }
                multi_textbox.clear()
            }
        }
        FluFilledButton {
            text: appInfo.lang.objectName === "En" ? "send image" : "发送图片"
            onClicked: {
                image_select.open()
            }
        }
    }
    FluMenu {
        id: popmenu
        FluMenuItem {
            text: lang.cancel
        }
        FluMenuItem {
            text: lang.download
            onClicked: {
                $ftp.downLoad(downloading_image)
                showSuccess(appInfo.lang.objectName === "En" ? "download succeed,in default Download directory" : "下载成功,位于默认下载目录",
                            3000)
            }
        }
    }
    FileDialog {
        id: image_select
        title: "Select an image"
        folder: StandardPaths.writableLocation($PicturesLocation)
        nameFilters: ["Image Files (*.png *.jpg)"]
        onAccepted: {
            var path = $ftp.upLoad(image_select.file.toString().substring(7))
            chat_model.append({
                                  "detail": path,
                                  "type": 1,
                                  "position": 0
                              })
            var send_json = '{"flag":"' + Define.SOCKET_MESSAGE + '","message_flag":"'
                    + Define.CLIENT_IMAGE_MESSAGE + '","account":"' + Define.account
                    + '","contact":"' + contact + '","message":"' + path + '"}'
            $Client.sendMessage(send_json)
        }
    }
}
