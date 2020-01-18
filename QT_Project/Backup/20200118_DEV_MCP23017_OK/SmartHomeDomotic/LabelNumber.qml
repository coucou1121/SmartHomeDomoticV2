import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Label
{

    property alias labelNumberText: labelNumber.text
    property alias textNumberText: textNumber.text

    id: labelNumber
    width: 300
    height: 100
    color:  Material.color(Material.Grey)
    text: "title"
    textFormat: Text.AutoText
    verticalAlignment: Text.AlignTop
    horizontalAlignment: Text.AlignHCenter
    font.family: "Arial"
    rotation: 0
    font.bold: false
    font.pointSize: 16

    Rectangle {
        id: rectangle
        color: "#353131"
        anchors.fill: parent
        z: -1
        opacity: 1
        border.width: 0
    }


        Text
        {
            id: textNumber
            color: "#ffffff"
            text: qsTr("value")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.bottom
            anchors.topMargin: -30
            anchors.right: parent.right
            anchors.rightMargin: 88
            anchors.left: parent.left
            anchors.leftMargin: 89
            font.family: "Arial"
            rotation: 0
            font.bold: false
            font.pointSize: 12
        }



}

/*##^## Designer {
    D{i:3;anchors_height:50;anchors_width:123;anchors_x:89;anchors_y:20}
}
 ##^##*/
