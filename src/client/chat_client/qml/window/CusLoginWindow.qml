import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import FluentUI 1.0
import "qrc:/qml/global"
import "../global/Define.js" as Define

FluWindow {
    id: window
    title: "chat:login"
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
                                      case Define.CLIENT_ACCOUNT_NOT_REGISTED:
                                      showError("This account does not exist")
                                      break
                                      case Define.CLIENT_WRONG_PASSWORD:
                                      showError("The password is wrong")
                                      break
                                      case Define.CLIENT_TRUE:
                                      Define.account = textbox_account.text
                                      FluApp.navigate("/main")
                                      window.close()
                                      break
                                  }
                              }
                          }
    }
    FluAppBar {
        id: appbar
        title: "Log in"
        width: parent.width
        showDark: true
        darkText: "Dark"
    }
    ColumnLayout {
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
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
        FluTooltip {
            id: tool_tip
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
            Keys.enabled: true
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter - 1) {
                    login_btn.clicked()
                }
            }
        }
        FluFilledButton {
            id: login_btn
            text: "log in"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            onClicked: {
                //TODO format control
                var send_json = '{"flag":"' + Define.SOCKET_LOG_IN + '","account":"'
                        + textbox_account.text + '","password":"' + $UseMD5.toStr(
                            textbox_password.text) + '"}'
                if (verifyValid()) {
                    $Client.sendMessage(send_json)
                }
            }
        }
        FluFilledButton {
            text: "log up"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            onClicked: {
                window.close()
                FluApp.navigate("/logup")
            }
        }
    }
    function verifyValid() {
        if (textbox_account.text.length < 8) {
            showError("account is too short")
            return false
        } else if (textbox_password.text.length < 8) {
            showError("password is too short")
            return false
        } else
            return true
    }
}
