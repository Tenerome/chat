import QtQuick 2.9
import QtQuick.Window 2.12
import "./qml"

Window {
    width: 800
    height: 600
    visible: true
    Rectangle {
        anchors.fill: parent
        color: "white"
        CusClient.load()
    }
}
