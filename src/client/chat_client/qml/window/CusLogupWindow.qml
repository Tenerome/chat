import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import FluentUI 1.0
import "qrc:/qml/global"
import "../global/Define.js" as Define

FluWindow {
    id: window
    title: "chat:logup"
    width: 800
    height: 600
    maximumWidth: 800
    maximumHeight: 600
    minimumWidth: 800
    minimumHeight: 600
    CusClient {
        id: cus_client
        onClose_by_Dialog: {
            window.close()
        }
        onRecvOneMessage: recv => {
                              if (recv !== "") {
                                  var recv_json = JSON.parse(recv)
                                  var flag = recv_json["flag"]
                                  switch (flag) {
                                      case Define.CLIENT_ACCOUNT_REGISTED:
                                      showError("The account has been registed")
                                      break
                                      case Define.CLIENT_TRUE:
                                      showSuccess("Log up succeed")
                                      break
                                  }
                              }
                          }
    }
    FluAppBar {
        id: appbar
        title: "Log up"
        width: parent.width
        showDark: true
        darkText: "Dark"
    }

    ColumnLayout {
        FluProgressRing {
            //progress ring
            id: progress_ring
            Layout.alignment: Qt.AlignHCenter
            Timer {
                interval: 1000
                repeat: false
                running: true
                onTriggered: {
                    progress_ring.destroy()
                }
            }
        }
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
        FluTooltip {
            id: tool_tip
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Image {
                Layout.alignment: Qt.AlignBottom
                source: FluTheme.darkMode === FluDarkMode.Dark ? "qrc:/res/icon/w_account.png" : "qrc:/res/icon/b_account.png"
                sourceSize.width: textbox_account.height - 5
                sourceSize.height: textbox_account.height - 5
            }
            FluTextBox {
                id: textbox_account
                placeholderText: "Input your account"
                Layout.preferredWidth: 260
                Layout.alignment: Qt.AlignHCenter
                focus: true
                validator: RegExpValidator {
                    regExp: /[1-9]([0-9]{7,10})/
                }
                onTextChanged: {
                    tool_tip.show("8-10 numbers", 2000)
                }
                onFocusChanged: {
                    if (!activeFocus) {
                        tool_tip.hide()
                    }
                }
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Image {
                Layout.alignment: Qt.AlignBottom
                source: FluTheme.darkMode === FluDarkMode.Dark ? "qrc:/res/icon/w_name.png" : "qrc:/res/icon/b_name.png"
                sourceSize.width: textbox_name.height - 5
                sourceSize.height: textbox_name.height - 5
            }
            FluTextBox {
                id: textbox_name
                Layout.topMargin: 20
                placeholderText: "Input your name"
                Layout.preferredWidth: 260
                Layout.alignment: Qt.AlignHCenter
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
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Image {
                Layout.alignment: Qt.AlignBottom
                source: FluTheme.darkMode === FluDarkMode.Dark ? "qrc:/res/icon/w_password.png" : "qrc:/res/icon/b_password.png"
                sourceSize.width: textbox_password.height - 5
                sourceSize.height: textbox_password.height - 5
            }
            FluTextBox {
                id: textbox_password
                Layout.topMargin: 20
                Layout.preferredWidth: 260
                placeholderText: "Input your password"
                echoMode: TextInput.Password
                Layout.alignment: Qt.AlignHCenter
                validator: RegExpValidator {
                    regExp: /[A-Za-z]{2}([0-9]{6,8})/
                }
                onTextChanged: {
                    tool_tip.show("tow letters with 6-8 numbers", 2000)
                }
                onFocusChanged: {
                    if (!activeFocus) {
                        tool_tip.hide()
                    }
                }
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Image {
                Layout.alignment: Qt.AlignBottom
                source: FluTheme.darkMode === FluDarkMode.Dark ? "qrc:/res/icon/w_password.png" : "qrc:/res/icon/b_password.png"
                sourceSize.width: textbox_password.height - 5
                sourceSize.height: textbox_password.height - 5
            }
            FluTextBox {
                id: textbox_verify_password
                Layout.topMargin: 20
                Layout.preferredWidth: 260
                placeholderText: "verify your password"
                echoMode: TextInput.Password
                Layout.alignment: Qt.AlignHCenter
                validator: RegExpValidator {
                    regExp: /[A-Za-z]{2}([0-9]{6,8})/
                }
                onTextChanged: {
                    tool_tip.show("tow letters with 6-8 numbers", 2000)
                }
                onFocusChanged: {
                    if (!activeFocus) {
                        tool_tip.hide()
                    }
                }
                Keys.enabled: true
                Keys.onPressed: {
                    if (event.key === Qt.Key_Enter - 1) {
                        logup_btn.clicked()
                    }
                }
            }
        }
        FluFilledButton {
            text: "back to login"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            onClicked: {
                //TODO format control
                FluApp.navigate("/login")
                window.close()
            }
        }
        FluFilledButton {
            id: logup_btn
            text: "log up"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            onClicked: {
                if (verifyValid()) {
                    var send_json = '{"flag":"' + Define.SOCKET_LOG_UP
                            + '","account":"' + textbox_account.text + '","name":"'
                            + textbox_name.text + '","password":"' + $UseMD5.toStr(
                                textbox_password.text) + '"}'
                    $Client.sendMessage(send_json)
                    console.log("log up succeed")
                    setNull()
                }
            }
        }
    }
    function verifyValid() {
        if (textbox_account.text.length < 8) {
            showError("account is too short")
            return false
        } else if (textbox_name.text.length < 5) {
            showError("name is too short")
            return false
        } else if (textbox_password.text.length < 8) {
            showError("password is too short")
            return false
        } else if (!verifyPasssword()) {
            showError("the two password are not same")
            return false
        } else
            return true
    }
    function verifyPasssword() {
        if (textbox_password.text === textbox_verify_password.text) {
            return true
        }
        return false
    }
    function setNull() {
        textbox_account.text = ""
        textbox_name.text = ""
        textbox_password.text = ""
        textbox_verify_password.text = ""
    }
}
