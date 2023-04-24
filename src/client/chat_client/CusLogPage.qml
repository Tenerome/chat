import QtQuick 2.0
import QtQuick.Window 2.12
import mycpp.Client 1.0
import QtQuick.Controls 2.5

Window {
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
            //log up and in frame
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 2
            color: lv2UI_color
            Grid {
                rows: 5
                columns: 2
                rowSpacing: 10
                columnSpacing: 5
                anchors.centerIn: parent
                //account
                Text {
                    id: account_label
                    text: "account:"
                    color: font_color
                }

                CusTextField {
                    id: account
                    maximumLength: 8
                }
                //name
                Text {
                    id: name_label
                    text: "name:"
                    color: font_color
                    visible: false
                }
                CusTextField {
                    id: name
                    maximumLength: 16
                    visible: false
                }
                //password
                Text {
                    id: password_label
                    text: "password:"
                    color: font_color
                }
                CusTextField {
                    id: password
                    maximumLength: 20
                    echoMode: TextInput.Password
                }
                //verify password
                Text {
                    id: verify_password_label
                    text: "verify password:"
                    color: font_color
                    visible: false
                }
                CusTextField {
                    id: verify_password
                    maximumLength: 20
                    echoMode: TextInput.Password
                    visible: false
                }
                //Button
                Button {
                    id: log_up
                    text: "log up"
                    x: this.x + 50
                    y: this.y + 30
                    onClicked: {
                        name_label.visible = true
                        name.visible = true
                        verify_password_label.visible = true
                        verify_password.visible = true

                        log_up.visible = false
                        log_in.visible = false

                        confirm_log_up.visible = true
                        back_to_log_in.visible = true
                    }
                }
                Button {
                    id: log_in
                    text: "log in"
                    x: this.x + 150
                    y: this.y + 30
                }

                Button {
                    id: confirm_log_up
                    text: "confirm log up"
                    visible: false
                    x: this.x + 30
                    y: this.y + 10
                }
                Button {
                    id: back_to_log_in
                    text: "back to log in"
                    visible: false
                    x: this.x + 100
                    y: this.y + 10
                    onClicked: {
                        name_label.visible = false
                        name.visible = false
                        verify_password_label.visible = false
                        verify_password.visible = false

                        log_up.visible = true
                        log_in.visible = true

                        confirm_log_up.visible = false
                        back_to_log_in.visible = false
                    }
                }
            }
        }
    }
}
