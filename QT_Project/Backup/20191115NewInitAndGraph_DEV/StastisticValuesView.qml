import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item
{
    property alias labelDeviceTemperatureMinDayText: labelDeviceTemperatureMinDay.text
    property alias labelDeviceTemperatureMaxDayText: labelDeviceTemperatureMaxDay.text
    property alias labelDeviceHumidityMinDayText: labelDeviceHumidityMinDay.text
    property alias labelDeviceHumidityMaxDayText: labelDeviceHumidityMaxDay.text
    property alias labelDeviceAtmoPressurMinDayText: labelDeviceAtmoPressurMinDay.text
    property alias labelDeviceAtmoPressurMaxDayText: labelDeviceAtmoPressurMaxDay.text
    property alias labelDeviceConsoDayText: labelDeviceConsoDay.text
    property alias labelDeviceConsoDayBeforeText: labelDeviceConsoDayBefore.text

    property alias labelDeviceTemperatureMinMonthText: labelDeviceTemperatureMinMonth.text
    property alias labelDeviceTemperatureMaxMonthText: labelDeviceTemperatureMaxMonth.text
    property alias labelDeviceHumidityMinMonthText: labelDeviceHumidityMinMonth.text
    property alias labelDeviceHumidityMaxMonthText: labelDeviceHumidityMaxMonth.text
    property alias labelDeviceAtmoPressurMaxMonthText: labelDeviceAtmoPressurMaxMonth.text
    property alias labelDeviceAtmoPressurMinMonthText: labelDeviceAtmoPressurMinMonth.text
    property alias labelDeviceConsoMonthText: labelDeviceConsoMonth.text
    property alias labelDeviceConsoMonthBeforeText: labelDeviceConsoMonthBefore.text

    id: item1
    width: 300
    height: 320

    Frame {
        id: frameTitleDay
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 165
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        Layout.preferredHeight: 150
        Layout.preferredWidth: 300
        padding: 5
        topPadding: 0
        Layout.maximumHeight: 40
        Layout.minimumHeight: 40
        Layout.fillHeight: true
        Layout.fillWidth: true

        GridLayout {
            anchors.fill: parent
            rows: 3
            columns: 2

            LabelDevice {
                id: labelDay
                text: "Today"
                Layout.columnSpan: 2
                horizontalAlignment: Text.AlignLeft
                Layout.maximumWidth: 100
                Layout.minimumWidth: 100
                Layout.preferredHeight: 24
                Layout.preferredWidth: 120
                font.pointSize: 16
            }

            Frame {
                id: frameTemperatureDay
                Layout.preferredHeight: 55
                Layout.preferredWidth: 130
                rightPadding: 2
                bottomPadding: 2
                leftPadding: 2
                topPadding: 2
                Layout.fillHeight: false
                Layout.fillWidth: false
                padding: 2

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Image {
                        id: imageTempratureDay
                        Layout.maximumHeight: 40
                        Layout.minimumHeight: 40
                        Layout.maximumWidth: 42
                        Layout.rowSpan: 2
                        Layout.minimumWidth: 30
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 30
                        fillMode: Image.PreserveAspectFit
                        antialiasing: true
                        clip: false
                        source: "Picture/thermometer.png"
                    }

                    ColumnLayout {
                        Layout.fillHeight: false
                        Layout.fillWidth: false
                        Layout.maximumHeight: 50
                        Layout.minimumHeight: 50
                        Layout.maximumWidth: 60
                        Layout.minimumWidth: 60
                        Layout.preferredHeight: 50
                        spacing: 0

                        LabelDevice {
                            id: labelDeviceTemperatureMaxDay
                            text: "0"
                            Layout.maximumWidth: 60
                            Layout.preferredHeight: 25
                            Layout.preferredWidth: 60
                            font.pointSize: 12
                            padding: 5
                            verticalAlignment: Text.AlignVCenter
                            Layout.minimumWidth: 60
                            horizontalAlignment: Text.AlignRight
                        }

                        LabelDevice {
                            id: labelDeviceTemperatureMinDay
                            text: "0"
                            Layout.maximumWidth: 60
                            Layout.preferredHeight: 25
                            Layout.preferredWidth: 60
                            font.pointSize: 12
                            padding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 60
                        }
                    }

                    ColumnLayout {
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        spacing: 0
                        Layout.maximumHeight: 50
                        Layout.minimumHeight: 50
                        Layout.maximumWidth: 25
                        Layout.minimumWidth: 25
                        Layout.preferredHeight: 50
                        Layout.preferredWidth: 25

                        LabelDevice {
                            id: labelDayTempMax
                            height: 10
                            text: "max"
                            font.bold: false
                            Layout.fillHeight: true
                            Layout.maximumHeight: 10
                            Layout.minimumHeight: 10
                            Layout.preferredWidth: 25
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 25
                            font.pointSize: 8
                            Layout.maximumWidth: 25
                            verticalAlignment: Text.AlignBottom
                        }

                        LabelDevice {
                            id: labelDeviceTemperatureUnity
                            color: "#cccccc"
                            text: "°c"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            leftPadding: 0
                            Layout.minimumWidth: 25
                            Layout.rowSpan: 2
                            Layout.preferredHeight: 20
                            Layout.preferredWidth: 30
                            font.pointSize: 12
                            padding: 5
                            verticalAlignment: Text.AlignVCenter
                            topPadding: 5
                            horizontalAlignment: Text.AlignLeft
                            Layout.maximumWidth: 30
                        }

                        LabelDevice {
                            id: labelDayTempMin
                            width: 25
                            height: 10
                            text: "min"
                            Layout.fillHeight: true
                            Layout.maximumHeight: 10
                            Layout.minimumHeight: 10
                            Layout.maximumWidth: 25
                            Layout.minimumWidth: 25
                            Layout.fillWidth: true
                            Layout.preferredWidth: 25
                            Layout.preferredHeight: 10
                            font.pointSize: 8
                            verticalAlignment: Text.AlignBottom
                        }

                    }
                }




            }

            Frame {
                id: frameAtmoPressurDay
                Layout.preferredHeight: 55
                Layout.preferredWidth: 156
                rightPadding: 2
                bottomPadding: 2
                leftPadding: 2
                topPadding: 2
                Layout.fillHeight: false
                Layout.fillWidth: false
                padding: 2


                RowLayout {
                    spacing: 0
                    anchors.fill: parent

                    Image {
                        id: imageAtmoPressureDay
                        Layout.maximumWidth: 40
                        Layout.maximumHeight: 40
                        Layout.minimumHeight: 40
                        Layout.rowSpan: 2
                        Layout.minimumWidth: 40
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 40
                        source: "Picture/atmosphericPressure.png"
                        clip: false
                        fillMode: Image.PreserveAspectFit
                        antialiasing: true
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelDeviceAtmoPressurMinDay
                            text: "0"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.maximumWidth: 70
                            Layout.preferredHeight: 25
                            Layout.preferredWidth: 70
                            font.pointSize: 12
                            padding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 70
                        }

                        LabelDevice {
                            id: labelDeviceAtmoPressurMaxDay
                            text: "0"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.maximumWidth: 70
                            Layout.preferredHeight: 25
                            Layout.preferredWidth: 70
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 70
                            font.pointSize: 12
                            padding: 5
                        }
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelDayPressureMin
                            text: "min"
                            horizontalAlignment: Text.AlignLeft
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 40
                            Layout.minimumHeight: 10
                            Layout.fillHeight: false
                            font.pointSize: 8
                            Layout.fillWidth: false
                            Layout.maximumWidth: 40
                            Layout.preferredWidth: 40
                            Layout.maximumHeight: 10
                            verticalAlignment: Text.AlignBottom
                        }

                        LabelDevice {
                            id: labelDeviceAtmoPressurMaxUnityDay
                            color: "#cccccc"
                            text: "mbar"
                            leftPadding: 0
                            Layout.minimumWidth: 40
                            Layout.rowSpan: 2
                            Layout.preferredHeight: 30
                            Layout.preferredWidth: 40
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            Layout.maximumWidth: 40
                        }

                        LabelDevice {
                            id: labelDayPressureMax
                            text: "max"
                            horizontalAlignment: Text.AlignLeft
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 40
                            Layout.minimumHeight: 10
                            Layout.fillHeight: false
                            font.pointSize: 8
                            Layout.maximumWidth: 40
                            Layout.preferredWidth: 40
                            font.bold: false
                            Layout.maximumHeight: 10
                            verticalAlignment: Text.AlignBottom
                        }
                    }
                }
            }

            Frame {
                id: frameHumidityDay
                Layout.preferredHeight: 55
                Layout.preferredWidth: 130
                rightPadding: 2
                bottomPadding: 2
                leftPadding: 2
                topPadding: 2
                Layout.fillHeight: false
                Layout.fillWidth: false
                padding: 2

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Image {
                        id: imageHumidityDay
                        Layout.maximumHeight: 40
                        Layout.minimumHeight: 40
                        Layout.maximumWidth: 42
                        Layout.rowSpan: 2
                        Layout.minimumWidth: 30
                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 30
                        source: "Picture/humidity.png"
                        clip: false
                        antialiasing: true
                        fillMode: Image.PreserveAspectFit
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelDeviceHumidityMaxDay
                            text: "0"
                            Layout.maximumWidth: 60
                            Layout.preferredHeight: 25
                            Layout.preferredWidth: 60
                            padding: 5
                            font.pointSize: 12
                            verticalAlignment: Text.AlignVCenter
                            Layout.minimumWidth: 60
                            horizontalAlignment: Text.AlignRight
                        }

                        LabelDevice {
                            id: labelDeviceHumidityMinDay
                            text: "0"
                            Layout.maximumWidth: 60
                            Layout.preferredHeight: 25
                            Layout.preferredWidth: 60
                            font.pointSize: 12
                            padding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 60
                        }
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelDayHumidityMax
                            text: "max"
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 25
                            Layout.minimumHeight: 10
                            Layout.fillHeight: true
                            font.pointSize: 8
                            Layout.maximumWidth: 25
                            Layout.preferredWidth: 25
                            font.bold: false
                            Layout.maximumHeight: 10
                            verticalAlignment: Text.AlignBottom
                        }

                        LabelDevice {
                            id: labelDeviceHumidityUnityDay
                            color: "#cccccc"
                            text: "%"
                            leftPadding: 0
                            Layout.minimumWidth: 25
                            Layout.rowSpan: 2
                            Layout.preferredHeight: 30
                            Layout.preferredWidth: 25
                            font.pointSize: 12
                            padding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            Layout.maximumWidth: 30
                        }

                        LabelDevice {
                            id: labelDayHumidityMin
                            text: "min"
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 25
                            Layout.minimumHeight: 10
                            Layout.fillHeight: true
                            font.pointSize: 8
                            Layout.fillWidth: true
                            Layout.maximumWidth: 25
                            Layout.preferredWidth: 25
                            Layout.maximumHeight: 10
                            verticalAlignment: Text.AlignBottom
                        }
                    }
                }










            }

            Frame {
                id: frameConsoDay
                Layout.preferredHeight: 55
                Layout.preferredWidth: 156
                leftPadding: 2
                Layout.fillHeight: false
                rightPadding: 2
                Layout.fillWidth: false
                padding: 2
                topPadding: 2

                RowLayout {
                    spacing: 0
                    anchors.fill: parent

                    Image {
                        id: imageConsoDay
                        Layout.preferredHeight: 40
                        Layout.minimumWidth: 30
                        Layout.rowSpan: 2
                        antialiasing: true
                        Layout.minimumHeight: 40
                        source: "Picture/ConsoOil.png"
                        clip: false
                        fillMode: Image.PreserveAspectFit
                        Layout.maximumWidth: 42
                        Layout.preferredWidth: 40
                        Layout.maximumHeight: 40
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelDeviceConsoDay
                            height: 25
                            text: "0"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 70
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 70
                            Layout.preferredWidth: 70
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelDeviceConsoDayBefore
                            height: 25
                            text: "0"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 70
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 70
                            Layout.preferredWidth: 70
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelDayConsoToday
                            width: 40
                            text: "consum"
                            horizontalAlignment: Text.AlignLeft
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 40
                            Layout.minimumHeight: 10
                            font.pointSize: 8
                            Layout.fillHeight: false
                            Layout.maximumWidth: 40
                            font.bold: false
                            Layout.preferredWidth: 40
                            verticalAlignment: Text.AlignBottom
                            Layout.maximumHeight: 10
                        }

                        LabelDevice {
                            id: labelDeviceConsoUnityDay
                            height: 24
                            color: "#cccccc"
                            text: "Lt"
                            Layout.maximumHeight: 24
                            Layout.minimumHeight: 24
                            Layout.preferredHeight: 24
                            Layout.rowSpan: 2
                            Layout.minimumWidth: 25
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignLeft
                            Layout.maximumWidth: 30
                            Layout.preferredWidth: 25
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelDayConsoYesterday
                            width: 40
                            height: 15
                            text: "volume"
                            horizontalAlignment: Text.AlignLeft
                            Layout.preferredHeight: 15
                            Layout.minimumWidth: 40
                            Layout.minimumHeight: 15
                            font.pointSize: 8
                            Layout.fillHeight: false
                            Layout.fillWidth: false
                            Layout.maximumWidth: 40
                            Layout.preferredWidth: 40
                            verticalAlignment: Text.AlignTop
                            Layout.maximumHeight: 15
                        }
                    }
                }



                bottomPadding: 2
            }
        }
    }

    Frame {
        id: frameTitleMonth
        width: 300
        visible: true
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 160
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        Layout.preferredHeight: 150
        Layout.preferredWidth: 300
        Layout.minimumHeight: 40
        Layout.fillHeight: true
        Layout.fillWidth: true
        padding: 5
        topPadding: 0

        GridLayout {
            anchors.bottomMargin: 0
            anchors.fill: parent
            rows: 3
            columns: 2

            LabelDevice {
                id: labelMonth
                width: 150
                text: "This month"
                Layout.fillWidth: false
                Layout.fillHeight: false
                Layout.columnSpan: 2
                horizontalAlignment: Text.AlignLeft
                Layout.preferredHeight: 24
                Layout.minimumWidth: 150
                font.pointSize: 16
                Layout.maximumWidth: 150
                Layout.preferredWidth: 150
            }

            Frame {
                id: frameTemperatureMonth
                Layout.preferredHeight: 55
                Layout.preferredWidth: 130
                leftPadding: 2
                Layout.fillHeight: false
                rightPadding: 2
                Layout.fillWidth: false
                padding: 2
                topPadding: 2

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Image {
                        id: imageTempratureMonth
                        Layout.preferredHeight: 40
                        Layout.rowSpan: 2
                        Layout.minimumWidth: 30
                        Layout.minimumHeight: 40
                        antialiasing: true
                        source: "Picture/thermometer.png"
                        fillMode: Image.PreserveAspectFit
                        clip: false
                        Layout.maximumWidth: 42
                        Layout.preferredWidth: 27
                        Layout.maximumHeight: 40
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelDeviceTemperatureMaxMonth
                            text: "0"
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 60
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 60
                            Layout.preferredWidth: 60
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelDeviceTemperatureMinMonth
                            text: "0"
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 60
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 60
                            Layout.preferredWidth: 60
                            verticalAlignment: Text.AlignVCenter

                        }
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelMonthTemperatureMax
                            text: "max"
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 25
                            Layout.minimumHeight: 10
                            font.pointSize: 8
                            Layout.fillHeight: true
                            Layout.maximumWidth: 25
                            font.bold: false
                            Layout.preferredWidth: 25
                            verticalAlignment: Text.AlignBottom
                            Layout.maximumHeight: 10
                        }

                        LabelDevice {
                            id: labelDeviceTemperatureUnity1
                            color: "#cccccc"
                            text: "°c"
                            leftPadding: 0
                            Layout.preferredHeight: 30
                            Layout.minimumWidth: 25
                            Layout.rowSpan: 2
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignLeft
                            topPadding: 5
                            Layout.maximumWidth: 30
                            Layout.preferredWidth: 25
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelMonthTemperatureMin
                            text: "min"
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 25
                            Layout.minimumHeight: 10
                            font.pointSize: 8
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.maximumWidth: 25
                            Layout.preferredWidth: 25
                            verticalAlignment: Text.AlignBottom
                            Layout.maximumHeight: 10
                        }
                    }
                }


                bottomPadding: 2
            }

            Frame {
                id: frameAtmoPressurMonth
                Layout.maximumHeight: 55
                Layout.minimumHeight: 55
                Layout.maximumWidth: 156
                Layout.minimumWidth: 156
                Layout.preferredHeight: 55
                Layout.preferredWidth: 156
                leftPadding: 2
                Layout.fillHeight: false
                rightPadding: 2
                Layout.fillWidth: false
                padding: 2
                topPadding: 2

                RowLayout {
                    spacing: 0
                    anchors.fill: parent

                    Image {
                        id: imageAtmoPressureMonth
                        Layout.preferredHeight: 40
                        Layout.rowSpan: 2
                        Layout.minimumWidth: 40
                        Layout.minimumHeight: 40
                        antialiasing: true
                        source: "Picture/atmosphericPressure.png"
                        clip: false
                        fillMode: Image.PreserveAspectFit
                        Layout.maximumWidth: 40
                        Layout.preferredWidth: 40
                        Layout.maximumHeight: 40
                    }

                    ColumnLayout {

                        LabelDevice {
                            id: labelDeviceAtmoPressurMinMonth
                            text: "0"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 70
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 70
                            Layout.preferredWidth: 70
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelDeviceAtmoPressurMaxMonth
                            text: "0"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 70
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 70
                            Layout.preferredWidth: 70
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelMonthPressureMax
                            text: "max"
                            horizontalAlignment: Text.AlignLeft
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 40
                            Layout.minimumHeight: 10
                            font.pointSize: 8
                            Layout.fillHeight: false
                            Layout.maximumWidth: 40
                            font.bold: false
                            Layout.preferredWidth: 40
                            verticalAlignment: Text.AlignBottom
                            Layout.maximumHeight: 10
                        }

                        LabelDevice {
                            id: labelDeviceAtmoPressurMaxUnityMonth
                            width: 40
                            color: "#cccccc"
                            text: "mbar"
                            Layout.maximumHeight: 30
                            Layout.minimumHeight: 30
                            leftPadding: 0
                            Layout.preferredHeight: 30
                            Layout.minimumWidth: 40
                            Layout.rowSpan: 2
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignLeft
                            Layout.maximumWidth: 40
                            Layout.preferredWidth: 40
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelMonthPressureMin
                            text: "min"
                            horizontalAlignment: Text.AlignLeft
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 40
                            Layout.minimumHeight: 10
                            font.pointSize: 8
                            Layout.fillHeight: false
                            Layout.fillWidth: false
                            Layout.maximumWidth: 40
                            Layout.preferredWidth: 40
                            verticalAlignment: Text.AlignBottom
                            Layout.maximumHeight: 10
                        }
                    }
                }


                bottomPadding: 2
            }

            Frame {
                id: frameHumidityMonth
                Layout.preferredHeight: 55
                Layout.preferredWidth: 130
                leftPadding: 2
                Layout.fillHeight: false
                rightPadding: 2
                Layout.fillWidth: false
                padding: 2
                topPadding: 2

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Image {
                        id: imageHumidityMonth
                        Layout.preferredHeight: 30
                        Layout.rowSpan: 2
                        Layout.minimumWidth: 30
                        Layout.minimumHeight: 40
                        antialiasing: true
                        source: "Picture/humidity.png"
                        clip: false
                        fillMode: Image.PreserveAspectFit
                        Layout.maximumWidth: 42
                        Layout.preferredWidth: 30
                        Layout.maximumHeight: 40
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelDeviceHumidityMaxMonth
                            text: "0"
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 60
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 60
                            Layout.preferredWidth: 60
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelDeviceHumidityMinMonth
                            text: "0"
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 60
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 60
                            Layout.preferredWidth: 60
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    ColumnLayout {
                        spacing: 0

                        LabelDevice {
                            id: labelMonthyHumidityMax
                            text: "max"
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 25
                            Layout.minimumHeight: 10
                            font.pointSize: 8
                            Layout.fillHeight: true
                            Layout.maximumWidth: 25
                            font.bold: false
                            Layout.preferredWidth: 25
                            verticalAlignment: Text.AlignBottom
                            Layout.maximumHeight: 10
                        }

                        LabelDevice {
                            id: labelDeviceHumidityUnityMonth
                            color: "#cccccc"
                            text: "%"
                            leftPadding: 0
                            Layout.preferredHeight: 30
                            Layout.minimumWidth: 25
                            Layout.rowSpan: 2
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignLeft
                            Layout.maximumWidth: 30
                            Layout.preferredWidth: 25
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelMonthyHumidityMin
                            text: "min"
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 25
                            Layout.minimumHeight: 10
                            font.pointSize: 8
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.maximumWidth: 25
                            Layout.preferredWidth: 25
                            verticalAlignment: Text.AlignBottom
                            Layout.maximumHeight: 10
                        }
                    }
                }

                bottomPadding: 2
            }

            Frame {
                id: frameConsoMonth
                Layout.maximumHeight: 55
                Layout.minimumHeight: 55
                Layout.maximumWidth: 156
                Layout.minimumWidth: 156
                Layout.preferredHeight: 55
                Layout.preferredWidth: 156
                leftPadding: 2
                Layout.fillHeight: false
                rightPadding: 2
                Layout.fillWidth: false
                padding: 2
                topPadding: 2

                RowLayout {
                    spacing: 0
                    anchors.fill: parent

                    Image {
                        id: imageConsoMonth
                        Layout.preferredHeight: 40
                        Layout.minimumWidth: 40
                        Layout.rowSpan: 2
                        antialiasing: true
                        Layout.minimumHeight: 40
                        source: "Picture/ConsoOil.png"
                        clip: false
                        fillMode: Image.PreserveAspectFit
                        Layout.maximumWidth: 40
                        Layout.preferredWidth: 40
                        Layout.maximumHeight: 40
                    }

                    ColumnLayout {

                        LabelDevice {
                            id: labelDeviceConsoMonth
                            height: 25
                            text: "0"
                            Layout.fillHeight: false
                            Layout.fillWidth: false
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 70
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 70
                            Layout.preferredWidth: 70
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelDeviceConsoMonthBefore
                            height: 25
                            text: "0"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.preferredHeight: 25
                            Layout.minimumWidth: 70
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignRight
                            Layout.maximumWidth: 70
                            Layout.preferredWidth: 70
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    ColumnLayout {
                        width: 40
                        Layout.fillHeight: false
                        Layout.fillWidth: false
                        Layout.maximumHeight: 50
                        Layout.minimumHeight: 500
                        Layout.preferredHeight: 50
                        Layout.maximumWidth: 40
                        Layout.minimumWidth: 40
                        Layout.preferredWidth: 40
                        spacing: 0

                        LabelDevice {
                            id: labelMonthConsoToday
                            width: 40
                            height: 10
                            text: "consum"
                            Layout.fillWidth: false
                            horizontalAlignment: Text.AlignLeft
                            Layout.preferredHeight: 10
                            Layout.minimumWidth: 40
                            Layout.minimumHeight: 10
                            Layout.fillHeight: false
                            font.pointSize: 8
                            Layout.maximumWidth: 40
                            Layout.preferredWidth: 40
                            font.bold: false
                            Layout.maximumHeight: 10
                            verticalAlignment: Text.AlignTop
                        }

                        LabelDevice {
                            id: labelDeviceConsoUnityMonth
                            width: 25
                            height: 24
                            color: "#cccccc"
                            text: "Lt"
                            Layout.maximumHeight: 25
                            Layout.minimumHeight: 25
                            Layout.preferredHeight: 25
                            Layout.rowSpan: 2
                            Layout.minimumWidth: 25
                            font.pointSize: 12
                            padding: 5
                            horizontalAlignment: Text.AlignLeft
                            Layout.maximumWidth: 30
                            Layout.preferredWidth: 25
                            verticalAlignment: Text.AlignVCenter
                        }

                        LabelDevice {
                            id: labelMonhtConsoYesterday
                            width: 40
                            height: 15
                            text: "volume"
                            horizontalAlignment: Text.AlignLeft
                            Layout.preferredHeight: 15
                            Layout.minimumWidth: 40
                            Layout.minimumHeight: 15
                            Layout.fillHeight: false
                            font.pointSize: 8
                            Layout.fillWidth: false
                            Layout.maximumWidth: 40
                            Layout.preferredWidth: 40
                            Layout.maximumHeight: 15
                            verticalAlignment: Text.AlignTop
                        }
                    }
                }


                bottomPadding: 2
            }
        }


        Layout.maximumHeight: 40
    }










}

/*##^## Designer {
    D{i:421;anchors_height:155;anchors_width:300;anchors_x:0;anchors_y:0}D{i:500;anchors_height:51;anchors_width:152}
D{i:465;anchors_height:155;anchors_x:0;anchors_y:161}
}
 ##^##*/
