import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

PageBackground {
    id: pageBackground
    title: "Light"

    GridLayout {
        y: 100
        anchors.horizontalCenterOffset: -8
        anchors.horizontalCenter: parent.horizontalCenter
        columnSpacing: 13
        rowSpacing: 9
        rows: 2
        columns: 2
    }
}

/*##^## Designer {
    D{i:1;anchors_height:40;anchors_width:196;anchors_x:89;anchors_y:115}
}
 ##^##*/
