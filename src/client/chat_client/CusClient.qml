import QtQuick 2.0
import QtQuick.Dialogs 1.3
import mycpp.Client 1.0

Item {
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
    MessageDialog {
        id: client_dialog
        title: "client error"
        text: "Connection failed"
        standardButtons: StandardButton.Retry | StandardButton.Close
        onAccepted: {
            console.log("retry to connect server")
        }
        onRejected: {
            client_timer.stop()
            mainWin.close()
        }
    }
}
