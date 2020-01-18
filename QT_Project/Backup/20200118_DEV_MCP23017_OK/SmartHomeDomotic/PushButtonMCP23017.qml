import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import io.qt.GlobalStyle 1.0

Item
{
    property alias pushButton: pushButton
    property alias labelPushButtonText: labelPushButton.text
    property alias pushButtonEnabled: pushButton.enabled

    property alias checkBoxOutputVisible: checkBoxOutput.visible
    property alias checkBoxOutputChecked: checkBoxOutput.checked

    property bool pushButtonPressed : false

    id: pushButtonMCP23017
    width: 80
    height: 30
    antialiasing: false
    clip: false

    onPushButtonEnabledChanged:
    {
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

    onCheckBoxOutputCheckedChanged:
    {
        console.log("onCheckBoxOutputCheckedChanged: " + checkBoxOutput.checked)

        setButtonAsOutput(checkBoxOutput.checked)
//        pushButtonEnabled = checkBoxInputChecked;
//        pushButton.visible = checkBoxInputChecked;
//        rectangleEnableOFF.visible = !checkBoxInputChecked
//        rectangleOff.visible = checkBoxInputChecked
    }

    function setButtonAsOutput(isOutput)
    {
        if(isOutput)
        {
            console.log("setButtonAsOutput: isOutput, value : " + isOutput)

            pushButtonEnabled = true;
            pushButton.visible = true;
            rectangleEnableOFF.visible = false
            rectangleOff.visible = true
            checkBoxOutput.checked = true

        }
        else
        {
            console.log("setButtonAsOutput: isOutput, value : " + isOutput)

            pushButtonEnabled = false;
            pushButton.visible = false;
            rectangleEnableOFF.visible = true
            rectangleOff.visible = false
            checkBoxOutput.checked = false
        }
    }

    function setLightOn(isInpoutOn)
    {
        console.log("setLightOn: " + isInpoutOn + " ,pushButtonEnabled: " + pushButtonEnabled)
        if(!pushButtonEnabled)
        {
            rectangleEnableOFF.visible = !isInpoutOn
            rectangleOn.visible = isInpoutOn
            rectangleOff.visible = !isInpoutOn

            if(isInpoutOn)
            {
                labelPushButton.color = GlobalStyle.pushButtonPoliceColorDarkGrey
            }
            else
            {
                labelPushButton.color = GlobalStyle.pushButtonPoliceColorWhite
            }
        }
        else
        {
            if(isInpoutOn)
            {
                labelPushButton.color = GlobalStyle.pushButtonPoliceColorWhite
            }
            else
            {
                labelPushButton.color = GlobalStyle.pushButtonPoliceColorDarkGrey
            }
        }
    }

    function setTitleText(Tiletext)
    {
        pushButtonText = Tiletext
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
                color: GlobalStyle.pbOFFgradientStopTop
            }

            GradientStop
            {
                position: 0.2
                color: GlobalStyle.pbOFFgradientStopMiddleTop
            }

            GradientStop
            {
                position: 0.8
                color: GlobalStyle.pbOFFgradientStopMiddleBottom
            }

            GradientStop
            {
                position: 1
                color: GlobalStyle.pbOFFgradientStopBottom
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
                color: GlobalStyle.pbONgradientStopTop
            }

            GradientStop {
                position: 0.2
                color: GlobalStyle.pbONgradientStopMiddleTop
            }

            GradientStop {
                position: 0.8
                color: GlobalStyle.pbONgradientStopMiddleBottom
            }

            GradientStop {
                position: 1
                color: GlobalStyle.pbONgradientStopBottom
            }
        }
    }




    Rectangle {
        id: rectangleEnableOFF
        x: 6
        y: -3
        radius: 2
        anchors.rightMargin: 0
        visible: true
        border.width: 1
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0
                color: GlobalStyle.pushButtonPoliceColorDarkGrey
            }

            GradientStop {
                position: 0.2
                color: GlobalStyle.pushButtonPoliceColorDarkGrey
            }

            GradientStop {
                position: 0.8
                color: GlobalStyle.pushButtonPoliceColorDarkGrey
            }

            GradientStop {
                position: 1
                color: GlobalStyle.pushButtonPoliceColorDarkGrey
            }
        }
    }

    Button {
        id: pushButton
        text: qsTr("23")
        enabled: false
        anchors.fill: parent
        opacity: 0
        visible: false
        highlighted: false
        autoRepeat: false
        autoExclusive: false
        checkable: true
        checked: false
        onPressed: {
            rectangleOn.visible = true
            rectangleOff.visible = false
            pushButtonPressed = true
        }
        onReleased: {
            rectangleOn.visible = false
            rectangleOff.visible = true
            pushButtonPressed = false
        }
    }


    Label {
        id: labelPushButton
        width: 50
        height: 50
        text: qsTr("Label")
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.rightMargin: 30
        leftPadding: 5
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        anchors.fill: parent
    }

    CheckBox {
        id: checkBoxOutput
        x: 50
        y: 0
        width: 30
        height: 30
        text: qsTr("")
        visible: false
    }
}
