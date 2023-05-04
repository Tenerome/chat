import QtQuick 2.9
import QtQuick.Dialogs 1.3
import FluentUI 1.0

Item {
    signal recvOneMessage(string str)
    Timer {
        id: recv_message_timer
        interval: 100
        running: true
        repeat: true
        onTriggered: {
            if ($Client.getConnectStatus()) {
                var recv = $Client.recvMessage()
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
            if ($Client.getConnectStatus()) {
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
