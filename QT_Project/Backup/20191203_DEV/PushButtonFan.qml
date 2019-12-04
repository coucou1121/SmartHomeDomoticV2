import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import io.qt.globalStyle 1.0

Item
{
    id: pushButtonFan
    width: 200
    height: 200
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
        logoFanOff.visible = rectangleOn.visible
        logoFanOn.visible = rectangleOff.visible
    }

    Rectangle {
        id: rectangleOff
        radius: 20
        visible: true
        border.width: 5
        border.color: globalStyle.pbBorderColorBlue
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
        border.color: globalStyle.pbBorderColorBlue
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
            logoFanOn.visible = true
            logoFanOff.visible = false
        }
        onReleased: {
            rectangleOn.visible = false
            rectangleOff.visible = true
            logoFanOn.visible = false
            logoFanOff.visible = true
        }
    }

    Image {
        id: logoFanOn
        sourceSize.height: 250
        sourceSize.width: 250
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "Picture/fanOn.png"
    }

    Image {
        id: logoFanOff
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent
        visible: false
        fillMode: Image.PreserveAspectFit
        source: "Picture/fanOff.png"
    }
}
