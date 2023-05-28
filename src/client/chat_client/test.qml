import QtQuick 2.9
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import FluentUI 1.0

Window {
    id: window
    maximumWidth: Screen.width
    maximumHeight: Screen.height
    minimumWidth: 600
    minimumHeight: 400
    visible: true
    Component.onCompleted: {

        $ftp.downLoad("/pub/test/img0.jpg")
        //        $ftp.upLoad("/home/tenerome/Pictures/img1.jpg")
    }
    FluAppBar {
        width: parent.width
    }
    Rectangle {
        anchors.fill: parent
        color: "white"
        Row {
            FluText {
                text: "test download image"
            }
        }
    }
}
