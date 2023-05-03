import QtQuick 2.9
import QtQuick.Dialogs 1.3
import mycpp.Client 1.0
import FluentUI 1.0

Item {
    property alias client_socket: client_socket
    Client {
        id: client_socket
    }
    signal recvOneMessage(string str)
    Timer {
        id: recv_message_timer
        interval: 100
        running: true
        repeat: true
        onTriggered: {
            if (client_socket.getConnectStatus()) {
                var recv = client_socket.recvMessage()
                recvOneMessage(recv)
            } else {
                client_timer.start()
            }
        }
    }
    FluProgressRing {
        id: progress_ring
        x: 365
        y: 130
        visible: false
    }
    Timer {
        id: client_timer
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            if (client_socket.connect("127.0.0.1", "8888")) {
                showSuccess("connect to server")
                progress_ring.visible = false
                stop()
            } else {
                progress_ring.visible = true
                client_dialog.open()
            }
        }
    }
    signal close_by_Dialog
    FluContentDialog {
        id: client_dialog
        title: "client error"
        message: "Connection failed"
        negativeText: "Quit"
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
        onNegativeClicked: {
            client_timer.stop()
            close_by_Dialog()
        }
        positiveText: "Retry"
        onPositiveClicked: {
            showInfo("retry to connect")
        }
    }
}
