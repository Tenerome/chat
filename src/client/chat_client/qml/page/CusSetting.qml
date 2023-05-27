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
        height: 400
        paddings: 10
        ColumnLayout {
            spacing: 10
            anchors {
                top: parent.top
                left: parent.left
            }
            FluText {
                text: lang.opacity
                fontStyle: FluText.BodyStrong
                Layout.bottomMargin: 4
            }
            FluSlider {
                id: opacity_slider
                value: 25
                maxValue: 25
                onValueChanged: {
                    window.opacity = (value + 75) / 100
                }
            }

            FluText {
                text: lang.darkmode
                fontStyle: FluText.BodyStrong
                Layout.bottomMargin: 4
            }
            Repeater {
                model: [{
                        "title": lang.system,
                        "mode": FluDarkMode.System
                    }, {
                        "title": lang.light,
                        "mode": FluDarkMode.Light
                    }, {
                        "title": lang.dark,
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

            FluText {
                text: lang.locale
                fontStyle: FluText.BodyStrong
                Layout.bottomMargin: 4
            }

            Flow {
                spacing: 5
                Repeater {
                    model: ["Zh", "En"]
                    delegate: FluRadioButton {
                        selected: appInfo.lang.objectName === modelData
                        text: modelData
                        onClicked: {
                            appInfo.changeLang(modelData)
                        }
                    }
                }
            }
        }
    }
}
