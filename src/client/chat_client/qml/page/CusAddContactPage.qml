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
    Column {
        spacing: 10
        Row {
            leftPadding: 200
            spacing: 5
            FluTextBox {
                id: textbox_contact
            }
            FluFilledButton {
                height: textbox_contact.height
                text: "Add"
                onClicked: {
                    var send_json = '{"flag":"' + Define.SOCKET_ADD_CONTACT + '","account":"'
                            + Define.account + '","contact":"' + textbox_contact.text + '"}'
                    $Client.sendMessage(send_json)
                }
            }
            FluFilledButton {
                //TODEL
                height: textbox_contact.height
                text: "Clear history"
                onClicked: {
                    listmodel.clear()
                }
            }
        }
        //    }
        FluScrollablePage {
            id: scroll_page
            width: page.width - 50
            height: page.height - 150
            Rectangle {
                id: recarea
                width: scroll_page.width
                height: scroll_page.height
                color: "white"
                radius: 10
                ListView {
                    id: listview
                    width: parent.width
                    height: parent.height
                    spacing: 10
                    delegate: Component {
                        FluRectangle {
                            id: add_frame
                            width: scroll_page.width
                            height: 50
                            FluRectangle {
                                width: parent.width
                                height: parent.height
                                z: 1
                                radius: [10, 10, 10, 10]
                                color: "#BD29B6F6"
                            }
                            Row {
                                z: 2
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 15
                                FluText {
                                    id: label
                                    text: contact
                                    color: "red"
                                    pixelSize: add_frame.height - 20
                                }
                                FluText {
                                    text: " request to be your friend:"
                                    visible: flag === "0" ? true : false
                                    pixelSize: add_frame.height - 20
                                }
                                FluText {
                                    text: " agree to be your friend"
                                    visible: flag === "1" ? true : false
                                    pixelSize: add_frame.height - 20
                                }
                                FluText {
                                    text: " reject to be your friend"
                                    visible: flag === "2" ? true : false
                                    pixelSize: add_frame.height - 20
                                }
                                FluFilledButton {
                                    id: reject_add
                                    anchors.verticalCenter: label.verticalCenter
                                    text: "Reject"
                                    normalColor: "orange"
                                    height: add_frame.height - 20
                                    visible: flag === "0" ? true : false //control diff
                                    onClicked: {
                                        var send_json = '{"flag":"' + Define.SOCKET_ANSWER_ADD
                                                + '","answer_flag":"'
                                                + Define.CLIENT_REJECT_ADD_CONTACT + '","account":"'
                                                + Define.account + '","contact":"' + contact + '"}'
                                        $Client.sendMessage(send_json)
                                        reject_add.enabled = false
                                        agree_add.visible = false
                                        reject_add.normalColor = "black"
                                    }
                                }
                                FluFilledButton {
                                    id: agree_add
                                    anchors.verticalCenter: label.verticalCenter
                                    text: "Agree"
                                    normalColor: "green"
                                    height: add_frame.height - 20
                                    visible: flag === "0" ? true : false
                                    onClicked: {
                                        var send_json = '{"flag":"' + Define.SOCKET_ANSWER_ADD
                                                + '","answer_flag":"'
                                                + Define.CLIENT_AGREE_ADD_CONTACT + '","account":"'
                                                + Define.account + '","contact":"' + contact + '"}'
                                        $Client.sendMessage(send_json)
                                        agree_add.enabled = false
                                        reject_add.visible = false
                                        agree_add.normalColor = "black"
                                    }
                                }
                            }
                        }
                    }
                    model: Define.add_page_listmodel
                }
            }
        }
    }
}
