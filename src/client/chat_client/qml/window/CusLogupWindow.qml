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
    }

    ColumnLayout {
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
        FluTextBox {
            id: textbox_account
            placeholderText: "Input your account"
            Layout.preferredWidth: 260
            Layout.alignment: Qt.AlignHCenter
        }
        FluTextBox {
            id: textbox_name
            placeholderText: "Input your name"
            Layout.preferredWidth: 260
            Layout.alignment: Qt.AlignHCenter
        }
        FluTextBox {
            id: textbox_password
            Layout.topMargin: 20
            Layout.preferredWidth: 260
            placeholderText: "Input your password"
            echoMode: TextInput.Password
            Layout.alignment: Qt.AlignHCenter
        }
        FluTextBox {
            id: textbox_verify_password
            Layout.topMargin: 20
            Layout.preferredWidth: 260
            placeholderText: "verify your password"
            echoMode: TextInput.Password
            Layout.alignment: Qt.AlignHCenter
            Keys.enabled: true
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter - 1) {
                    logup_btn.clicked()
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
                var send_json = '{"flag":"' + Define.SOCKET_LOG_UP + '","account":"'
                        + textbox_account.text + '","name":"' + textbox_name.text
                        + '","password":"' + textbox_password.text + '"}'
                $Client.sendMessage(send_json)
            }
        }
    }
}
