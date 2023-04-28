import QtQuick 2.9
import QtQuick.Dialogs 1.3
import mycpp.Client 1.0
import FluentUI 1.0

Item {
    property alias client_socket: client_socket
    Client {
        id: client_socket
    }
    Timer {
        id: client_timer
        interval: 500
        repeat: true
        running: true
        onTriggered: {
            if (client_socket.connect("127.0.0.1", "8888")) {
                stop()
            } else {
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
            showSuccess("retry to connect socket")
        }
    }
}
