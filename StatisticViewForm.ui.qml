import QtQuick 2.4
import io.qt.CustomPlotItem 1.0
import QtQuick.Layouts 1.0

PageBackground
{
    //    property alias refreshTimer:  plotViewTemperature.refreshTimer
    property alias customPlotPressure: customPlotPressure
    property alias customPlotHumidity: customPlotHumidity
    property alias customPlotRoomData: customPlotRoomData


    width: 900
    height: 800

    id: statisticView
    color: "#222222"
    title: "Statistic view"

    clip: true

    ColumnLayout {
        anchors.topMargin: 40
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 60
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        CustomPlot
        {
            id: customPlotRoomData
            Layout.preferredHeight: 166
            visible: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            objectName: "customPlotRoomData"
        }

        CustomPlot {
            id: customPlotHumidity
            Layout.preferredHeight: 194
            visible: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            objectName: "customPlotHumidity"
        }

        CustomPlot {
            id: customPlotPressure
            Layout.preferredHeight: 197
            visible: false
            Layout.fillHeight: true
            Layout.fillWidth: true
            objectName: "customPlotPressure"
        }
    }

}
