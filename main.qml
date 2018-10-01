import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

//import io.qt.DataSource 1.0

Window
{
    id: window
    width: 1200
    height: 800
    minimumWidth: 1200
    minimumHeight: 800
    visible: true
    title: "Samrt Home Domotic"

    Material.theme: Material.Dark
    Material.accent: Material.DeepPurple

    StackLayout
    {
        id : swipeView
        anchors.bottomMargin: -40
        anchors.leftMargin: 0
        anchors.left: sideBar.right
        anchors.bottom: tabBar.top
        anchors.right: parent.right
        anchors.top: parent.top
        currentIndex: tabBar.currentIndex

        HomeViewer
        {
            id: homeViewer
            objectName: "homeViewer"
            anchors.fill: parent
//            Layout.fillWidth: true
//            Layout.fillHeight: true
        }

        TankViewer
        {
            id: tankViewer
            objectName: "tankViewer"
//            tank1TankObjectName: "tank_1"
            anchors.fill: parent
            Layout.fillHeight: true
            Layout.fillWidth: true
        }



        Setting
        {
            id: settingViewer
            objectName: "settingViewer"
            anchors.fill: parent
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        StatisticView
        {
            id: statisticView
            objectName: "statisticView"
            anchors.fill: parent
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    TabBar
    {
        id: tabBar
        anchors.top: parent.bottom
        anchors.topMargin: -40
        anchors.bottom: parent.bottom
        anchors.left: sideBar.right
        anchors.right: parent.right
        currentIndex: swipeView.currentIndex

        TabButton
        {
            id: tabButtonLight
            x: 0
            text: qsTr("Home")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        TabButton
        {
            id: tabButtonTank
            x: 0
            text:  qsTr("Tank")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
        }


        TabButton
        {
            id: tabButtonSetting
            x: 0
            text: qsTr("Setting")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        TabButton
        {
            id: tabButtonStatistic
            x: 0
            text: qsTr("Statistic")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    SideBar
    {
        id: sideBar
        anchors.right: parent.left
        anchors.rightMargin: -300
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        BME280
        {
            id: bME280
            objectName: "bME280"
            x: 0
            y: 273
        }


//        WarningDisplay
//        {
//            id: warningDisplay
//            objectName: "warningDisplay"
//            x: 14
//            y: 494
//            width: 273
//            height: 82
//        }


    }




    //![2]

    //![2]



}

/*##^## Designer {
    D{i:6;anchors_x:0}D{i:7;anchors_x:0}D{i:5;anchors_height:40;anchors_y:760}D{i:9;anchors_height:800;anchors_width:300}
}
 ##^##*/
