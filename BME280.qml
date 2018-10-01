import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item
{
    property alias labelDeviceTemperatureText: labelDeviceTemperature.text
    property alias labelDeviceHumidityText: labelDeviceHumidity.text
    property alias labelDeviceAtmoPressurText: labelDeviceAtmoPressur.text

    function updateValue(temperature, humidity, pressure)
    {
 //       console.log("updateValue : temp : " + temperature + ", humidity : " +  humidity + "pressure : " + pressure);

        labelDeviceTemperatureText = temperature
        labelDeviceHumidityText = humidity
        labelDeviceAtmoPressurText = pressure
        //       radioButton3timesTankLiquide = E_TankLiquidInside.ECO_OIL
    }

    id: item1
    width: 300
    height: 180

    Timer
    {
        signal sendRefreshRoomData()
        property alias refreshTimer: roomDataTimer.interval

        id: roomDataTimer
        objectName: "roomDataTimer"

        //       interval: 1 / 60 * 1000 // 60 Hz
        interval: 100 // 10 Hz
        running: true
        repeat: true
        triggeredOnStart: false
        onTriggered:
        {
            sendRefreshRoomData()
        }
    }

    Frame {
        id: frameTemperature
        anchors.bottomMargin: 2
        anchors.bottom: frameHumidity.top
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        padding: 5

        Image {
            id: imageTemprature
            width: 50
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.minimumWidth: 42
            Layout.preferredHeight: 55
            Layout.preferredWidth: 42
            fillMode: Image.PreserveAspectFit
            antialiasing: true
            clip: false
            source: "Picture/thermometer.png"
        }

        LabelDevice {
            id: labelDeviceTemperature
            text: "0"
            anchors.rightMargin: 5
            anchors.right: labelDeviceTemperatureUnity.left
            anchors.left: imageTemprature.right
            padding: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.minimumWidth: 150
        }

        LabelDevice {
            id: labelDeviceTemperatureUnity
            x: 192
            width: 70
            color: "#cccccc"
            text: "°c"
            topPadding: 5
            padding: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.maximumWidth: 100
        }
    }

    Frame {
        id: frameHumidity
        y: 90
        height: 58
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.left: parent.left
        padding: 5

        Image {
            id: imageHumidity
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.minimumWidth: 42
            Layout.preferredHeight: 58
            Layout.preferredWidth: 40
            source: "Picture/humidity.png"
            clip: false
            antialiasing: true
            fillMode: Image.PreserveAspectFit
        }

        LabelDevice {
            id: labelDeviceHumidity
            text: "0"
            anchors.rightMargin: 5
            anchors.right: labelDeviceHumidityUnity.left
            anchors.left: imageHumidity.right
            padding: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Layout.minimumWidth: 150
        }

        LabelDevice {
            id: labelDeviceHumidityUnity
            width: 70
            color: "#cccccc"
            text: "%"
            padding: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.maximumWidth: 100
        }
    }

    Frame {
        id: frameAtmoPressur
        anchors.leftMargin: 0
        anchors.topMargin: 2
        anchors.bottom: parent.bottom
        anchors.top: frameHumidity.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        padding: 5

        Image {
            id: imageAtmoPressure
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.minimumWidth: 42
            Layout.preferredHeight: 58
            Layout.preferredWidth: 42
            source: "Picture/atmosphericPressure.png"
            clip: false
            fillMode: Image.PreserveAspectFit
            antialiasing: true
        }


        LabelDevice {
            id: labelDeviceAtmoPressur
            text: "0"
            anchors.rightMargin: 5
            anchors.right: labelDeviceAtmoPressurUnity.left
            anchors.left: imageAtmoPressure.right
            padding: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.minimumWidth: 150
        }
        LabelDevice {
            id: labelDeviceAtmoPressurUnity
            x: 226
            width: 70
            color: "#cccccc"
            text: "mbar"
            padding: 5
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            Layout.maximumWidth: 100
        }
    }

}

/*##^## Designer {
    D{i:76;anchors_width:150;anchors_x:37}D{i:74;anchors_height:60;anchors_x:0;anchors_y:0}
D{i:80;anchors_width:150;anchors_x:41;anchors_y:"-8"}D{i:78;anchors_height:42;anchors_y:90}
D{i:85;anchors_width:200;anchors_x:42}D{i:82;anchors_height:46;anchors_y:154}
}
 ##^##*/
