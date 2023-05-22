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
    Rectangle {
        id: inner
        width: page.width - 50
        height: page.height - 150
        border.color: "gray"
        color: FluTheme.darkMode === FluDarkMode.Dark ? "#454545" : "white"
        radius: 10
        ColumnLayout {
            x: 50
            y: 50
            spacing: 10
            RowLayout {
                spacing: 5
                FluText {
                    text: "uid:"
                    pixelSize: 20
                }
                FluText {
                    text: Define.uid
                    pixelSize: 20
                }
            }
            RowLayout {
                spacing: 5
                FluText {
                    text: "name:"
                    pixelSize: 20
                }
                FluText {
                    text: Define.name
                    pixelSize: 20
                }
            }
            RowLayout {
                FluTooltip {
                    id: tool_tip
                }
                FluTextBox {
                    id: set_name
                    placeholderText: "Input new name"
                    Layout.preferredWidth: 260
                    Layout.alignment: Qt.AlignHCenter
                    focus: true
                    validator: RegExpValidator {
                        regExp: /([A-Za-z]{5,10})/
                    }
                    onTextChanged: {
                        tool_tip.show("5-10 letters", 2000)
                    }
                    onFocusChanged: {
                        if (!activeFocus) {
                            tool_tip.hide()
                        }
                    }
                    Keys.enabled: true
                    Keys.onPressed: {
                        if (event.key === Qt.Key_Enter - 1) {
                            setname_btn.clicked()
                        }
                    }
                }
                FluFilledButton {
                    id: setname_btn
                    text: "set name"
                    onClicked: {
                        if (set_name.text.length < 5) {
                            showError("name is too short")
                        } else if (set_name.text === Define.name) {
                            showError("please use a new name")
                        } else {
                            var send_json = '{"flag":"' + Define.SOCKET_EDIT_CONTACT
                                    + '","edit_flag":"' + Define.CLIENT_EDIT_NICKNAME
                                    + '","account":"' + Define.account + '","contact":"'
                                    + Define.account + '","nickname":"' + set_name.text + '"}'
                            $Client.sendMessage(send_json)
                            set_name.text = ""
                            showSuccess("Set Succeed,Please Flush")
                        }
                    }
                }
            }
        }
    }
}
