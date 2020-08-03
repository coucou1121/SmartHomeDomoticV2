import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.0

Item {
    width: 120
    height: 200
    LabelDevice {
        id: labelDeviceMCP23017_1
        x: 24
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
        anchors.top: labelDeviceMCP23017_1.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 6
        rightPadding: 5
        bottomPadding: 0
        leftPadding: 5
        topPadding: 0





        GridLayout {
            anchors.bottomMargin: 4
            anchors.fill: parent
            rows: 8
            columns: 3

            Text {
                id: textGPB0
                text: qsTr("GPB0")
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Frame {
                id: frameID
                Layout.rowSpan: 2
                Layout.preferredHeight: 37
                Layout.preferredWidth: 28
                leftPadding: 2
                rightPadding: 2
                bottomPadding: 2
                topPadding: 2

                LabelDevice {
                    id: labelDeviceMCP23017ID
                    text: "ID"
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 17
                    anchors.top: parent.top
                    anchors.topMargin: 0
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
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: labelDeviceMCP23017ID.bottom
                    anchors.topMargin: 2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 15
                    font.pixelSize: 10
                }
            }

            Text {
                id: textGPA7
                text: qsTr("GPA7")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPB1
                text: qsTr("GPB1")
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPA6
                text: qsTr("GPA6")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPB2
                text: qsTr("GPB2")
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Frame {
                id: frameIAdd
                Layout.rowSpan: 2
                Layout.preferredHeight: 37
                Layout.preferredWidth: 28
                leftPadding: 2
                rightPadding: 2
                bottomPadding: 2
                topPadding: 2
                LabelDevice {
                    id: labelDeviceMCP23017Add
                    text: "Add"
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 17
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.rightMargin: 0
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
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: labelDeviceMCP23017Add.bottom
                    anchors.topMargin: 2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -1
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    Layout.preferredWidth: 30
                    font.pixelSize: 10
                    Layout.preferredHeight: 15
                }
            }

            Text {
                id: textGPA5
                text: qsTr("GPA5")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPB3
                text: qsTr("GPB3")
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPA4
                text: qsTr("GPA4")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPB4
                text: qsTr("GPB4")
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Item {
                id: spacer
                Layout.preferredWidth: 14
                Layout.preferredHeight: 14
            }

            Text {
                id: textGPA3
                text: qsTr("GPA3")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPB5
                text: qsTr("GPB5")
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Item {
                id: spacer1
                Layout.preferredWidth: 14
                Layout.preferredHeight: 14
            }

            Text {
                id: textGPA2
                text: qsTr("GPA2")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPB6
                text: qsTr("GPB6")
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Item {
                id: spacer2
                Layout.preferredWidth: 14
                Layout.preferredHeight: 14
            }

            Text {
                id: textGPA1
                text: qsTr("GPA1")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Text {
                id: textGPB7
                text: qsTr("GPB7")
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }

            Item {
                id: spacer3
                Layout.preferredWidth: 14
                Layout.preferredHeight: 14
            }

            Text {
                id: textGPA0
                text: qsTr("GPA0")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 15
                Layout.preferredWidth: 30
                font.pixelSize: 12
            }
        }

    }


}

/*##^## Designer {
    D{i:30;anchors_height:16;anchors_width:20;anchors_x:1;anchors_y:0}D{i:47;anchors_height:12;anchors_width:22;anchors_x:2;anchors_y:21}
D{i:51;anchors_height:16;anchors_width:28;anchors_x:-2;anchors_y:0}D{i:52;anchors_height:12;anchors_width:26;anchors_x:-1;anchors_y:22}
D{i:53;anchors_x:0;anchors_y:1}D{i:4;anchors_height:180;anchors_width:100;anchors_x:10;anchors_y:20}
}
 ##^##*/
