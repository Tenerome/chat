import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import "qrc:/qml/global/"
import FluentUI 1.0

FluScrollablePage {
    id: page
    leftPadding: 10
    rightPadding: 0
    bottomPadding: 10
    Item {
        id: message
        property alias text: inner.text
        Text {
            id: inner
        }
    }

    FluScrollablePage {
        id: textscroll
        width: page.width
        height: page.height - 300
        Rectangle {
            id: recarea
            width: textscroll.width - 30
            height: textscroll.height
            border.color: "#7F8C8D"
            radius: 10
        }
    }
    ColumnLayout {
        FluMultilineTextBox {
            id: multi_textbox
            Layout.preferredWidth: recarea.width
            Layout.preferredHeight: 200
        }
        RowLayout {
            FluFilledButton {
                id: send_btn
                text: "send"
                function movmessageBox(str) {
                    var component = Qt.createComponent(
                                "qrc:/qml/global/CusMessageBox.qml")
                    component.text = str
                    console.log(component.text)
                    if (component.status === Component.Ready) {
                        var newMessage = component.createObject(recarea)
                        newMessage.y += 30
                    } else {
                        console.log("Error loading component:",
                                    component.errorString())
                    }
                }
                onClicked: {
                    movmessageBox(multi_textbox.text)
                }
            }
            spacing: 50
            FluFilledButton {
                id: image_btn
                text: "image"
            }
        }
    }
}
