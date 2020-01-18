import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.0

import io.qt.GlobalStyle 1.0

Item {

    signal sendIODIRregChanged(int deviceID, int regIODIRvalue)
    signal sendGPIOregChanged(int deviceID, int regPGIOvalue)

    property alias checkBoxSettingChecked: checkBoxSetting.checked

    property alias labelDeviceMCP23017Text: labelDeviceMCP23017.text

    property alias textIOdirText: textIOdir.text
    property alias textAddText: textAdd.text
    property alias textIDText: textID.text

    property alias button_GPA0PushButtonEnabled: button_GPA0.pushButtonEnabled
    property alias button_GPA1PushButtonEnabled: button_GPA1.pushButtonEnabled
    property alias button_GPA2PushButtonEnabled: button_GPA2.pushButtonEnabled
    property alias button_GPA3PushButtonEnabled: button_GPA3.pushButtonEnabled
    property alias button_GPA4PushButtonEnabled: button_GPA4.pushButtonEnabled
    property alias button_GPA5PushButtonEnabled: button_GPA5.pushButtonEnabled
    property alias button_GPA6PushButtonEnabled: button_GPA6.pushButtonEnabled
    property alias button_GPA7PushButtonEnabled: button_GPA7.pushButtonEnabled

    property alias button_GPB0PushButtonEnabled: button_GPB0.pushButtonEnabled
    property alias button_GPB1PushButtonEnabled: button_GPB1.pushButtonEnabled
    property alias button_GPB2PushButtonEnabled: button_GPB2.pushButtonEnabled
    property alias button_GPB3PushButtonEnabled: button_GPB3.pushButtonEnabled
    property alias button_GPB4PushButtonEnabled: button_GPB4.pushButtonEnabled
    property alias button_GPB5PushButtonEnabled: button_GPB5.pushButtonEnabled
    property alias button_GPB6PushButtonEnabled: button_GPB6.pushButtonEnabled
    property alias button_GPB7PushButtonEnabled: button_GPB7.pushButtonEnabled

    property alias button_GPA0checkBoxOutputChecked: button_GPA0.checkBoxOutputChecked
    property alias button_GPA1checkBoxOutputChecked: button_GPA1.checkBoxOutputChecked
    property alias button_GPA2checkBoxOutputChecked: button_GPA2.checkBoxOutputChecked
    property alias button_GPA3checkBoxOutputChecked: button_GPA3.checkBoxOutputChecked
    property alias button_GPA4checkBoxOutputChecked: button_GPA4.checkBoxOutputChecked
    property alias button_GPA5checkBoxOutputChecked: button_GPA5.checkBoxOutputChecked
    property alias button_GPA6checkBoxOutputChecked: button_GPA6.checkBoxOutputChecked
    property alias button_GPA7checkBoxOutputChecked: button_GPA7.checkBoxOutputChecked

    property alias button_GPB0checkBoxOutputChecked: button_GPB0.checkBoxOutputChecked
    property alias button_GPB1checkBoxOutputChecked: button_GPB1.checkBoxOutputChecked
    property alias button_GPB2checkBoxOutputChecked: button_GPB2.checkBoxOutputChecked
    property alias button_GPB3checkBoxOutputChecked: button_GPB3.checkBoxOutputChecked
    property alias button_GPB4checkBoxOutputChecked: button_GPB4.checkBoxOutputChecked
    property alias button_GPB5checkBoxOutputChecked: button_GPB5.checkBoxOutputChecked
    property alias button_GPB6checkBoxOutputChecked: button_GPB6.checkBoxOutputChecked
    property alias button_GPB7checkBoxOutputChecked: button_GPB7.checkBoxOutputChecked

    property alias button_GPA0PushButtonPressed: button_GPA0.pushButtonPressed
    property alias button_GPA1PushButtonPressed: button_GPA1.pushButtonPressed
    property alias button_GPA2PushButtonPressed: button_GPA2.pushButtonPressed
    property alias button_GPA3PushButtonPressed: button_GPA3.pushButtonPressed
    property alias button_GPA4PushButtonPressed: button_GPA4.pushButtonPressed
    property alias button_GPA5PushButtonPressed: button_GPA5.pushButtonPressed
    property alias button_GPA6PushButtonPressed: button_GPA6.pushButtonPressed
    property alias button_GPA7PushButtonPressed: button_GPA7.pushButtonPressed

    property alias button_GPB0PushButtonPressed: button_GPB0.pushButtonPressed
    property alias button_GPB1PushButtonPressed: button_GPB1.pushButtonPressed
    property alias button_GPB2PushButtonPressed: button_GPB2.pushButtonPressed
    property alias button_GPB3PushButtonPressed: button_GPB3.pushButtonPressed
    property alias button_GPB4PushButtonPressed: button_GPB4.pushButtonPressed
    property alias button_GPB5PushButtonPressed: button_GPB5.pushButtonPressed
    property alias button_GPB6PushButtonPressed: button_GPB6.pushButtonPressed
    property alias button_GPB7PushButtonPressed: button_GPB7.pushButtonPressed

    property int regIODIR: 0x0000
    property int regGPIO: 0x0000
    property int deviceID: 0

    function setregIODIR(value)
    {
        regIODIR = value
        console.log("setregIODIR: " + value.toString(2))

        //        checkBoxSettingChecked = true
        button_GPA0checkBoxOutputChecked = ((~value >> 0) & 0x0001)
        button_GPA1checkBoxOutputChecked = ((~value >> 1) & 0x0001)
        button_GPA2checkBoxOutputChecked = ((~value >> 2) & 0x0001)
        button_GPA3checkBoxOutputChecked = ((~value >> 3) & 0x0001)
        button_GPA4checkBoxOutputChecked = ((~value >> 4) & 0x0001)
        button_GPA5checkBoxOutputChecked = ((~value >> 5) & 0x0001)
        button_GPA6checkBoxOutputChecked = ((~value >> 6) & 0x0001)
        button_GPA7checkBoxOutputChecked = ((~value >> 7) & 0x0001)
        button_GPB0checkBoxOutputChecked = ((~value >> 8) & 0x0001)
        button_GPB1checkBoxOutputChecked = ((~value >> 9) & 0x0001)
        button_GPB2checkBoxOutputChecked = ((~value >> 10) & 0x0001)
        button_GPB3checkBoxOutputChecked = ((~value >> 11) & 0x0001)
        button_GPB4checkBoxOutputChecked = ((~value >> 12) & 0x0001)
        button_GPB5checkBoxOutputChecked = ((~value >> 13) & 0x0001)
        button_GPB6checkBoxOutputChecked = ((~value >> 14) & 0x0001)
        button_GPB7checkBoxOutputChecked = ((~value >> 15) & 0x0001)
        //        checkBoxSettingChecked = false

    }

    function setregGPIO(value)
    {
        console.log("setregGPIO: " + value.toString(2))
        regGPIO = value
    }

    function setID(value)
    {
        textIDText = value
    }

    function setAdd(value)
    {
        textAddText = value
    }

    function setIODir(value)
    {
        textIOdirText = value
    }

    onRegGPIOChanged:
    {
        var regGPIOinv = ~regGPIO
        button_GPA0.setLightOn(regGPIOinv & 0x0001)
        button_GPA1.setLightOn((regGPIOinv >> 1) & 0x0001)
        button_GPA2.setLightOn((regGPIOinv >> 2) & 0x0001)
        button_GPA3.setLightOn((regGPIOinv >> 3) & 0x0001)
        button_GPA4.setLightOn((regGPIOinv >> 4) & 0x0001)
        button_GPA5.setLightOn((regGPIOinv >> 5) & 0x0001)
        button_GPA6.setLightOn((regGPIOinv >> 6) & 0x0001)
        button_GPA7.setLightOn((regGPIOinv >> 7) & 0x0001)
        button_GPB0.setLightOn((regGPIOinv >> 8) & 0x0001)
        button_GPB1.setLightOn((regGPIOinv >> 9) & 0x0001)
        button_GPB2.setLightOn((regGPIOinv >> 10) & 0x0001)
        button_GPB3.setLightOn((regGPIOinv >> 11) & 0x0001)
        button_GPB4.setLightOn((regGPIOinv >> 12) & 0x0001)
        button_GPB5.setLightOn((regGPIOinv >> 13) & 0x0001)
        button_GPB6.setLightOn((regGPIOinv >> 14) & 0x0001)
        button_GPB7.setLightOn((regGPIOinv >> 15) & 0x0001)
    }

    onRegIODIRChanged:
    {
        console.log("onRegIODIRChanged: " + regIODIR.toString(2))
        sendIODIRregChanged(deviceID, regIODIR)
    }

    onCheckBoxSettingCheckedChanged:
    {
        button_GPA0.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPA1.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPA2.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPA3.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPA4.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPA5.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPA6.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPA7.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPB0.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPB1.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPB2.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPB3.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPB4.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPB5.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPB6.checkBoxOutputVisible = checkBoxSettingChecked
        button_GPB7.checkBoxOutputVisible = checkBoxSettingChecked
    }

    onButton_GPA0PushButtonEnabledChanged:
    {
        regIODIR = button_GPA0.checkBoxOutputChecked ?  regIODIR & ~(1 << 0) : regIODIR | (1 << 0)
        console.log("onButton_GPA0PushButtonEnabledChanged: " + regIODIR.toString(2))
    }

    onButton_GPA1PushButtonEnabledChanged:
    {
        regIODIR = button_GPA1.checkBoxOutputChecked ?  regIODIR & ~(1 << 1) : regIODIR | (1 << 1)
        //        console.log("onButton_GPA1PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPA2PushButtonEnabledChanged:
    {
        regIODIR = button_GPA2.checkBoxOutputChecked ?  regIODIR & ~(1 << 2) : regIODIR | (1 << 2)
        //        console.log("onButton_GPA2PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPA3PushButtonEnabledChanged:
    {
        regIODIR = button_GPA3.checkBoxOutputChecked ?  regIODIR & ~(1 << 3) : regIODIR | (1 << 3)
        //        console.log("onButton_GPA3PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPA4PushButtonEnabledChanged:
    {
        regIODIR = button_GPA4.checkBoxOutputChecked ?  regIODIR & ~(1 << 4) :regIODIR | (1 << 4)
        //        console.log("onButton_GPA4PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPA5PushButtonEnabledChanged:
    {
        regIODIR = button_GPA5.checkBoxOutputChecked ?  regIODIR & ~(1 << 5) :regIODIR | (1 << 5)
        //        console.log("onButton_GPA5PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPA6PushButtonEnabledChanged:
    {
        regIODIR = button_GPA6.checkBoxOutputChecked ?  regIODIR & ~(1 << 6) :regIODIR | (1 << 6)
        //        console.log("onButton_GPA6PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPA7PushButtonEnabledChanged:
    {
        regIODIR = button_GPA7.checkBoxOutputChecked ?  regIODIR & ~(1 << 7) :regIODIR | (1 << 7)
        //        console.log("onButton_GPA7PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPB0PushButtonEnabledChanged:
    {
        regIODIR = button_GPB0.checkBoxOutputChecked ?  regIODIR & ~(1 << 8) : regIODIR | (1 << 8)
        //        console.log("onButton_GPB0PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPB1PushButtonEnabledChanged:
    {
        regIODIR = button_GPB1.checkBoxOutputChecked ?  regIODIR & ~(1 << 9) :regIODIR | (1 << 9)
        //        console.log("onButton_GPA0PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPB2PushButtonEnabledChanged:
    {
        regIODIR = button_GPB2.checkBoxOutputChecked ?  regIODIR & ~(1 << 10) : regIODIR | (1 << 10)
        //        console.log("onButton_GPB2PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPB3PushButtonEnabledChanged:
    {
        regIODIR = button_GPB3.checkBoxOutputChecked ? regIODIR & ~(1 << 11) :  regIODIR | (1 << 11)
        //        console.log("onButton_GPB3PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPB4PushButtonEnabledChanged:
    {
        regIODIR = button_GPB4.checkBoxOutputChecked ? regIODIR & ~(1 << 12) : regIODIR | (1 << 12)
        //        console.log("onButton_GPB4PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPB5PushButtonEnabledChanged:
    {
        regIODIR = button_GPB5.checkBoxOutputChecked ?  regIODIR & ~(1 << 13) :regIODIR | (1 << 13)
        //        console.log("onButton_GPB5PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPB6PushButtonEnabledChanged:
    {
        regIODIR = button_GPB6.checkBoxOutputChecked ? regIODIR & ~(1 << 14) : regIODIR | (1 << 14)
        //        console.log("onButton_GPB6PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPB7PushButtonEnabledChanged:
    {
        regIODIR = button_GPB7.checkBoxOutputChecked ?  regIODIR & ~(1 << 15) : regIODIR | (1 << 15)
        //        console.log("onButton_GPB7PushButtonEnabledChanged: " + regIODIR)
    }

    onButton_GPA0PushButtonPressedChanged:
    {
        regGPIO = button_GPA0.pushButtonPressed ?  regGPIO | (1 << 0) : regGPIO & ~(1 << 0)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPA0PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPA1PushButtonPressedChanged:
    {
        regGPIO = button_GPA1.pushButtonPressed ?  regGPIO | (1 << 1) : regGPIO & ~(1 << 1)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPA1PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPA2PushButtonPressedChanged:
    {
        regGPIO = button_GPA2.pushButtonPressed ?  regGPIO | (1 << 2) : regGPIO & ~(1 << 2)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPA2PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPA3PushButtonPressedChanged:
    {
        regGPIO = button_GPA3.pushButtonPressed ?  regGPIO | (1 << 3) : regGPIO & ~(1 << 3)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPA3PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPA4PushButtonPressedChanged:
    {
        regGPIO = button_GPA4.pushButtonPressed ?  regGPIO | (1 << 4) : regGPIO & ~(1 << 4)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPA4PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPA5PushButtonPressedChanged:
    {
        regGPIO = button_GPA5.pushButtonPressed ?  regGPIO | (1 << 5) : regGPIO & ~(1 << 5)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPA5PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPA6PushButtonPressedChanged:
    {
        regGPIO = button_GPA6.pushButtonPressed ?  regGPIO | (1 << 6) : regGPIO & ~(1 << 6)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPA6PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPA7PushButtonPressedChanged:
    {
        regGPIO = button_GPA7.pushButtonPressed ?  regGPIO | (1 << 7) : regGPIO & ~(1 << 7)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPA7PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPB0PushButtonPressedChanged:
    {
        regGPIO = button_GPB0.pushButtonPressed ?  regGPIO | (1 << 8) : regGPIO & ~(1 << 8)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPB0PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPB1PushButtonPressedChanged:
    {
        regGPIO = button_GPB1.pushButtonPressed ?  regGPIO | (1 << 9) : regGPIO & ~(1 << 9)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPB1PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPB2PushButtonPressedChanged:
    {
        regGPIO = button_GPB2.pushButtonPressed ?  regGPIO | (1 << 10) : regGPIO & ~(1 << 10)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPB2PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPB3PushButtonPressedChanged:
    {
        regGPIO = button_GPB3.pushButtonPressed ?  regGPIO | (1 << 11) : regGPIO & ~(1 << 11)
        console.log("onButton_GPB3PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPB4PushButtonPressedChanged:
    {
        regGPIO = button_GPB4.pushButtonPressed ?  regGPIO | (1 << 12) : regGPIO & ~(1 << 12)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPB4PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPB5PushButtonPressedChanged:
    {
        regGPIO = button_GPB5.pushButtonPressed ?  regGPIO | (1 << 13) : regGPIO & ~(1 << 13)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPB5PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPB6PushButtonPressedChanged:
    {
        regGPIO = button_GPB6.pushButtonPressed ?  regGPIO | (1 << 14) : regGPIO & ~(1 << 14)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPB6PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    onButton_GPB7PushButtonPressedChanged:
    {
        regGPIO = button_GPB7.pushButtonPressed ?  regGPIO | (1 << 15) : regGPIO & ~(1 << 15)
        sendGPIOregChanged(deviceID, regGPIO)
        console.log("onButton_GPB7PushButtonPressedChanged: " + regGPIO.toString(2))
    }

    id: item1
    width: 240
    height: 300

    LabelDevice {
        id: labelDeviceMCP23017
        y: 0
        height: 20
        text: "Title"
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        Layout.preferredWidth: 120
        Layout.fillWidth: true
        Layout.rowSpan: 1
        verticalAlignment: Text.AlignBottom
        Layout.maximumWidth: 120
        Layout.fillHeight: false
        font.pointSize: GlobalStyle.textfontSizeBig
        Layout.minimumWidth: 120
        visible: true
        Layout.preferredHeight: 50
    }

    Frame {
        id: frame
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.top: labelDeviceMCP23017.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 6
        rightPadding: 5
        bottomPadding: 2
        leftPadding: 5
        topPadding: 0





        GridLayout {
            columnSpacing: 3
            rowSpacing: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            rows: 8
            columns: 3

            PushButtonMCP23017 {
                id: button_GPB0
                width: 80
                objectName: "button_GPB0"
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB0"
            }

            Frame {
                id: frameID
                width: 54
                Layout.rowSpan: 2
                Layout.preferredHeight: 65
                Layout.preferredWidth: 50
                leftPadding: 2
                rightPadding: 2
                bottomPadding: 2
                topPadding: 2

                LabelDevice {
                    id: labelDeviceMCP23017ID
                    width: 58
                    height: 16
                    text: "ID"
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.horizontalCenterOffset: 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.fillWidth: true
                    Layout.preferredWidth: 120
                    Layout.rowSpan: 1
                    verticalAlignment: Text.AlignBottom
                    Layout.maximumWidth: 120
                    Layout.fillHeight: false
                    font.pointSize: GlobalStyle.textfontSizeMed
                    Layout.minimumWidth: 120
                    visible: true
                    Layout.preferredHeight: 50
                }

                Text {
                    id: textID
                    color: GlobalStyle.policeColorWhite
                    text: qsTr("")
                    font.pointSize: GlobalStyle.textfontSizeSmall
                    anchors.top: labelDeviceMCP23017ID.bottom
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 15
                }
            }

            PushButtonMCP23017 {
                id: button_GPA0
                pushButtonPressed: false
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA0"
                objectName: "button_GPA0"
            }

            PushButtonMCP23017 {
                id: button_GPB1
                pushButtonEnabled: false
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                objectName: "button_GPB1"
                labelPushButtonText: "GPB1"
            }

            PushButtonMCP23017 {
                id: button_GPA1
                pushButtonPressed: false
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA1"
                objectName: "button_GPA1"
            }

            PushButtonMCP23017 {
                id: button_GPB2
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB2"
                objectName: "button_GPB2"
            }

            Frame {
                id: frameIAdd
                width: 54
                Layout.rowSpan: 2
                Layout.preferredHeight: 67
                Layout.preferredWidth: 50
                leftPadding: 2
                rightPadding: 2
                bottomPadding: 2
                topPadding: 2
                LabelDevice {
                    id: labelDeviceMCP23017Add
                    width: 58
                    height: 16
                    text: "Add"
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.maximumWidth: 120
                    Layout.preferredWidth: 120
                    verticalAlignment: Text.AlignBottom
                    Layout.preferredHeight: 50
                    font.pointSize: GlobalStyle.textfontSizeMed
                    Layout.minimumWidth: 120
                    Layout.rowSpan: 1
                    visible: true
                }

                Text {
                    id: textAdd
                    color: GlobalStyle.policeColorWhite
                    text: qsTr("")
                    font.pointSize: GlobalStyle.textfontSizeSmall
                    anchors.top: labelDeviceMCP23017Add.bottom
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 15
                }
            }

            PushButtonMCP23017 {
                id: button_GPA2
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA2"
                objectName: "button_GPA2"
            }

            PushButtonMCP23017 {
                id: button_GPB3
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB3"
                objectName: "button_GPB3"
            }

            PushButtonMCP23017 {
                id: button_GPA3
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA3"
                objectName: "button_GPA3"
            }

            PushButtonMCP23017 {
                id: button_GPB4
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB4"
                objectName: "button_GPB4"
            }

            Frame {
                id: frameIIOdir
                width: 54
                topPadding: 2
                rightPadding: 2
                LabelDevice {
                    id: labelDeviceMCP23017IOdir
                    width: 58
                    height: 16
                    text: "IOreg"
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    visible: true
                    font.pointSize: GlobalStyle.textfontSizeMed
                    Layout.fillWidth: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.maximumWidth: 120
                    verticalAlignment: Text.AlignBottom
                    Layout.fillHeight: false
                    Layout.minimumWidth: 120
                    Layout.rowSpan: 1
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: 120
                }

                Text {
                    id: textIOdir
                    color: GlobalStyle.policeColorWhite
                    text: qsTr("")
                    font.pointSize: GlobalStyle.textfontSizeSmall
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: labelDeviceMCP23017IOdir.bottom
                    anchors.left: parent.left
                    Layout.preferredHeight: 15
                    Layout.preferredWidth: 30
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                }
                Layout.rowSpan: 2
                Layout.preferredHeight: 66
                Layout.preferredWidth: 50
                leftPadding: 2
                bottomPadding: 2
            }

            PushButtonMCP23017 {
                id: button_GPA4
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA4"
                objectName: "button_GPA4"
            }

            PushButtonMCP23017 {
                id: button_GPB5
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB5"
                objectName: "button_GPB5"
            }

            PushButtonMCP23017 {
                id: button_GPA5
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA5"
                objectName: "button_GPA5"
            }

            PushButtonMCP23017 {
                id: button_GPB6
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB6"
                objectName: "button_GPB6"
            }

            Frame {
                id: frameIIOSetup
                width: 54
                Layout.rowSpan: 2
                LabelDevice {
                    id: labelDeviceMCP23017Setup
                    width: 58
                    height: 16
                    text: "Setting"
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    Layout.maximumWidth: 120
                    Layout.rowSpan: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.preferredHeight: 50
                    font.pointSize: GlobalStyle.textfontSizeMed
                    verticalAlignment: Text.AlignBottom
                    Layout.minimumWidth: 120
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.preferredWidth: 120
                    visible: true
                }

                CheckBox {
                    id: checkBoxSetting
                    x: 8
                    y: 24
                    width: 30
                    height: 30
                    text: qsTr("")
                }

                Layout.preferredHeight: 65
                topPadding: 2
                rightPadding: 2
                bottomPadding: 2
                Layout.preferredWidth: 50
                leftPadding: 2
            }

            PushButtonMCP23017 {
                id: button_GPA6
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA6"
                objectName: "button_GPA6"
            }

            PushButtonMCP23017 {
                id: button_GPB7
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB7"
                objectName: "button_GPB7"
            }

            PushButtonMCP23017 {
                id: button_GPA7
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA7"
                objectName: "button_GPA7"
            }
        }

    }


}

/*##^## Designer {
    D{i:39;anchors_height:16;anchors_width:58;anchors_x:0;anchors_y:2}
}
 ##^##*/
