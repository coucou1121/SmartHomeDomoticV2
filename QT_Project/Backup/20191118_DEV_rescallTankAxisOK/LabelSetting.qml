import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Label
{
    property alias textEditText: textInput.text
    property alias labelVisible: label.visible

    id: label
    width: 300
    height: 50
    color:  Material.color(Material.Purple)
    text: "title"
    visible: true
    font.family: "Arial"
    topPadding: 0
    padding: 5
    rotation: 0
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignLeft
    font.bold: false
    font.pointSize: 22

    Rectangle {
        id: rectangle
        color: "#e6e6e6"
        z: -1
        anchors.leftMargin: 0
        opacity: 1
        border.width: 0
        anchors.fill: parent
    }

    Rectangle
    {
        id: rectangle1
        x: 150
        y: 8
        color: "#ffffff"
        anchors.bottomMargin: 5
        anchors.rightMargin: 5
        anchors.topMargin: 5
        anchors.leftMargin: 130
        z: 0
        anchors.fill: parent

        TextInput
        {
            // Store the previous text for restoring it if we cancel
            property string oldText

            // Lets us know that the user is cancelling the save
            property bool cancelling

            id: textInput
            width: 165
            text: "text"
            font.family: "Arial"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 3
            z: 1
            font.pixelSize: 22
            //validator: IntValidator{ bottom: 1; top: 30000}

            Keys.onEscapePressed: {
                // Cancel the save, and deselect the text input
                cancelling = true
                focus = false
            }

            onEditingFinished: {
                if (cancelling) {
                    // When cancelling, restore the old text, and clear state.
                    text = oldText
                    oldText = ""
                    cancelling = false
                } else {
                    // TO DO: Handle new text
                }
            }

            onActiveFocusChanged: {
                // When we first gain focus, save the old text and select everything for clearing.
                if (activeFocus) {
                    oldText = text
                    selectAll()
                }
            }
        }
    }

}
