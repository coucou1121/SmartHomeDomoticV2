import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Label
{
    property alias numberInputValue: numberInput.value
    property alias labelNumberText: labelNumber.text
    property alias numberInputStepSize: numberInput.stepSize
    property alias numberInputFrom: numberInput.from
    property alias numberInputTo: numberInput.to

    function decreaseNumber()
    {
        numberInput.decrease()
    }

    function increaseNumber()
    {
        numberInput.increase()
    }

    id: labelNumber
    width: 300
    height: 70
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

    SpinBox {

        // Store the previous text for restoring it if we cancel
        property int oldText

        // Lets us know that the user is cancelling the save
        property bool cancelling

        id: numberInput

        x: 130
        y: 5
        z: 2


        height: 50
        anchors.right: parent.right
        value: numberInput.value

        anchors.horizontalCenterOffset: -1
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 28


        from: 0
        stepSize: 100
        to: 5000

        }



}

/*##^## Designer {
    D{i:5;anchors_width:300}
}
 ##^##*/
