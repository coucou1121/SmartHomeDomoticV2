import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Item
{
    id: pushButtonLight
    width: 200
    height: 200
    antialiasing: false
    clip: false

    property alias pushButton: pushButton
    property alias pushButtonChecked: pushButton.checked

    function setLightOn(bool)
    {
        pushButtonChecked = bool
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
        radius: 20
        visible: true
        border.width: 5
        border.color: Material.color("ffffff")
        anchors.fill: parent
        gradient:
            Gradient
        {
            GradientStop
            {
                position: 0
                color: "#000000"
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
        x: 0
        y: 5
        radius: 20
        visible: false
        anchors.fill: parent
        border.width: 5
        border.color: Material.color("ffffff")
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
        text: qsTr("")
        opacity: 0
        visible: true
        anchors.fill: parent
        highlighted: false
        autoRepeat: false
        autoExclusive: false
        checkable: true
        checked: false
    }

    Image {
        id: logoLightOn
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent
        sourceSize.height: 150
        sourceSize.width: 150
        fillMode: Image.PreserveAspectFit
        smooth: true
        antialiasing: false
        visible: false
        source: "./Picture/lightBulbOn.png"
    }

    Image {
        id: logoLightOff
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent
        sourceSize.height: 150
        sourceSize.width: 150
        clip: false
        fillMode: Image.PreserveAspectFit
        visible: true
        source: "./Picture/lightBulbOff.png"
        antialiasing: true
    }
}

/*##^## Designer {
    D{i:15;anchors_height:200;anchors_width:200;anchors_x:0;anchors_y:0}
}
 ##^##*/
