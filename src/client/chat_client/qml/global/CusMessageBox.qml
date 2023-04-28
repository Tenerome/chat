import QtQuick 2.9
import FluentUI 1.0

Item {
    property alias text: inner.text
    FluInfoBar {
        id: inner
    }
}
