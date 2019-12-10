import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import io.qt.globalStyle 1.0

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

//    onPushButtonCheckedChanged:
//    {
//        rectangleOn.visible = pushButtonChecked ? true : false
//        rectangleOff.visible = pushButtonChecked ? false : true
////        logoLightOff.visible = rectangleOn.visible
////        logoLightOn.visible = rectangleOff.visible
//    }

    Rectangle {
        id: rectangleOff
        radius: 20
        visible: true
        border.width: 5
        border.color: globalStyle.pbBorderColorYellow
        anchors.fill: parent
        gradient:
            Gradient
        {
            GradientStop
            {
                position: 0
                color: globalStyle.pbOFFgradientStopTop
            }

            GradientStop
            {
                position: 0.2
                color: globalStyle.pbOFFgradientStopMiddleTop
            }

            GradientStop
            {
                position: 0.8
                color: globalStyle.pbOFFgradientStopMiddleBottom
            }

            GradientStop
            {
                position: 1
                color: globalStyle.pbOFFgradientStopBottom
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
        border.color: globalStyle.pbBorderColorYellow
        gradient: Gradient {
            GradientStop {
                position: 0
                color: globalStyle.pbONgradientStopTop
            }

            GradientStop {
                position: 0.2
                color: globalStyle.pbONgradientStopMiddleTop
            }

            GradientStop {
                position: 0.8
                color: globalStyle.pbONgradientStopMiddleBottom
            }

            GradientStop {
                position: 1
                color: globalStyle.pbONgradientStopBottom
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
        onPressed: {
            rectangleOn.visible = true
            rectangleOff.visible = false
        }
        onReleased: {
            rectangleOn.visible = false
            rectangleOff.visible = true
        }

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
