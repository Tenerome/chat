import QtQuick 2.9
import FluentUI 1.0

FluPaneItem {
    temp_id: "del"
    title: "del"
    //    cusIcon: Image {
    //        source: FluTheme.darkMode
    //                === FluDarkMode.Dark ? "qrc:/res/icon/w_contact.png" : "qrc:/res/icon/b_contact.png"
    //        width: 20
    //        height: 20
    //    }
    onTap: {
        tap_contact_S(temp_id)
    }
    onRclicked: {
        edit_contact_S(temp_id)
    }
}
