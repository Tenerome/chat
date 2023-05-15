import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0

FluScrollablePage {

    title: "Settings"
    leftPadding: 10
    rightPadding: 10
    bottomPadding: 20
    spacing: 0

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 136
        paddings: 10

        ColumnLayout {
            spacing: 10
            anchors {
                top: parent.top
                left: parent.left
            }
            FluText {
                text: "Dark Mode"
                fontStyle: FluText.BodyStrong
                Layout.bottomMargin: 4
            }
            Repeater {
                model: [{
                        "title": "System",
                        "mode": FluDarkMode.System
                    }, {
                        "title": "Light",
                        "mode": FluDarkMode.Light
                    }, {
                        "title": "Dark",
                        "mode": FluDarkMode.Dark
                    }]
                delegate: FluRadioButton {
                    selected: FluTheme.darkMode === modelData.mode
                    text: modelData.title
                    onClicked: {
                        FluTheme.darkMode = modelData.mode
                    }
                }
            }
        }
    }
}
