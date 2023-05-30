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

    Rectangle {
        anchors.fill: parent
        color: "white"
        Row {
            FluText {
                text: "test download image"
            }
            Button {
                text: "select image"
                onClicked: {
                    image_select.open()
                }
            }
        }
    }
    FileDialog {
        id: image_select
        title: "Select an image"
        folder: StandardPaths.writableLocation($PicturesLocation)
        nameFilters: ["Image Files (*.png *.jpg)"]
        onAccepted: {
            var path = image_select.file.toString().substring(7)
            console.log($ftp.upLoad(path))
        }
    }
}
