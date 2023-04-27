import QtQuick 2.0
import QtQuick.Controls 2.5
import "DefConst.js" as DC

Rectangle {
    id: inputBox
    width: 300
    height: 50
    color: "#f2f2f2"
    border.color: "#bfbfbf"
    border.width: 1
    radius: 5

    property alias maximumLength: txtin.maximumLength
    property alias echoMode: txtin.echoMode
    property alias label: txt.text
    Text {
        id: txt
        color: DC.font_color
        visible: true
        anchors.centerIn: parent
    }
    TextInput {
        id: txtin
        width: inputBox.width - 10
        height: inputBox.height - 10
        anchors.centerIn: parent
        anchors.left: txt.right
        font.pointSize: 20
        selectByMouse: true
        selectionColor: DC.lv1UI_color
    }
}
