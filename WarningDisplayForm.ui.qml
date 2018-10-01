import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item
{
    property alias nbErrorCounterTextVisible: nbErrorCounterText.visible
    property alias nbErrorCounterText: nbErrorCounterText.text
    property alias warningTextText: warningText.text
    property alias rectangleColor: rectangle.color

    id: warningDisplay
    width: 300
    height: 100

    Rectangle
    {
        id: rectangle
        color: "#a58107"
        anchors.fill: parent

        ColumnLayout {
            anchors.leftMargin: 10
            spacing: 0
            anchors.fill: parent

            Text {
                id: warningText
                color: "#ffffff"
                text: qsTr("Text")
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredHeight: 27
                Layout.preferredWidth: 283
                font.pixelSize: 26
            }

            Text {
                id: nbErrorCounterText
                color: "#ffffff"
                text: qsTr("0")
                Layout.preferredHeight: 27
                Layout.preferredWidth: 283
                font.pixelSize: 20
            }
        }
    }

}

/*##^## Designer {
    D{i:1;anchors_height:200;anchors_width:200;anchors_x:64;anchors_y:110}
}
 ##^##*/
