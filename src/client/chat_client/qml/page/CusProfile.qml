import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import FluentUI 1.0
import "qrc:/qml/global/"
import "../global/Define.js" as Define

FluContentPage {
    id: page
    width: parent.width
    height: parent.height
    Rectangle {
        id: inner
        width: page.width - 200
        height: page.height - 200
        anchors.topMargin: 80
        border.color: "gray"
    }
}
