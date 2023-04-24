import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id: inputBox
    width: 300
    height: 50
    color: "#f2f2f2"
    border.color: "#bfbfbf"
    border.width: 1
    radius: 5

    property alias maximumLength: inputText.maximumLength
    property alias echoMode: inputText.echoMode
    TextInput {
        id: inputText
        width: inputBox.width - 10
        height: inputBox.height - 10
        anchors.centerIn: parent
        font.pointSize: 20
        selectByMouse: true
        selectionColor: lv1UI_color
    }
}
