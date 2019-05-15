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
    
    
    width: 900
    height: 800
    
    id: statisticView
    color: "#222222"
    property alias customPlotStatisticsConso: customPlotStatisticsConso
    property alias gridLayoutStatistic: gridLayoutStatistic
    property alias columnLayoutPlotStatistic: columnLayoutPlotStatistic
    property alias customPlotStatisticsPressure: customPlotStatisticsPressure
    property alias customPlotStatisticHumidity: customPlotStatisticHumidity
    property alias labelDeviceTemperatureMin: labelDeviceTemperatureMin
    property alias labelDeviceTemperatureMax: labelDeviceTemperatureMax
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
                Layout.preferredWidth: 900
                Layout.minimumHeight: 50
                visible: true
                Layout.fillHeight: true
                Layout.fillWidth: true
                objectName: "customPlotRoomData"
            }

            CustomPlot {
                id: customPlotTanksData
                Layout.preferredWidth: 900
                Layout.minimumHeight: 50
                visible: true
                Layout.fillHeight: true
                Layout.fillWidth: true
                objectName: "customPlotTanksData"
            }

            GridLayout {
                id: gridLayoutStatistic
                visible: true
                Layout.fillHeight: true
                Layout.fillWidth: true
                rows: 2
                columns: 2

                StastisticSelector {
                    id: statisticSelectorViewer
                    Layout.minimumWidth: 200
                    Layout.maximumWidth: 200
                    Layout.maximumHeight: 190
                    Layout.minimumHeight: 190
                    Layout.preferredHeight: 190
                    Layout.fillWidth: false
                    Layout.preferredWidth: 200
                    Layout.fillHeight: false
                    objectName: "statisticSelectorViewer"
                    visible: true
                }

                ColumnLayout {
                    id: columnLayoutPlotStatistic
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    visible: true
                    Layout.rowSpan: 2

                    CustomPlot {
                        id: customPlotStatistics
                        Layout.rowSpan: 2
                        visible: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        objectName: "customPlotStatistics"
                    }

                    CustomPlot {
                        id: customPlotStatisticHumidity
                        visible: true
                        Layout.fillHeight: true
                        objectName: "customPlotStatistics"
                        Layout.rowSpan: 2
                        Layout.fillWidth: true
                    }

                    CustomPlot {
                        id: customPlotStatisticsPressure
                        Layout.fillHeight: true
                        visible: true
                        objectName: "customPlotStatistics"
                        Layout.fillWidth: true
                        Layout.rowSpan: 2
                    }

                    CustomPlot {
                        id: customPlotStatisticsConso
                        visible: true
                        Layout.rowSpan: 2
                        objectName: "customPlotStatistics"
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }

                Frame {
                    id: frameStatistic
                    Layout.maximumWidth: 200
                    Layout.minimumWidth: 200
                    Layout.rowSpan: 2
                    visible: true
                    Layout.preferredWidth: 200
                    Layout.fillWidth: true
                    Layout.fillHeight: false
                    padding: 5
                    Layout.preferredHeight: 273
                    topPadding: 0

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.bottom: parent.bottom

                        LabelDevice {
                            id: labelDay
                            text: "Today"
                            Layout.preferredWidth: 156
                            Layout.minimumWidth: 100
                            font.pointSize: 16
                            Layout.columnSpan: 2
                            Layout.preferredHeight: 24
                            horizontalAlignment: Text.AlignLeft
                            Layout.maximumWidth: 100
                        }

                        Frame {
                            id: frameTemperatureDay
                            leftPadding: 2
                            Layout.preferredWidth: 156
                            Layout.fillWidth: true
                            Layout.fillHeight: false
                            rightPadding: 2
                            padding: 2
                            Layout.preferredHeight: 55
                            topPadding: 2
                            RowLayout {
                                spacing: 0
                                Image {
                                    id: imageTempratureDay
                                    source: "Picture/thermometer.png"
                                    Layout.preferredWidth: 40
                                    Layout.minimumWidth: 40
                                    clip: false
                                    antialiasing: true
                                    fillMode: Image.PreserveAspectFit
                                    Layout.preferredHeight: 40
                                    Layout.maximumHeight: 40
                                    Layout.maximumWidth: 40
                                    Layout.minimumHeight: 40
                                    Layout.rowSpan: 2
                                }

                                ColumnLayout {
                                    spacing: 0
                                    Layout.fillWidth: false
                                    Layout.fillHeight: false
                                    LabelDevice {
                                        id: labelDeviceTemperatureMax
                                        text: "0"
                                        Layout.preferredWidth: 70
                                        verticalAlignment: Text.AlignVCenter
                                        Layout.minimumWidth: 70
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        horizontalAlignment: Text.AlignRight
                                        Layout.maximumWidth: 70
                                    }

                                    LabelDevice {
                                        id: labelDeviceTemperatureMin
                                        text: "0"
                                        Layout.preferredWidth: 70
                                        verticalAlignment: Text.AlignVCenter
                                        Layout.minimumWidth: 70
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        horizontalAlignment: Text.AlignRight
                                        Layout.maximumWidth: 70
                                    }
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDayTempMax
                                        height: 10
                                        text: "max"
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        verticalAlignment: Text.AlignBottom
                                        Layout.fillHeight: true
                                        font.pointSize: 8
                                        Layout.preferredHeight: 10
                                        font.bold: false
                                        Layout.maximumHeight: 10
                                        Layout.maximumWidth: 40
                                        Layout.minimumHeight: 10
                                    }

                                    LabelDevice {
                                        id: labelDeviceTemperatureUnity
                                        color: "#cccccc"
                                        text: "°c"
                                        leftPadding: 0
                                        Layout.preferredWidth: 40
                                        Layout.fillWidth: true
                                        Layout.minimumWidth: 40
                                        verticalAlignment: Text.AlignVCenter
                                        Layout.fillHeight: true
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 20
                                        topPadding: 5
                                        Layout.maximumHeight: 25
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.maximumWidth: 40
                                        Layout.minimumHeight: 25
                                        Layout.rowSpan: 2
                                    }

                                    LabelDevice {
                                        id: labelDayTempMin
                                        width: 25
                                        height: 10
                                        text: "min"
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.fillWidth: true
                                        verticalAlignment: Text.AlignBottom
                                        Layout.fillHeight: true
                                        font.pointSize: 8
                                        Layout.preferredHeight: 10
                                        Layout.maximumHeight: 10
                                        Layout.maximumWidth: 40
                                        Layout.minimumHeight: 10
                                    }
                                }
                                anchors.fill: parent
                            }
                            bottomPadding: 2
                        }

                        Frame {
                            id: frameHumidityDay
                            leftPadding: 2
                            Layout.preferredWidth: 156
                            Layout.fillWidth: true
                            Layout.fillHeight: false
                            rightPadding: 2
                            padding: 2
                            Layout.preferredHeight: 55
                            topPadding: 2
                            RowLayout {
                                spacing: 0
                                Image {
                                    id: imageHumidityDay
                                    width: 40
                                    source: "Picture/humidity.png"
                                    Layout.preferredWidth: 40
                                    Layout.minimumWidth: 40
                                    clip: false
                                    antialiasing: true
                                    fillMode: Image.PreserveAspectFit
                                    Layout.preferredHeight: 30
                                    Layout.maximumHeight: 40
                                    Layout.maximumWidth: 40
                                    Layout.minimumHeight: 40
                                    Layout.rowSpan: 2
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDeviceHumidityMax
                                        text: "0"
                                        Layout.preferredWidth: 70
                                        verticalAlignment: Text.AlignVCenter
                                        Layout.minimumWidth: 70
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        horizontalAlignment: Text.AlignRight
                                        Layout.maximumWidth: 70
                                    }

                                    LabelDevice {
                                        id: labelDeviceHumidityMinDay
                                        text: "0"
                                        Layout.preferredWidth: 70
                                        verticalAlignment: Text.AlignVCenter
                                        Layout.minimumWidth: 70
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        horizontalAlignment: Text.AlignRight
                                        Layout.maximumWidth: 70
                                    }
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDayHumidityMax
                                        text: "max"
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        verticalAlignment: Text.AlignBottom
                                        Layout.fillHeight: true
                                        font.pointSize: 8
                                        Layout.preferredHeight: 10
                                        font.bold: false
                                        Layout.maximumHeight: 10
                                        Layout.maximumWidth: 40
                                        Layout.minimumHeight: 10
                                    }

                                    LabelDevice {
                                        id: labelDeviceHumidityUnityDay
                                        color: "#cccccc"
                                        text: "%"
                                        leftPadding: 0
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        verticalAlignment: Text.AlignVCenter
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 30
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.maximumWidth: 40
                                        Layout.rowSpan: 2
                                    }

                                    LabelDevice {
                                        id: labelDayHumidityMin
                                        text: "min"
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.fillWidth: true
                                        verticalAlignment: Text.AlignBottom
                                        Layout.fillHeight: true
                                        font.pointSize: 8
                                        Layout.preferredHeight: 10
                                        Layout.maximumHeight: 10
                                        Layout.maximumWidth: 40
                                        Layout.minimumHeight: 10
                                    }
                                }
                                anchors.fill: parent
                            }
                            bottomPadding: 2
                        }

                        Frame {
                            id: frameAtmoPressurDay
                            leftPadding: 2
                            Layout.preferredWidth: 156
                            Layout.fillWidth: true
                            Layout.fillHeight: false
                            rightPadding: 2
                            padding: 2
                            Layout.preferredHeight: 55
                            topPadding: 2
                            RowLayout {
                                spacing: 0
                                Image {
                                    id: imageAtmoPressureDay
                                    source: "Picture/atmosphericPressure.png"
                                    Layout.preferredWidth: 40
                                    Layout.minimumWidth: 40
                                    clip: false
                                    antialiasing: true
                                    fillMode: Image.PreserveAspectFit
                                    Layout.preferredHeight: 40
                                    Layout.maximumHeight: 40
                                    Layout.maximumWidth: 40
                                    Layout.minimumHeight: 40
                                    Layout.rowSpan: 2
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDeviceAtmoPressurMinDay
                                        text: "0"
                                        Layout.preferredWidth: 70
                                        verticalAlignment: Text.AlignVCenter
                                        Layout.minimumWidth: 70
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        Layout.maximumHeight: 25
                                        horizontalAlignment: Text.AlignRight
                                        Layout.maximumWidth: 70
                                        Layout.minimumHeight: 25
                                    }

                                    LabelDevice {
                                        id: labelDeviceAtmoPressurMaxDay
                                        text: "0"
                                        Layout.preferredWidth: 70
                                        verticalAlignment: Text.AlignVCenter
                                        Layout.minimumWidth: 70
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        Layout.maximumHeight: 25
                                        horizontalAlignment: Text.AlignRight
                                        Layout.maximumWidth: 70
                                        Layout.minimumHeight: 25
                                    }
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDayPressureMin
                                        text: "min"
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        Layout.fillWidth: false
                                        verticalAlignment: Text.AlignBottom
                                        Layout.fillHeight: false
                                        font.pointSize: 8
                                        Layout.preferredHeight: 10
                                        Layout.maximumHeight: 10
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.maximumWidth: 40
                                        Layout.minimumHeight: 10
                                    }

                                    LabelDevice {
                                        id: labelDeviceAtmoPressurMaxUnityDay
                                        color: "#cccccc"
                                        text: "mbar"
                                        leftPadding: 0
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        verticalAlignment: Text.AlignVCenter
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 30
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.maximumWidth: 40
                                        Layout.rowSpan: 2
                                    }

                                    LabelDevice {
                                        id: labelDayPressureMax
                                        text: "max"
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        verticalAlignment: Text.AlignBottom
                                        Layout.fillHeight: false
                                        font.pointSize: 8
                                        Layout.preferredHeight: 10
                                        font.bold: false
                                        Layout.maximumHeight: 10
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.maximumWidth: 40
                                        Layout.minimumHeight: 10
                                    }
                                }
                                anchors.fill: parent
                            }
                            bottomPadding: 2
                        }

                        Frame {
                            id: frameConsoDay
                            leftPadding: 2
                            Layout.preferredWidth: 156
                            Layout.fillWidth: true
                            Layout.fillHeight: false
                            rightPadding: 2
                            padding: 2
                            Layout.preferredHeight: 55
                            topPadding: 2
                            RowLayout {
                                spacing: 0
                                Image {
                                    id: imageConsoDay
                                    source: "Picture/ConsoOil.png"
                                    Layout.preferredWidth: 40
                                    Layout.minimumWidth: 40
                                    clip: false
                                    antialiasing: true
                                    fillMode: Image.PreserveAspectFit
                                    Layout.preferredHeight: 40
                                    Layout.maximumHeight: 40
                                    Layout.maximumWidth: 40
                                    Layout.rowSpan: 2
                                    Layout.minimumHeight: 40
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDeviceConsoDay
                                        height: 25
                                        text: "0"
                                        Layout.preferredWidth: 70
                                        Layout.minimumWidth: 70
                                        verticalAlignment: Text.AlignVCenter
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        Layout.maximumHeight: 25
                                        horizontalAlignment: Text.AlignRight
                                        Layout.maximumWidth: 70
                                        Layout.minimumHeight: 25
                                    }

                                    LabelDevice {
                                        id: labelDeviceConsoDayBefore
                                        height: 25
                                        text: "0"
                                        Layout.preferredWidth: 70
                                        Layout.minimumWidth: 70
                                        verticalAlignment: Text.AlignVCenter
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        Layout.maximumHeight: 25
                                        horizontalAlignment: Text.AlignRight
                                        Layout.maximumWidth: 70
                                        Layout.minimumHeight: 25
                                    }
                                }

                                ColumnLayout {
                                    spacing: 0
                                    LabelDevice {
                                        id: labelDayConsoToday
                                        width: 40
                                        text: "today"
                                        Layout.preferredWidth: 40
                                        Layout.minimumWidth: 40
                                        verticalAlignment: Text.AlignBottom
                                        Layout.fillHeight: false
                                        font.pointSize: 8
                                        Layout.preferredHeight: 10
                                        font.bold: false
                                        Layout.maximumHeight: 10
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.maximumWidth: 40
                                        Layout.minimumHeight: 10
                                    }

                                    LabelDevice {
                                        id: labelDeviceConsoUnityDay
                                        height: 25
                                        color: "#cccccc"
                                        text: "Lt"
                                        Layout.preferredWidth: 25
                                        Layout.minimumWidth: 25
                                        verticalAlignment: Text.AlignVCenter
                                        font.pointSize: 12
                                        padding: 5
                                        Layout.preferredHeight: 25
                                        Layout.maximumHeight: 25
                                        horizontalAlignment: Text.AlignLeft
                                        Layout.maximumWidth: 30
                                        Layout.minimumHeight: 25
                                        Layout.rowSpan: 2
                                    }

                                    LabelDevice {
                                        id: labelDayConsoYesterday
                                        height: 15
                                        text: "yest."
                                        Layout.preferredWidth: 25
                                        Layout.minimumWidth: 25
                                        Layout.fillWidth: false
                                        verticalAlignment: Text.AlignTop
                                        Layout.fillHeight: false
                                        font.pointSize: 8
                                        Layout.preferredHeight: 15
                                        Layout.maximumHeight: 15
                                        Layout.maximumWidth: 25
                                        Layout.minimumHeight: 15
                                    }
                                }
                                anchors.fill: parent
                            }
                            bottomPadding: 2
                        }
                    }
                    Layout.maximumHeight: 300
                    Layout.minimumHeight: 200
                }
            }
        }
        
        
    }
}
