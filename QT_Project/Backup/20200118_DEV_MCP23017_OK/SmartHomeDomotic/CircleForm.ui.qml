import QtQuick 2.4

Item {
    width: 200
    height: 200
    property alias buttonColor: button.color
    property alias displayText: display.text

    Rectangle {
        id: button
        color: "#d54e4e"
        radius: width*0.5
        anchors.fill: parent

        Text {
            id: display
            x: 59
            y: 75
            text: qsTr("Text")
            font.pixelSize: 42
        }
    }
}
