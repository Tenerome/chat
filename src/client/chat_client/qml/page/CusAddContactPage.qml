import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import FluentUI 1.0
import "qrc:/qml/global/"
import "../global/Define.js" as Define

FluScrollablePage {
    id: page
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
                                      case Define.CLIENT_ACCOUNT_ONLINE:
                                      showSuccess("Send add request")
                                      break
                                      case Define.CLIENT_BUFFER_ADD_CONTACT:
                                      showSuccess("Send add request")
                                      break
                                      case Define.CLIENT_ADD_CONTACT_REQUEST:
                                      var contact = recv_json["account"]
                                      Define.contact = contact
                                      add_contact_dialog.open()
                                      break
                                      case Define.CLIENT_ANSWER_YES:
                                      //listmodel
                                      var contact1 = recv_json["account"]
                                      showSuccess(
                                          contact1 + "agree to be your friend")
                                      break
                                      case Define.CLIENT_ANSWER_NO:
                                      //listmodel
                                      var contact2 = recv_json["account"]
                                      showSuccess(
                                          contact2 + "agree to be your friend")
                                      break
                                  }
                              }
                          }
    }
    FluArea {
        width: page.width - 50
        height: 600
        Row {
            Layout.alignment: Qt.AlignCenter
            FluTextBox {
                id: textbox_contact
            }
            spacing: 30
            FluFilledButton {
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
    FluContentDialog {
        id: add_contact_dialog
        title: Define.contact + "request to be your friend"
        message: "Agree or reject?"
        negativeText: "Reject"
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
        onNegativeClicked: {
            //TODO
            var send_json = '{"flag":"' + Define.SOCKET_ANSWER_ADD + '","answer_flag":"'
                    + Define.CLIENT_REJECT_ADD_CONTACT + '","account":"'
                    + Define.account + '","contact":"' + Define.contact + '"}'
            $Client.sendMessage(send_json)
        }
        positiveText: "Agree"
        onPositiveClicked: {
            var send_json = '{"flag":"' + Define.SOCKET_ANSWER_ADD + '","answer_flag":"'
                    + Define.CLIENT_AGREE_ADD_CONTACT + '","account":"'
                    + Define.account + '","contact":"' + Define.contact + '"}'
            $Client.sendMessage(send_json)
        }
    }
}
