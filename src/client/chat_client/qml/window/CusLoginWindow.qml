import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import FluentUI 1.0
import "qrc:/qml/global"

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
    }
    FluAppBar {
        id: appbar
        title: "Log in"
        width: parent.width
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
        FluTextBox {
            id: textbox_account
            placeholderText: "Input your account"
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
        FluFilledButton {
            id: login_btn
            text: "log in"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            signal sendMessage(string str)
            onClicked: {
                //TODO format control
                sendMessage(textbox_account.text + textbox_password.text)
                FluApp.navigate("/main")
                window.close()
            }
        }
        FluFilledButton {
            text: "log up"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            onClicked: {
                FluApp.navigate("/logup")
                window.close()
            }
        }
    }
}
