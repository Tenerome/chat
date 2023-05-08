import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import FluentUI 1.0
import "qrc:/qml/global/"
import "../global/Define.js" as Define

FluContentPage {
    id: page
    width: parent.width
    height: parent.height
    visible: true
    Component.onCompleted: {
        listmodel.clear()
        Define.add_page_listmodel = listmodel
    }
    //    CusClient {
    //        id: cus_client
    //        onClose_by_Dialog: {
    //            window.close()
    //        }
    //        onRecvOneMessage: recv => {
    //                              if (recv !== "") {
    //                                  parseJson(recv)
    //                              }
    //                          }
    //    }
    //    function parseJson(recv) {
    //        console.log(recv)
    //        var recv_json = JSON.parse(recv)
    //        var flag = recv_json["flag"]
    //        var contact = recv_json["contact"]
    //        switch (flag) {
    //        case Define.CLIENT_ACCOUNT_NOT_REGISTED:
    //            showError("This account does not exist")
    //            break
    //        case Define.CLIENT_ACCOUNT_ONLINE:
    //            showSuccess("Send add request")
    //            break
    //        case Define.CLIENT_BUFFER_ADD_CONTACT:
    //            showSuccess("Send add request")
    //            break
    //        case Define.CLIENT_ADD_CONTACT_REQUEST:
    //            listmodel.append({
    //                                 "contact": contact,
    //                                 "flag": "0"
    //                             })
    //            break
    //        case Define.CLIENT_ANSWER_YES:
    //            listmodel.append({
    //                                 "contact": contact,
    //                                 "flag": "1"
    //                             })
    //            break
    //        case Define.CLIENT_ANSWER_NO:
    //            listmodel.append({
    //                                 "contact": contact,
    //                                 "flag": "2"
    //                             })
    //            break
    //        }
    //    }
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
                            width: page.width
                            height: 50
                            //                            color: "orange"
                            Row {
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
                                    text: " agree to be your friend:"
                                    visible: flag === "1" ? true : false
                                    pixelSize: add_frame.height - 20
                                }
                                FluText {
                                    text: " reject to be your friend:"
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
                    model: ListModel {
                        id: listmodel
                        ListElement {
                            flag: ""
                            contact: ""
                        }
                    }
                }
            }
        }
    }
}
