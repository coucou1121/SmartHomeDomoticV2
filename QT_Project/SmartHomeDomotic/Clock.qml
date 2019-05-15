import QtQuick 2.0
import QtQuick.Layouts 1.0

PageBackground
{
    id: pageBackground

    property string dateToDay
    property string timeNow

    function timeChanged()
    {
        var date = new Date;
        dateToDay = date.toLocaleDateString(Qt.locale("fr_FR"),"dddd, dd MMMM yyyy")
        timeNow = date.toLocaleString(Qt.locale("fr_FR"),"HH:mm:ss")
    }


    width: 300
    height: 100
    color: "#00000000"

    Timer
    {
        interval: 100;
        running: true;
        repeat: true;
        onTriggered: clock.timeChanged()
    }


    GridLayout {
        anchors.leftMargin: 10
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        rows: 2
        columns: 2

        Image {
            id: logo
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 74
            Layout.preferredWidth: 113
            Layout.fillHeight: true
            Layout.fillWidth: true
            fillMode: Image.PreserveAspectFit
            source: "Picture/mountain_logo.png"
        }

        LabelDevice
        {
            id: labelDeviceTime
            color: "#cdcdcd"
            text: timeNow
            Layout.preferredHeight: 74
            Layout.preferredWidth: 181
            textFormat: Text.PlainText
            Layout.fillWidth: true
            z: 1
            Layout.fillHeight: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        LabelDevice
        {
            id: labelDeviceDate
            color: "#cccccc"
            text: dateToDay
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Layout.preferredHeight: 21
            Layout.preferredWidth: 300
            z: 2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 13
        }
    }



}

/*##^## Designer {
    D{i:20;anchors_x:0;anchors_y:0}
}
 ##^##*/
