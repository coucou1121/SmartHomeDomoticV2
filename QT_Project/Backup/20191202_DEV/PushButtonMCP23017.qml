import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Item
{
    property alias pushButton: pushButton
    property alias pushButtonChecked: pushButton.checked

    id: pushButtonMCP23017
    width: 100
    height: 30
    property alias labelPushButtonText: labelPushButton.text
    antialiasing: false
    clip: false


    function setLightOn(bool)
    {
        pushButtonChecked = bool
    }

    function setTitleText(Tiletext)
    {
        pushButtonText = Tiletext
    }

    onPushButtonCheckedChanged:
    {
        rectangleOn.visible = pushButtonChecked ? true : false
        rectangleOff.visible = pushButtonChecked ? false : true
        //        logoLightOff.visible = rectangleOn.visible
        //        logoLightOn.visible = rectangleOff.visible
    }


    Rectangle {
        id: rectangleOff
        radius: 2
        anchors.fill: parent
        visible: true
        border.width: 1
        gradient:
            Gradient
        {
            GradientStop
            {
                position: 0
                color: "#ffffff"
            }

            GradientStop
            {
                position: 0.2
                color: "#343434"
            }

            GradientStop
            {
                position: 0.8
                color: "#363636"
            }

            GradientStop
            {
                position: 1
                color: "#000000"
            }



        }
    }

    Rectangle {
        id: rectangleOn
        radius: 2
        anchors.fill: parent
        visible: false
        border.width: 1
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#605a00"
            }

            GradientStop {
                position: 0.2
                color: "#fffba9"
            }

            GradientStop {
                position: 0.8
                color: "#fffba9"
            }

            GradientStop {
                position: 1
                color: "#605a00"
            }
        }
    }




    Button {
        id: pushButton
        text: qsTr("23")
        anchors.fill: parent
        opacity: 0
        visible: true
        highlighted: false
        autoRepeat: false
        autoExclusive: false
        checkable: true
        checked: false
    }

    Label {
        id: labelPushButton
        width: 50
        height: 50
        text: qsTr("Label")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.fill: parent
    }
}
