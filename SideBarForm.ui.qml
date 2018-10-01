import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

PageBackground
{
    id: pageBackground
    width: 300
    height: 800
    title: "Smart Home"

    ColumnLayout {
        x: 0
        y: 40

        Clock {
            id: clock
            Layout.preferredHeight: 100
            z: 1
        }

        WarningDisplay
        {
            id: warningDisplaySideBar
            objectName: "warningDisplaySideBar"
        }
    }
}

/*##^## Designer {
    D{i:8;anchors_x:74;anchors_y:104}
}
 ##^##*/
