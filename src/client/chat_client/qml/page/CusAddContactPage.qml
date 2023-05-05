import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import FluentUI 1.0
import "qrc:/qml/global/"
import "../global/Define.js" as Define

Page {
    id: page
    CusClient {
        id: cus_client
        onClose_by_Dialog: {
            window.close()
        }
        onRecvOneMessage: recv => {}
    }
    Rectangle {
        anchors.centerIn: parent
        Row {
            anchors.centerIn: parent
            FluTextBox {
                id: textbox_contact
            }
            spacing: 30
            FluFilledButton {
                anchors.bottom: account_text.bottom
                height: textbox_contact.height
                text: "Add"
                onClicked: {
                    var send_json = '{"flag":"' + Define.SOCKET_ADD_CONTACT + '","account":"'
                            + Define.account + '","contact":"' + textbox_contact.text + '"}'
                    $Client.sendMessage(send_json)
                }
            }
        }
    }
}
