import QtQuick 2.0
import QtQuick.Window 2.12
import mycpp.Client 1.0
import QtQuick.Controls 2.5

Window {
    property string lv1UI_color: "#7B7D7D"
    property string lv2UI_color: "#7F8C8D"
    property string lv3UI_color: "#95A5A6"
    property string component_color: "#BDC3C7"
    property string font_color: "#ECF0F1"
    id: mainWin
    width: 1600
    height: 900
    minimumWidth: 1200
    minimumHeight: 675
    visible: true
    CusClient {} //client_socket
    Rectangle {
        //root
        id: root
        anchors.fill: parent
        color: lv1UI_color
        Rectangle {
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 2
            color: lv2UI_color
            Grid {
                rows: 3
                columns: 2
                rowSpacing: 10
                columnSpacing: 5
                anchors.centerIn: parent
                Text {
                    id: account_label
                    text: "account:"
                    color: font_color
                }
                TextField {
                    id: account
                    width: 200
                    maximumLength: 8
                    selectByMouse: true
                    selectionColor: lv1UI_color
                    placeholderText: "input account"
                    background: Rectangle {
                        radius: 5
                    }
                }
                Text {
                    id: password_label
                    text: "password:"
                    color: font_color
                }
                TextField {
                    id: password
                    width: 200
                    maximumLength: 20
                    selectByMouse: true
                    selectionColor: lv1UI_color
                    placeholderText: "input password"
                }
                Rectangle {
                    anchors {
                        left: parent.left
                        bottom: parent.bottom
                    }
                    Button {
                        id: logup
                        text: "Log up"
                    }
                }
                Rectangle {
                    anchors {
                        right: parent.right
                        bottom: parent.bottom
                    }
                    Button {
                        id: login
                        text: "Log in"
                    }
                }
            }
        }
    }
}
