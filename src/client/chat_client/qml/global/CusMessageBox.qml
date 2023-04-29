import QtQuick 2.9
import FluentUI 1.0

//    property alias text: inner.text
Component {
    property alias text: inner.text
    FluText {
        id: inner
    }
}
