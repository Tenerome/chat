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
            FluTooltip {
                id: tool_tip
            }
            FluTextBox {
                id: textbox_contact
                validator: RegExpValidator {
                    regExp: /[1-9]([0-9]{7,10})/
                }
                onTextChanged: {
                    tool_tip.show(lang.account_format, 2000)
                }
                onFocusChanged: {
                    if (!activeFocus) {
                        tool_tip.hide()
                    }
                }
            }
            FluFilledButton {
                height: textbox_contact.height
                text: lang.add
                onClicked: {
                    if (textbox_contact.text.length < 8) {
                        showError(lang.account_short)
                    } else if (textbox_contact.text === Define.account) {
                        showError(appInfo.lang.objectName
                                  === "En" ? "you can't add yourself" : "不能添加自已")
                    } else if (alreadyContact()) {
                        showError(appInfo.lang.objectName
                                  === "En" ? "this account has been your contact" : "已经是好友了")
                    } else {
                        var send_json = '{"flag":"' + Define.SOCKET_ADD_CONTACT
                                + '","account":"' + Define.account
                                + '","contact":"' + textbox_contact.text + '"}'
                        $Client.sendMessage(send_json)
                    }
                }
            }
            FluFilledButton {
                height: textbox_contact.height
                text: lang.clear_history
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
                color: FluTheme.darkMode === FluDarkMode.Dark ? "#454545" : "white"
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
                                color: FluTheme.darkMode
                                       === FluDarkMode.Dark ? "#707B7C" : "#ECF0F1"
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
                                    text: appInfo.lang.objectName
                                          === "En" ? " request to be your friend:" : " 申请添加好友："
                                    visible: flag === "0" ? true : false
                                    pixelSize: add_frame.height - 20
                                }
                                FluText {
                                    text: appInfo.lang.objectName
                                          === "En" ? " agree to be your friend" : " 同意添加好友"
                                    visible: flag === "1" ? true : false
                                    pixelSize: add_frame.height - 20
                                }
                                FluText {
                                    text: appInfo.lang.objectName
                                          === "En" ? " reject to be your friend" : " 拒绝添加好友"
                                    visible: flag === "2" ? true : false
                                    pixelSize: add_frame.height - 20
                                }
                                FluFilledButton {
                                    id: reject_add
                                    anchors.verticalCenter: label.verticalCenter
                                    text: appInfo.lang.objectName === "En" ? "Reject" : "拒绝"
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
                                        reject_add.normalColor = "#486FC3"
                                    }
                                }
                                FluFilledButton {
                                    id: agree_add
                                    anchors.verticalCenter: label.verticalCenter
                                    text: appInfo.lang.objectName === "En" ? "Agree" : "同意"
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
                                        agree_add.normalColor = "#486FC3"
                                        showSuccess(appInfo.lang.objectName === "En" ? "Add Contact,Please Flush" : "添加成功，请刷新")
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
    function alreadyContact() {
        for (let key in Define.contact_map)
            if (textbox_contact.text === key) {
                return true
            } else {
                return false
            }
    }
}
