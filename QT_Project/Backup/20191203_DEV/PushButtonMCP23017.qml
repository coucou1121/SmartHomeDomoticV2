import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import io.qt.globalStyle 1.0

Item
{
    property alias pushButton: pushButton
    property alias pushButtonChecked: pushButton.checked
    property alias labelPushButtonText: labelPushButton.text
    property alias pushButtonEnabled: pushButton.enabled

    id: pushButtonMCP23017
    width: 100
    height: 30
    antialiasing: false
    clip: false

    onPushButtonEnabledChanged: {
        if(pushButtonEnabled)
        {
            rectangleEnableOFF.visible = false
            rectangleOff.visible = true
        }
        else
        {
            rectangleEnableOFF.visible = true
            rectangleOff.visible = false
        }

        rectangleOn.visible = false

    }

    function setLightOn(isInpoutOn)
    {
//        console.log("setLightOn: " + isInpoutOn + " ,pushButtonEnabled: " + pushButtonEnabled)
        if(!pushButtonEnabled)
        {
            rectangleEnableOFF.visible = !isInpoutOn
            rectangleOn.visible = isInpoutOn
            rectangleOff.visible = !isInpoutOn
        }

        if(isInpoutOn)
        {
            labelPushButton.color = globalStyle.pushButtonPoliceColorDarkGrey
        }
        else
        {
            labelPushButton.color = globalStyle.pushButtonPoliceColorWhite
        }
    }

    function setTitleText(Tiletext)
    {
        pushButtonText = Tiletext
    }

    //    onPushButtonCheckedChanged:
    //    {
    //        rectangleOn.visible = pushButtonChecked ? true : false
    //        rectangleOff.visible = pushButtonChecked ? false : true
    //        //        logoLightOff.visible = rectangleOn.visible
    //        //        logoLightOn.visible = rectangleOff.visible
    //    }



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
        radius: 2
        anchors.fill: parent
        visible: false
        border.width: 1
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




    Rectangle {
        id: rectangleEnableOFF
        x: 6
        y: -3
        radius: 2
        visible: false
        border.width: 1
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0
                color: globalStyle.pushButtonPoliceColorDarkGrey
            }

            GradientStop {
                position: 0.2
                color: globalStyle.pushButtonPoliceColorDarkGrey
            }

            GradientStop {
                position: 0.8
                color: globalStyle.pushButtonPoliceColorDarkGrey
            }

            GradientStop {
                position: 1
                color: globalStyle.pushButtonPoliceColorDarkGrey
            }
        }
    }

    Button {
        id: pushButton
        text: qsTr("23")
        enabled: true
        anchors.fill: parent
        opacity: 0
        visible: true
        highlighted: false
        autoRepeat: false
        autoExclusive: false
        checkable: true
        checked: false
        onPressed: {
            rectangleOn.visible = true
            rectangleOff.visible = false
            labelPushButton.color = globalStyle.pushButtonPoliceColorDarkGrey
        }
        onReleased: {
            rectangleOn.visible = false
            rectangleOff.visible = true
            labelPushButton.color = globalStyle.pushButtonPoliceColorWhite
        }
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
