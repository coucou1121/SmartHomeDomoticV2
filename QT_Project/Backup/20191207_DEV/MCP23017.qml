import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.0

import io.qt.GlobalStyle 1.0

Item {
    id: item1
    width: 240
    height: 300
    property alias checkBoxSettingChecked: checkBoxSetting.checked

    property alias labelDeviceMCP23017Text: labelDeviceMCP23017.text
    property alias textIIOdirText: textIIOdir.text

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

    property int regIODIR: 0xFFFF

    function setRegIODIR(value, valueTxt)
    {
        //        console.log("setRegIODIR: " + value)
        regIODIR = value
        textIIOdirText = valueTxt
    }

    function setAllInpout(inputsValue)
    {
        //        console.log("setAllInpout: " + inputsValue)

        button_GPA0.setLightOn(inputsValue & 0x0001)
        button_GPA1.setLightOn((inputsValue >> 1) & 0x0001)
        button_GPA2.setLightOn((inputsValue >> 2) & 0x0001)
        button_GPA3.setLightOn((inputsValue >> 3) & 0x0001)
        button_GPA4.setLightOn((inputsValue >> 4) & 0x0001)
        button_GPA5.setLightOn((inputsValue >> 5) & 0x0001)
        button_GPA6.setLightOn((inputsValue >> 6) & 0x0001)
        button_GPA7.setLightOn((inputsValue >> 7) & 0x0001)
        button_GPB0.setLightOn((inputsValue >> 8) & 0x0001)
        button_GPB1.setLightOn((inputsValue >> 9) & 0x0001)
        button_GPB2.setLightOn((inputsValue >> 10) & 0x0001)
        button_GPB3.setLightOn((inputsValue >> 11) & 0x0001)
        button_GPB4.setLightOn((inputsValue >> 12) & 0x0001)
        button_GPB5.setLightOn((inputsValue >> 13) & 0x0001)
        button_GPB6.setLightOn((inputsValue >> 14) & 0x0001)
        button_GPB7.setLightOn((inputsValue >> 15) & 0x0001)
    }

    onRegIODIRChanged:
    {
        button_GPA0PushButtonEnabled = regIODIR & 0x0001
        button_GPA1PushButtonEnabled = (regIODIR >> 1) & 0x0001
        button_GPA2PushButtonEnabled = (regIODIR >> 2) & 0x0001
        button_GPA3PushButtonEnabled = (regIODIR >> 3) & 0x0001
        button_GPA4PushButtonEnabled = (regIODIR >> 4) & 0x0001
        button_GPA5PushButtonEnabled = (regIODIR >> 5) & 0x0001
        button_GPA6PushButtonEnabled = (regIODIR >> 6) & 0x0001
        button_GPA7PushButtonEnabled = (regIODIR >> 7) & 0x0001
        button_GPB0PushButtonEnabled = (regIODIR >> 8) & 0x0001
        button_GPB1PushButtonEnabled = (regIODIR >> 9) & 0x0001
        button_GPB2PushButtonEnabled = (regIODIR >> 10) & 0x0001
        button_GPB3PushButtonEnabled = (regIODIR >> 11) & 0x0001
        button_GPB4PushButtonEnabled = (regIODIR >> 12) & 0x0001
        button_GPB5PushButtonEnabled = (regIODIR >> 13) & 0x0001
        button_GPB6PushButtonEnabled = (regIODIR >> 14) & 0x0001
        button_GPB7PushButtonEnabled = (regIODIR >> 15) & 0x0001
    }

    onCheckBoxSettingCheckedChanged:
    {
        button_GPA0.checkBoxInputVisible = checkBoxSettingChecked
        button_GPA1.checkBoxInputVisible = checkBoxSettingChecked
        button_GPA2.checkBoxInputVisible = checkBoxSettingChecked
        button_GPA3.checkBoxInputVisible = checkBoxSettingChecked
        button_GPA4.checkBoxInputVisible = checkBoxSettingChecked
        button_GPA5.checkBoxInputVisible = checkBoxSettingChecked
        button_GPA6.checkBoxInputVisible = checkBoxSettingChecked
        button_GPA7.checkBoxInputVisible = checkBoxSettingChecked
        button_GPB0.checkBoxInputVisible = checkBoxSettingChecked
        button_GPB1.checkBoxInputVisible = checkBoxSettingChecked
        button_GPB2.checkBoxInputVisible = checkBoxSettingChecked
        button_GPB3.checkBoxInputVisible = checkBoxSettingChecked
        button_GPB4.checkBoxInputVisible = checkBoxSettingChecked
        button_GPB5.checkBoxInputVisible = checkBoxSettingChecked
        button_GPB6.checkBoxInputVisible = checkBoxSettingChecked
        button_GPB7.checkBoxInputVisible = checkBoxSettingChecked
    }

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
        font.pointSize: 10
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
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.fillWidth: true
                    Layout.preferredWidth: 120
                    Layout.rowSpan: 1
                    verticalAlignment: Text.AlignBottom
                    Layout.maximumWidth: 120
                    Layout.fillHeight: false
                    font.pointSize: 10
                    Layout.minimumWidth: 120
                    visible: true
                    Layout.preferredHeight: 50
                }

                Text {
                    id: textID
                    color: GlobalStyle.policeColorWhite
                    text: qsTr("")
                    anchors.top: labelDeviceMCP23017ID.bottom
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 15
                    font.pixelSize: 10
                }
            }

            PushButtonMCP23017 {
                id: button_GPA0
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA0"
                objectName: "button_GPA0"
            }

            PushButtonMCP23017 {
                id: button_GPB1
                pushButtonEnabled: true
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                objectName: "button_GPB1"
                labelPushButtonText: "GPB1"
            }

            PushButtonMCP23017 {
                id: button_GPA1
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
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.maximumWidth: 120
                    Layout.preferredWidth: 120
                    verticalAlignment: Text.AlignBottom
                    Layout.preferredHeight: 50
                    font.pointSize: 10
                    Layout.minimumWidth: 120
                    Layout.rowSpan: 1
                    visible: true
                }

                Text {
                    id: textIAdd
                    color: GlobalStyle.policeColorWhite
                    text: qsTr("")
                    anchors.top: labelDeviceMCP23017Add.bottom
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 30
                    font.pixelSize: 10
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
                topPadding: 2
                rightPadding: 2
                LabelDevice {
                    id: labelDeviceMCP23017IOdir
                    width: 58
                    height: 16
                    text: "IOreg"
                    visible: true
                    font.pointSize: 10
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
                    id: textIIOdir
                    color: GlobalStyle.policeColorWhite
                    text: qsTr("")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 10
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
                Layout.rowSpan: 2
                LabelDevice {
                    id: labelDeviceMCP23017Setup
                    width: 58
                    height: 16
                    text: "Setting"
                    Layout.maximumWidth: 120
                    Layout.rowSpan: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.preferredHeight: 50
                    font.pointSize: 10
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
