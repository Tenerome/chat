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
                if (recv !== "") {
                    console.log("recv message:" + recv) //TODEL
                    recvOneMessage(recv)
                }
            } else {
                client_timer.start()
            }
            recv = ""
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
        title: appInfo.lang.objectName === "En" ? "client error" : "错误"
        message: appInfo.lang.objectName === "En" ? "Connection failed" : "连接断开"
        negativeText: lang.quit
        buttonFlags: FluContentDialog.NegativeButton | FluContentDialog.PositiveButton
        onNegativeClicked: {
            client_timer.stop()
            close_by_Dialog()
        }
        positiveText: lang.retry
        onPositiveClicked: {
            showInfo(appInfo.lang.objectName === "En" ? "retry to connect" : "重新连接")
        }
    }
}
