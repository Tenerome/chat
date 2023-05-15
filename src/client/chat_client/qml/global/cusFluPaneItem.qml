import QtQuick 2.9
import FluentUI 1.0

FluPaneItem {
    temp_id: "del"
    title: "del"
    onTap: {
        tap_contact_S(temp_id)
    }
    onRclicked: {
        edit_contact_S(temp_id)
    }
}
