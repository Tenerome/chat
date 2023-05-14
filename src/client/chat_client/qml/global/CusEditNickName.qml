import QtQuick 2.9
import FluentUI 1.0
import QtQuick.Layouts 1.3

FluRectangle {
    id: rec
    RowLayout {
        anchors.fill: parent
        width: 520
        height: 55
        spacing: 10
        Rectangle {
            color: "#BD29B6F7"
            border.color: "gray"
            radius: 10
            width: 350
            height: 45
            TextEdit {
                id: new_nickname
                anchors.fill: parent
                Layout.preferredHeight: 45
                Layout.preferredWidth: 350
                verticalAlignment: TextEdit.AlignVCenter
                leftPadding: 2
                selectByMouse: true
                cursorVisible: true
                selectionColor: "#66B3FF"
                focus: true
            }
        }
        FluFilledButton {
            text: "confirm"
            height: 50
        }
        FluFilledButton {
            text: "cancel"
            height: 50
            onClicked: {
                //                edit_window.visible = false
                rec.parent.pop()
            }
        }
    }
}
