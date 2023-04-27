import QtQuick 2.0
import QtQuick.Window 2.12
import mycpp.Client 1.0
import QtQuick.Controls 2.5
import "DefConst.js" as DC

import FluentUI 1.0

Window {
    id: mainWin
    width: 1600
    height: 900
    minimumWidth: 1200
    minimumHeight: 675
    visible: true
    CusClient {}
}
