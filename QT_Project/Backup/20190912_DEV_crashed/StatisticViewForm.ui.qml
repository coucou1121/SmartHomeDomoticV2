import QtQuick 2.7
import io.qt.CustomPlotItem 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4

PageBackground {
    //    property alias refreshTimer:  plotViewTemperature.refreshTimer
    property alias mouseAreaStatisticView: mouseAreaStatisticView
    property alias customPlotRoomData: customPlotRoomData
    property alias customPlotTanksData: customPlotTanksData
    property alias customPlotStatistics: customPlotStatistics
    property alias statisticSelectorViewer: statisticSelectorViewer
    property alias frameStatistic: frameStatistic
    
    property alias labelDeviceConsoBeforeText: labelDeviceConsoDayBefore.text
    property alias labelDeviceConsoText: labelDeviceConsoDay.text
    property alias labelDeviceAtmoPressurMaxText: labelDeviceAtmoPressurMaxDay.text
    property alias labelDeviceAtmoPressurMinText: labelDeviceAtmoPressurMinDay.text
    property alias labelDeviceHumidityMinText: labelDeviceHumidityMinDay.text
    property alias labelDeviceHumidityMaxText: labelDeviceHumidityMax.text
    property alias labelDeviceTemperatureMinText: labelDeviceTemperatureMin.text
    property alias labelDeviceTemperatureMaxText: labelDeviceTemperatureMax.text

    property alias customPlotStatisticsConso: customPlotStatisticsConso
    property alias gridLayoutStatistic: gridLayoutStatistic
    property alias columnLayoutPlotStatistic: columnLayoutPlotStatistic
    property alias customPlotStatisticsPressure: customPlotStatisticsPressure
    property alias customPlotStatisticHumidity: customPlotStatisticHumidity
    property alias labelDeviceTemperatureMin: labelDeviceTemperatureMin
    property alias labelDeviceTemperatureMax: labelDeviceTemperatureMax

    
    width: 900
    height: 800
    id: statisticView
    color: "#222222"
    title: "Statistic view"   
    clip: true
    
    MouseArea {
        id: mouseAreaStatisticView
        x: 0
        y: 30
        anchors.fill: parent


        ColumnLayout {
            anchors.bottomMargin: 42
            anchors.topMargin: 30
            anchors.fill: parent

            CustomPlot {
                id: customPlotRoomData
                objectName: "customPlotRoomData"
                visible: true
                Layout.preferredWidth: 900
                Layout.minimumHeight: 50
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            CustomPlot {
                id: customPlotTanksData
                objectName: "customPlotTanksData"
                visible: true
                Layout.preferredWidth: 900
                Layout.minimumHeight: 50
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            GridLayout {
                id: gridLayoutStatistic
                visible: false
                Layout.fillHeight: true
                Layout.fillWidth: true
                rows: 2
                columns: 2

                StastisticSelector {
                    id: statisticSelectorViewer
                    objectName: "statisticSelectorViewer"
                    visible: true
                    Layout.minimumWidth: 200
                    Layout.maximumWidth: 200
                    Layout.minimumHeight: 190
                    Layout.maximumHeight: 190
                    Layout.preferredHeight: 190
                    Layout.preferredWidth: 200
                    Layout.fillWidth: false
                    Layout.fillHeight: false
                }

                ColumnLayout {
                    id: columnLayoutPlotStatistic
                    visible: true
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.rowSpan: 2

                    CustomPlot {
                        id: customPlotStatistics
                        objectName: "customPlotStatistics"
                        visible: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.rowSpan: 2
                    }

                    CustomPlot {
                        id: customPlotStatisticHumidity
                        objectName: "customPlotStatistics"
                        visible: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.rowSpan: 2
                    }

                    CustomPlot {
                        id: customPlotStatisticsPressure
                        objectName: "customPlotStatistics"
                        visible: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.rowSpan: 2
                    }

                    CustomPlot {
                        id: customPlotStatisticsConso
                        objectName: "customPlotStatistics"
                        visible: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.rowSpan: 2
                    }
                }

                Frame {
                    id: frameStatistic
                    visible: true
                    Layout.maximumWidth: 200
                    Layout.minimumWidth: 200
                    Layout.preferredHeight: 273
                    Layout.preferredWidth: 200
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.rowSpan: 2
                    padding: 5
                    topPadding: 0

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.bottom: parent.bottom
                        Layout.maximumHeight: 300
                        Layout.minimumHeight: 200

                        LabelDevice {
                            id: labelDay
                            text: "Today"
                            font.pointSize: 16
                            Layout.maximumWidth: 100
                            Layout.minimumWidth: 100
                            Layout.preferredHeight: 24
                            Layout.preferredWidth: 156
                            Layout.columnSpan: 2
                            horizontalAlignment: Text.AlignLeft
                        }

                        Frame {
                            id: frameTemperatureDay
                            Layout.preferredHeight: 55
                            Layout.preferredWidth: 156
                            Layout.fillWidth: true
                            Layout.fillHeight: false
                            padding: 2
                            rightPadding: 2
                            leftPadding: 2
                            topPadding: 2
                            bottomPadding: 2
                            RowLayout {
                                spacing: 0
                                anchors.fill: parent
                                Image {
                                    id: imageTempratureDay
                                    source: "Picture/thermometer.png"
                                    Layout.maximumWidth: 40
                                    Layout.minimumWidth: 40
                                    Layout.maximumHeight: 40
                                    Layout.minimumHeight: 40
                                    Layout.preferredHeight: 40
                                    Layout.preferredWidth: 40
                                    Layout.rowSpan: 2
                                    clip: false
                                    antialiasing: true
                                    fillMode: Image.PreserveAspectFit
                                }

                                ColumnLayout {
                                    Layout.fillWidth: false
                                    Layout.fillHeight: false
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDeviceTemperatureMax
                                        text: "0"
                                        font.pointSize: 12
                                        Layout.maximumWidth: 70
                                        Layout.minimumWidth: 70
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 70
                                        padding: 5
                                        horizontalAlignment: Text.AlignRight
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    LabelDevice {
                                        id: labelDeviceTemperatureMin
                                        text: "0"
                                        font.pointSize: 12
                                        Layout.minimumWidth: 70
                                        Layout.maximumWidth: 70
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 70
                                        padding: 5
                                        horizontalAlignment: Text.AlignRight
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }

                                ColumnLayout
                                {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDayTempMax
                                        height: 10
                                        text: "max"
                                        font.bold: false
                                        font.pointSize: 8
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.maximumHeight: 10
                                        Layout.minimumHeight: 10
                                        Layout.preferredHeight: 10
                                        Layout.preferredWidth: 40
                                        Layout.fillHeight: true
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignBottom
                                    }

                                    LabelDevice {
                                        id: labelDeviceTemperatureUnity
                                        color: "#cccccc"
                                        text: "°c"
                                        font.pointSize: 12
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.maximumHeight: 25
                                        Layout.minimumHeight: 25
                                        Layout.preferredHeight: 20
                                        Layout.preferredWidth: 40
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                        Layout.rowSpan: 2
                                        padding: 5
                                        leftPadding: 0
                                        topPadding: 5
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    LabelDevice {
                                        id: labelDayTempMin
                                        height: 10
                                        width: 25
                                        text: "min"
                                        font.pointSize: 8
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.maximumHeight: 10
                                        Layout.minimumHeight: 10
                                        Layout.preferredHeight: 10
                                        Layout.preferredWidth: 40
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignBottom
                                    }
                                }
                            }
                        }

                        Frame {
                            id: frameHumidityDay
                            Layout.preferredHeight: 55
                            Layout.preferredWidth: 156
                            Layout.fillHeight: false
                            Layout.fillWidth: true
                            padding: 2
                            leftPadding: 2
                            rightPadding: 2
                            topPadding: 2
                            bottomPadding: 2
                            RowLayout {
                                spacing: 0
                                anchors.fill: parent
                                Image {
                                    id: imageHumidityDay
                                    source: "Picture/humidity.png"
                                    width: 40
                                    Layout.maximumWidth: 40
                                    Layout.minimumWidth: 40
                                    Layout.maximumHeight: 40
                                    Layout.minimumHeight: 40
                                    Layout.preferredHeight: 30
                                    Layout.preferredWidth: 40
                                    Layout.rowSpan: 2
                                    clip: false
                                    antialiasing: true
                                    fillMode: Image.PreserveAspectFit
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDeviceHumidityMax
                                        text: "0"
                                        font.pointSize: 12
                                        Layout.maximumWidth: 70
                                        Layout.minimumWidth: 70
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 70
                                        padding: 5
                                        horizontalAlignment: Text.AlignRight
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    LabelDevice {
                                        id: labelDeviceHumidityMinDay
                                        text: "0"
                                        font.pointSize: 12
                                        Layout.maximumWidth: 70
                                        Layout.minimumWidth: 70
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 70
                                        padding: 5
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignRight
                                    }
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDayHumidityMax
                                        text: "max"
                                        font.bold: false
                                        font.pointSize: 8
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.maximumHeight: 10
                                        Layout.minimumHeight: 10
                                        Layout.preferredHeight: 10
                                        Layout.preferredWidth: 40
                                        Layout.fillHeight: true
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignBottom
                                    }

                                    LabelDevice {
                                        id: labelDeviceHumidityUnityDay
                                        color: "#cccccc"
                                        text: "%"
                                        font.pointSize: 12
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.preferredHeight: 30
                                        Layout.preferredWidth: 40
                                        Layout.rowSpan: 2
                                        padding: 5
                                        leftPadding: 0
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignLeft
                                    }

                                    LabelDevice {
                                        id: labelDayHumidityMin
                                        text: "min"
                                        font.pointSize: 8
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.maximumHeight: 10
                                        Layout.minimumHeight: 10
                                        Layout.preferredHeight: 10
                                        Layout.preferredWidth: 40
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignBottom
                                    }
                                }
                            }
                        }

                        Frame {
                            id: frameAtmoPressurDay
                            Layout.preferredHeight: 55
                            Layout.preferredWidth: 156
                            Layout.fillHeight: false
                            Layout.fillWidth: true
                            padding: 2
                            rightPadding: 2
                            leftPadding: 2
                            topPadding: 2
                            bottomPadding: 2
                            RowLayout {
                                spacing: 0
                                anchors.fill: parent
                                Image {
                                    id: imageAtmoPressureDay
                                    source: "Picture/atmosphericPressure.png"
                                    Layout.maximumWidth: 40
                                    Layout.minimumWidth: 40
                                    Layout.maximumHeight: 40
                                    Layout.minimumHeight: 40
                                    Layout.preferredHeight: 40
                                    Layout.preferredWidth: 40
                                    Layout.rowSpan: 2
                                    clip: false
                                    antialiasing: true
                                    fillMode: Image.PreserveAspectFit
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDeviceAtmoPressurMinDay
                                        text: "0"
                                        font.pointSize: 12
                                        Layout.maximumWidth: 70
                                        Layout.minimumWidth: 70
                                        Layout.maximumHeight: 25
                                        Layout.minimumHeight: 25
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 70
                                        padding: 5
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignRight
                                    }

                                    LabelDevice {
                                        id: labelDeviceAtmoPressurMaxDay
                                        text: "0"
                                        font.pointSize: 12
                                        Layout.maximumWidth: 70
                                        Layout.minimumWidth: 70
                                        Layout.maximumHeight: 25
                                        Layout.minimumHeight: 25
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 70
                                        padding: 5
                                        horizontalAlignment: Text.AlignRight
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDayPressureMin
                                        text: "min"
                                        font.pointSize: 8
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.maximumHeight: 10
                                        Layout.minimumHeight: 10
                                        Layout.preferredHeight: 10
                                        Layout.preferredWidth: 40
                                        Layout.fillHeight: false
                                        Layout.fillWidth: false
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignBottom
                                    }

                                    LabelDevice {
                                        id: labelDeviceAtmoPressurMaxUnityDay
                                        color: "#cccccc"
                                        text: "mbar"
                                        font.pointSize: 12
                                        leftPadding: 0
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.preferredHeight: 30
                                        Layout.preferredWidth: 40
                                        Layout.rowSpan: 2
                                        padding: 5
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    LabelDevice {
                                        id: labelDayPressureMax
                                        text: "max"
                                        font.bold: false
                                        font.pointSize: 8
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.maximumHeight: 10
                                        Layout.minimumHeight: 10
                                        Layout.preferredHeight: 10
                                        Layout.preferredWidth: 40
                                        Layout.fillHeight: false
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignBottom
                                    }
                                }
                            }
                        }

                        Frame {
                            id: frameConsoDay
                            Layout.preferredHeight: 55
                            Layout.preferredWidth: 156
                            Layout.fillHeight: false
                            Layout.fillWidth: true
                            padding: 2
                            rightPadding: 2
                            leftPadding: 2
                            topPadding: 2
                            bottomPadding: 2
                            RowLayout {
                                spacing: 0
                                anchors.fill: parent
                                Image {
                                    id: imageConsoDay
                                    source: "Picture/ConsoOil.png"
                                    Layout.maximumWidth: 40
                                    Layout.minimumWidth: 40
                                    Layout.maximumHeight: 40
                                    Layout.minimumHeight: 40
                                    Layout.preferredHeight: 40
                                    Layout.preferredWidth: 40
                                    Layout.rowSpan: 2
                                    clip: false
                                    antialiasing: true
                                    fillMode: Image.PreserveAspectFit
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDeviceConsoDay
                                        text: "0"
                                        height: 25
                                        font.pointSize: 12
                                        Layout.maximumWidth: 70
                                        Layout.minimumWidth: 70
                                        Layout.maximumHeight: 25
                                        Layout.minimumHeight: 25
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 70
                                        padding: 5
                                        horizontalAlignment: Text.AlignRight
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    LabelDevice {
                                        id: labelDeviceConsoDayBefore
                                        text: "0"
                                        height: 25
                                        font.pointSize: 12
                                        Layout.maximumWidth: 70
                                        Layout.minimumWidth: 70
                                        Layout.maximumHeight: 25
                                        Layout.minimumHeight: 25
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 70
                                        padding: 5
                                        horizontalAlignment: Text.AlignRight
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDayConsoToday
                                        text: "today"
                                        width: 40
                                        font.pointSize: 8
                                        font.bold: false
                                        Layout.maximumWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.maximumHeight: 10
                                        Layout.minimumHeight: 10
                                        Layout.preferredHeight: 10
                                        Layout.preferredWidth: 40
                                        Layout.fillHeight: false
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignBottom
                                    }

                                    LabelDevice {
                                        id: labelDeviceConsoUnityDay
                                        color: "#cccccc"
                                        text: "Lt"
                                        height: 25
                                        Layout.maximumWidth: 30
                                        Layout.minimumWidth: 25
                                        Layout.maximumHeight: 25
                                        Layout.minimumHeight: 25
                                        Layout.preferredHeight: 25
                                        Layout.preferredWidth: 25
                                        Layout.rowSpan: 2
                                        padding: 5
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    LabelDevice {
                                        id: labelDayConsoYesterday
                                        text: "yest."
                                        font.pointSize: 8
                                        height: 15
                                        Layout.maximumWidth: 25
                                        Layout.minimumWidth: 25
                                        Layout.maximumHeight: 15
                                        Layout.minimumHeight: 15
                                        Layout.preferredHeight: 15
                                        Layout.preferredWidth: 25
                                        Layout.fillHeight: false
                                        Layout.fillWidth: false
                                        verticalAlignment: Text.AlignTop
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
        
        
    }
}
