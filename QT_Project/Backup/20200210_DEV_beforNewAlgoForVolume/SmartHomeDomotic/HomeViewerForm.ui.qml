import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

PageBackground
{
    property alias textEditAtStartup: textEditAtStartup
    property alias textEditAtStartupText: textEditAtStartup.text

    property alias tank1textNameText: tank1textName.text
    property alias tank2textNameText: tank2textName.text
    property alias tank3textNameText: tank3textName.text
    property alias tank4textNameText: tank4textName.text
    property alias tank5textNameText: tank5textName.text
    property alias tank6textNameText: tank6textName.text

    property alias tank1textQuantity: tank1textQuantity
    property alias tank2textQuantity: tank2textQuantity
    property alias tank3textQuantity: tank3textQuantity
    property alias tank4textQuantity: tank4textQuantity
    property alias tank5textQuantity: tank5textQuantity
    property alias tank6textQuantity: tank6textQuantity

    property alias tank1textQuantityText: tank1textQuantity.text
    property alias tank2textQuantityText: tank2textQuantity.text
    property alias tank3textQuantityText: tank3textQuantity.text
    property alias tank4textQuantityText: tank4textQuantity.text
    property alias tank5textQuantityText: tank5textQuantity.text
    property alias tank6textQuantityText: tank6textQuantity.text

    property alias rectangleSensor1Color: rectangleSensor1.color
    property alias rectangleSensor2Color: rectangleSensor2.color
    property alias rectangleSensor3Color: rectangleSensor3.color
    property alias rectangleSensor4Color: rectangleSensor4.color
    property alias rectangleSensor5Color: rectangleSensor5.color
    property alias rectangleSensor6Color: rectangleSensor6.color

    property alias textBME280Text: textBME280.text
    property alias textSensor1Text: textSensor1.text
    property alias textSensor2Text: textSensor2.text
    property alias textSensor3Text: textSensor3.text
    property alias textSensor4Text: textSensor4.text
    property alias textSensor5Text: textSensor5.text
    property alias textSensor6Text: textSensor6.text
    property alias textAD2Text: textAD2.text
    property alias textAD1Text: textAD1.text
    property alias textMCP23017_1Text: textMCP23017_1.text
    property alias textMCP23017_2Text: textMCP23017_2.text
    property alias textMCP23017_3Text: textMCP23017_3.text
    property alias textMCP23017_4Text: textMCP23017_4.text

    property alias rectangleBME280Visible: rectangleBME280.visible
    property alias tank1rectangleVisible: tank1rectangle.visible
    property alias tank2rectangleVisible: tank2rectangle.visible
    property alias tank3rectangleVisible: tank3rectangle.visible
    property alias tank4rectangleVisible: tank4rectangle.visible
    property alias tank5rectangleVisible: tank5rectangle.visible
    property alias tank6rectangleVisible: tank6rectangle.visible
    property alias rectangleSensor1Visible: rectangleSensor1.visible
    property alias rectangleSensor2Visible: rectangleSensor2.visible
    property alias rectangleSensor3Visible: rectangleSensor3.visible
    property alias rectangleSensor4Visible: rectangleSensor4.visible
    property alias rectangleSensor5Visible: rectangleSensor5.visible
    property alias rectangleSensor6Visible: rectangleSensor6.visible
    property alias rectangleAD1Visible: rectangleAD1.visible
    property alias rectangleAD2Visible: rectangleAD2.visible
    property alias rectangleMCP23017_1Visible: rectangleMCP23017_1.visible
    property alias rectangleMCP23017_2Visible: rectangleMCP23017_2.visible
    property alias rectangleMCP23017_3Visible: rectangleMCP23017_3.visible
    property alias rectangleMCP23017_4Visible: rectangleMCP23017_4.visible

    property alias rectangleBME280Color: rectangleBME280.color
    property alias tank6rectangleColor: tank6rectangle.color
    property alias tank5rectangleColor: tank5rectangle.color
    property alias tank4rectangleColor: tank4rectangle.color
    property alias tank3rectangleColor: tank3rectangle.color
    property alias tank2rectangleColor: tank2rectangle.color
    property alias tank1rectangleColor: tank1rectangle.color
    property alias rectangleAD1Color: rectangleAD1.color
    property alias rectangleAD2Color: rectangleAD2.color
    property alias rectangleMCP23017_1Color: rectangleMCP23017_1.color
    property alias rectangleMCP23017_2Color: rectangleMCP23017_2.color
    property alias rectangleMCP23017_3Color: rectangleMCP23017_3.color
    property alias rectangleMCP23017_4Color: rectangleMCP23017_4.color

    property int someNumber: 0

    id: homeViewer
    width: 980
    height: 800

    Frame {
        id: frameTank
        width: 740
        anchors.right: parent.right
        anchors.rightMargin: 33
        anchors.left: frameDevice.right
        anchors.leftMargin: 6
        anchors.bottom: frameTextEdit.top
        anchors.bottomMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 54
        topPadding: 0
        padding: 20

        LabelDevice {
            id: labelDevice
            text: "Tank"
            anchors.horizontalCenterOffset: -6
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            Layout.columnSpan: 3
            Layout.preferredHeight: 50
            Layout.preferredWidth: 655
        }

        GridLayout {
            id: gridLayoutTank
            anchors.top: labelDevice.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            rowSpacing: 5
            columnSpacing: 5
            rows: 3
            columns: 3

            Rectangle {
                id: tank1rectangle
                color: "#707070"
                radius: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 200
                border.width: 2
                border.color: "#808080"
                Text {
                    id: tank1textName
                    x: 40
                    width: 71
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 45
                    anchors.top: parent.top
                    anchors.topMargin: 8
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                }

                Text {
                    id: tank1textQuantity
                    x: 48
                    width: 71
                    text: qsTr("0")
                    font.bold: true
                    anchors.top: parent.top
                    anchors.topMargin: 45
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    anchors.horizontalCenterOffset: 0
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                id: tank2rectangle
                color: "#707070"
                radius: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 200
                border.width: 2
                border.color: "#808080"
                Text {
                    id: tank2textName
                    x: 40
                    width: 71
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 45
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                    anchors.topMargin: 8
                }

                Text {
                    id: tank2textQuantity
                    x: 48
                    width: 71
                    text: qsTr("0")
                    font.bold: true
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 0
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 45
                }
            }

            Rectangle {
                id: tank3rectangle
                color: "#707070"
                radius: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 200
                border.width: 2
                border.color: "#808080"
                Text {
                    id: tank3textName
                    x: 40
                    width: 71
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 45
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                    anchors.topMargin: 8
                }

                Text {
                    id: tank3textQuantity
                    x: 48
                    width: 71
                    text: qsTr("0")
                    font.bold: true
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 0
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 45
                }
            }

            Rectangle {
                id: tank4rectangle
                color: "#707070"
                radius: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 200
                border.width: 2
                border.color: "#808080"
                Text {
                    id: tank4textName
                    x: 40
                    width: 71
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 45
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                    anchors.topMargin: 8
                }

                Text {
                    id: tank4textQuantity
                    x: 48
                    width: 71
                    text: qsTr("0")
                    font.bold: true
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 0
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 45
                }
            }

            Rectangle {
                id: tank5rectangle
                color: "#707070"
                radius: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 200
                border.width: 2
                border.color: "#808080"
                Text {
                    id: tank5textName
                    x: 40
                    width: 71
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 45
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                    anchors.topMargin: 8
                }

                Text {
                    id: tank5textQuantity
                    x: 48
                    width: 71
                    text: qsTr("0")
                    font.bold: true
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 0
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 45
                }
            }

            Rectangle {
                id: tank6rectangle
                color: "#707070"
                radius: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 200
                border.width: 2
                border.color: "#808080"
                Text {
                    id: tank6textName
                    x: 40
                    width: 71
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 45
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                    anchors.topMargin: 8
                }

                Text {
                    id: tank6textQuantity
                    x: 48
                    width: 71
                    text: qsTr("0")
                    font.bold: true
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    horizontalAlignment: Text.AlignHCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 0
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 45
                }
            }
        }






    }

    Frame {
        id: frameDevice
        anchors.right: parent.left
        anchors.rightMargin: -200
        anchors.left: parent.left
        anchors.leftMargin: 34
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 54
        topPadding: 0
        padding: 20

        LabelDevice {
            id: labelDeviceDevice
            text: "Devices"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        ColumnLayout {
            id: columnLayoutDevices
            anchors.top: labelDeviceDevice.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            spacing: 5



            Rectangle {
                id: rectangleBME280
                color: "#707070"
                radius: 20
                Layout.preferredHeight: 40
                border.width: 2
                Layout.fillWidth: true
                border.color: "#808080"
                Text {
                    id: textBME280
                    x: 11
                    y: 7
                    width: 71
                    height: 27
                    font.pixelSize: 20
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 90
            }

            Rectangle {
                id: rectangleSensor1
                color: "#707070"
                radius: 20
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 40
                Layout.preferredWidth: 90
                border.color: "#808080"
                border.width: 2

                Text {
                    id: textSensor1
                    x: 11
                    y: 7
                    width: 71
                    height: 27
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                }
            }

            Rectangle {
                id: rectangleSensor2
                color: "#707070"
                radius: 20
                Layout.preferredHeight: 40
                border.color: "#808080"
                Layout.preferredWidth: 90
                Text {
                    id: textSensor2
                    x: 11
                    y: 7
                    width: 71
                    height: 27
                    font.pixelSize: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.width: 2
                Layout.fillWidth: true
            }

            Rectangle {
                id: rectangleSensor3
                color: "#707070"
                radius: 20
                Layout.preferredHeight: 40
                border.color: "#808080"
                Layout.preferredWidth: 90
                Text {
                    id: textSensor3
                    x: 11
                    y: 7
                    width: 71
                    height: 27
                    font.pixelSize: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.width: 2
                Layout.fillWidth: true
            }

            Rectangle {
                id: rectangleSensor4
                color: "#707070"
                radius: 20
                Layout.preferredHeight: 40
                border.color: "#808080"
                Layout.preferredWidth: 90
                Text {
                    id: textSensor4
                    x: 11
                    y: 7
                    width: 71
                    height: 27
                    font.pixelSize: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.width: 2
                Layout.fillWidth: true
            }

            Rectangle {
                id: rectangleSensor5
                color: "#707070"
                radius: 20
                Layout.preferredHeight: 40
                border.color: "#808080"
                Layout.preferredWidth: 90
                Text {
                    id: textSensor5
                    x: 11
                    y: 7
                    width: 71
                    height: 27
                    font.pixelSize: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.width: 2
                Layout.fillWidth: true
            }

            Rectangle {
                id: rectangleSensor6
                color: "#707070"
                radius: 20
                Layout.preferredHeight: 40
                border.color: "#808080"
                Layout.preferredWidth: 90
                Text {
                    id: textSensor6
                    x: 11
                    y: 7
                    width: 71
                    height: 27
                    font.pixelSize: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.width: 2
                Layout.fillWidth: true
            }

            Rectangle {
                id: rectangleAD1
                width: 100
                color: "#707070"
                radius: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 90
                border.width: 2
                border.color: "#808080"
                Text {
                    id: textAD1
                    x: 8
                    y: 8
                    width: 71
                    height: 27
                    text: qsTr("")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                id: rectangleAD2
                width: 100
                color: "#707070"
                radius: 20
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 40
                Layout.preferredWidth: 90
                border.width: 2
                border.color: "#808080"
                Text {
                    id: textAD2
                    x: 8
                    y: 8
                    width: 71
                    height: 27
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 20
                }
            }

            Rectangle {
                id: rectangleMCP23017_1
                width: 100
                color: "#707070"
                radius: 20
                border.width: 2
                Layout.preferredHeight: 40
                border.color: "#808080"
                Text {
                    id: textMCP23017_1
                    x: 8
                    y: 8
                    width: 71
                    height: 27
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                Layout.preferredWidth: 90
            }

            Rectangle {
                id: rectangleMCP23017_2
                width: 100
                color: "#707070"
                radius: 20
                border.width: 2
                border.color: "#808080"
                Layout.preferredHeight: 40
                Text {
                    id: textMCP23017_2
                    x: 8
                    y: 8
                    width: 71
                    height: 27
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 90
                Layout.fillWidth: true
            }

            Rectangle {
                id: rectangleMCP23017_3
                width: 100
                color: "#707070"
                radius: 20
                border.width: 2
                border.color: "#808080"
                Layout.preferredHeight: 40
                Text {
                    id: textMCP23017_3
                    x: 8
                    y: 8
                    width: 71
                    height: 27
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 90
                Layout.fillWidth: true
            }

            Rectangle {
                id: rectangleMCP23017_4
                width: 100
                color: "#707070"
                radius: 20
                border.width: 2
                border.color: "#808080"
                Layout.preferredHeight: 40
                Text {
                    id: textMCP23017_4
                    x: 8
                    y: 8
                    width: 71
                    height: 27
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 90
                Layout.fillWidth: true
            }







        }



    }

    Frame {
        id: frameTextEdit
        width: 740
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.right: parent.right
        anchors.rightMargin: 33
        anchors.left: frameDevice.right
        anchors.leftMargin: 6
        anchors.topMargin: 335
        anchors.top: parent.top
        padding: 20

        TextEdit
        {
            id: textEditAtStartup
            objectName: "textEditAtStartup"
            color: "#c9baba"
            text: ""
            anchors.fill: parent
            activeFocusOnPress: false
            readOnly: false
            cursorVisible: true
            visible: true
            font.pointSize: 10
            horizontalAlignment: Text.AlignLeft
        }
    }
}

/*##^## Designer {
    D{i:3;anchors_y:2}D{i:11;anchors_height:27;anchors_width:71;anchors_x:40;anchors_y:8}
D{i:12;anchors_height:27;anchors_y:45}D{i:14;anchors_height:27;anchors_width:71;anchors_x:40;anchors_y:8}
D{i:15;anchors_height:27;anchors_y:45}D{i:17;anchors_height:27;anchors_width:71;anchors_x:40;anchors_y:8}
D{i:18;anchors_height:27;anchors_y:45}D{i:20;anchors_height:27;anchors_width:71;anchors_x:40;anchors_y:8}
D{i:21;anchors_height:27;anchors_y:45}D{i:24;anchors_height:27;anchors_width:142;anchors_x:15;anchors_y:9}
D{i:26;anchors_height:27;anchors_width:71;anchors_x:40;anchors_y:8}D{i:31;anchors_x:4;anchors_y:"-6"}
D{i:23;anchors_height:27;anchors_width:71;anchors_x:40;anchors_y:8}D{i:41;anchors_height:27;anchors_width:71;anchors_x:40;anchors_y:8}
}
 ##^##*/
