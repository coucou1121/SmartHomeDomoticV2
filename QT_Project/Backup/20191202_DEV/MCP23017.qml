import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.0

import io.qt.globalStyle 1.0

Item {
    width: 240
    height: 300


    LabelDevice {
        id: labelDeviceMCP23017_1
        x: 84
        y: 0
        width: 72
        height: 20
        text: "Title"
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
        anchors.top: labelDeviceMCP23017_1.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 6
        rightPadding: 5
        bottomPadding: 2
        leftPadding: 5
        topPadding: 0





        GridLayout {
            anchors.fill: parent
            columnSpacing: 2
            rowSpacing: 2
            rows: 8
            columns: 3

            PushButtonMCP23017 {
                id: button_GPB0
                Layout.fillHeight: false
                Layout.fillWidth: false
                objectName: "button_GPB0"
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB0"
            }

            Frame {
                id: frameID
                Layout.rowSpan: 2
                Layout.preferredHeight: 63
                Layout.preferredWidth: 60
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
                    text: qsTr("")
                    anchors.top: labelDeviceMCP23017ID.bottom
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.topMargin: -16
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 15
                    font.pixelSize: 10
                }
            }

            PushButtonMCP23017 {
                id: button_GPB8
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA0"
                objectName: "button_GPB0"
            }

            PushButtonMCP23017 {
                id: button_GPB1
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                objectName: "button_GPB0"
                labelPushButtonText: "GPB1"
            }

            PushButtonMCP23017 {
                id: button_GPB9
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA1"
                objectName: "button_GPB0"
            }

            PushButtonMCP23017 {
                id: button_GPB2
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB2"
                objectName: "button_GPB0"
            }

            Frame {
                id: frameIAdd
                Layout.rowSpan: 2
                Layout.preferredHeight: 65
                Layout.preferredWidth: 60
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
                    text: qsTr("")
                    anchors.top: labelDeviceMCP23017Add.bottom
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.topMargin: -16
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 30
                    font.pixelSize: 10
                    Layout.preferredHeight: 15
                }
            }

            PushButtonMCP23017 {
                id: button_GPB10
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA2"
                objectName: "button_GPB0"
            }

            PushButtonMCP23017 {
                id: button_GPB3
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB3"
                objectName: "button_GPB0"
            }

            PushButtonMCP23017 {
                id: button_GPB11
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA3"
                objectName: "button_GPB0"
            }

            PushButtonMCP23017 {
                id: button_GPB4
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB4"
                objectName: "button_GPB0"
            }

            Item {
                id: spacer
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            PushButtonMCP23017 {
                id: button_GPB12
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA4"
                objectName: "button_GPB0"
            }

            PushButtonMCP23017 {
                id: button_GPB5
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB5"
                objectName: "button_GPB0"
            }

            Item {
                id: spacer1
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            PushButtonMCP23017 {
                id: button_GPB13
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA5"
                objectName: "button_GPB0"
            }

            PushButtonMCP23017 {
                id: button_GPB6
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB6"
                objectName: "button_GPB0"
            }

            Item {
                id: spacer2
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            PushButtonMCP23017 {
                id: button_GPB14
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA6"
                objectName: "button_GPB0"
            }

            PushButtonMCP23017 {
                id: button_GPB7
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPB7"
                objectName: "button_GPB0"
            }

            Item {
                id: spacer3
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            PushButtonMCP23017 {
                id: button_GPB15
                Layout.preferredHeight: 30
                Layout.preferredWidth: 80
                labelPushButtonText: "GPA7"
                objectName: "button_GPB0"
            }
        }

    }


}

/*##^## Designer {
    D{i:35;anchors_height:12;anchors_width:56;anchors_x:0;anchors_y:42}D{i:39;anchors_height:16;anchors_width:58}
D{i:40;anchors_height:54;anchors_width:56;anchors_x:0;anchors_y:22}D{i:69;anchors_x:-1;anchors_y:6}
}
 ##^##*/
