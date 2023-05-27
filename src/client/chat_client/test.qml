import QtQuick 2.9
import QtQuick.Window 2.3
import "./qml"
import FluentUI 1.0

Window {
    id: window
    width: Screen.width
    height: Screen.height
    visible: true
    FluAppBar {
        width: parent.width
    }
    Rectangle {
        anchors.fill: parent
        color: "white"
        Row {
            FluText {
                text: lang.home
            }
            FluTextBox {}
        }
        //        Image {
        //            source: "ftp://127.0.0.1/pub/test/img0.jpg"
        //            sourceSize.width: window.width
        //            sourceSize.height: window.height
        //            width: 400
        //            height: 200
        //        }
    }
}
