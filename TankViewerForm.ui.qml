import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

import io.qt.GlobalEnumerate 1.0

PageBackground {
    property alias tank6TankObjectName: tank6.tankObjectName
    property alias tank5TankObjectName: tank5.tankObjectName
    property alias tank4TankObjectName: tank4.tankObjectName
    property alias tank3TankObjectName: tank3.tankObjectName
    property alias tank2TankObjectName: tank2.tankObjectName
    property alias tank1TankObjectName: tank1.tankObjectName

    property alias tank6TankTitleText: tank6.tankTitleText
    property alias tank5TankTitleText: tank5.tankTitleText
    property alias tank4TankTitleText: tank4.tankTitleText
    property alias tank3TankTitleText: tank3.tankTitleText
    property alias tank2TankTitleText: tank2.tankTitleText
    property alias tank1TankTitleText: tank1.tankTitleText

    property alias tank6Visible: tank6.visible
    property alias tank5Visible: tank5.visible
    property alias tank4Visible: tank4.visible
    property alias tank3Visible: tank3.visible
    property alias tank2Visible: tank2.visible
    property alias tank1Visible: tank1.visible

    property alias tank1TankVolumeMax: tank1.tankVolumeMax
    property alias tank2TankVolumeMax: tank2.tankVolumeMax
    property alias tank3TankVolumeMax: tank3.tankVolumeMax
    property alias tank4TankVolumeMax: tank4.tankVolumeMax
    property alias tank5TankVolumeMax: tank5.tankVolumeMax
    property alias tank6TankVolumeMax: tank6.tankVolumeMax

    property alias tank6WarningLowLevel: tank6.warningLowLevel
    property alias tank5WarningLowLevel: tank5.warningLowLevel
    property alias tank4WarningLowLevel: tank4.warningLowLevel
    property alias tank3WarningLowLevel: tank3.warningLowLevel
    property alias tank2WarningLowLevel: tank2.warningLowLevel
    property alias tank1WarningLowLevel: tank1.warningLowLevel

    property alias tank1TankVolumeAcutal: tank1.tankVolumeAcutal
    property alias tank2TankVolumeAcutal: tank2.tankVolumeAcutal
    property alias tank3TankVolumeAcutal: tank3.tankVolumeAcutal
    property alias tank4TankVolumeAcutal: tank4.tankVolumeAcutal
    property alias tank5TankVolumeAcutal: tank5.tankVolumeAcutal
    property alias tank6TankVolumeAcutal: tank6.tankVolumeAcutal

    property alias tank1TankLiquide: tank1.radioButton3timesTankLiquide
    property alias tank2TankLiquide: tank2.radioButton3timesTankLiquide
    property alias tank3TankLiquide: tank3.radioButton3timesTankLiquide
    property alias tank4TankLiquide: tank4.radioButton3timesTankLiquide
    property alias tank5TankLiquide: tank5.radioButton3timesTankLiquide
    property alias tank6TankLiquide: tank6.radioButton3timesTankLiquide

    property string tank1Text: E_TankObjectName.TANK1
    property string tank2Text: E_TankObjectName.TANK2
    property string tank3Text: E_TankObjectName.TANK3
    property string tank4Text: E_TankObjectName.TANK4
    property string tank5Text: E_TankObjectName.TANK5
    property string tank6Text: E_TankObjectName.TANK6

    property alias tank1TankHeightVMax: tank1.tankHeightVMax
    property alias tank2TankHeightVMax: tank2.tankHeightVMax
    property alias tank3TankHeightVMax: tank3.tankHeightVMax
    property alias tank4TankHeightVMax: tank4.tankHeightVMax
    property alias tank5TankHeightVMax: tank5.tankHeightVMax
    property alias tank6TankHeightVMax: tank6.tankHeightVMax

    width: 900
    height: 800

    id: tankViewerPage
    color: "#222222"
    title: "TankViever"

    GridLayout {
        id: gridLayout
        rowSpacing: -70
        columnSpacing: -100
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        rows: 2
        columns: 3

        Tank
        {
            id: tank1
            visible: true
            objectName: tank1.tankObjectName
            tankTitleText: tank1.tankTitleText
            tankVolumeAcutal: 500
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: false
            Layout.fillWidth: false
            rotation: 270
            //           target: warningCPPReceiver
        }

        Tank
        {
            id: tank2
            visible: true
            objectName: tank2.tankObjectName
            tankObjectName: tank2.tankObjectName
            tankTitleText: tank2.tankTitleText
            tankVolumeAcutal: 900
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: false
            Layout.fillWidth: false
            rotation: 270
        }

        Tank
        {
            id: tank3
            visible: true
            objectName: tank3.tankObjectName
            tankTitleText: tank3.tankTitleText
            tankVolumeAcutal: 3000
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            rotation: 270
        }

        Tank
        {
            id: tank4
            visible: true
            objectName: tank4.tankObjectName
            tankTitleText: tank4.tankTitleText
            tankVolumeAcutal: 5000
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            rotation: 270
        }

        Tank
        {
            id: tank5
            visible: true
            objectName: tank5.tankObjectName
            tankTitleText: tank5.tankTitleText
            tankVolumeAcutal: 5000
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            rotation: 270
            Layout.fillHeight: false
        }

        Tank
        {
            id: tank6
            visible: true
            objectName: tank6.tankObjectName
            tankTitleText: tank6.tankTitleText
            tankVolumeAcutal: 5000
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            rotation: 270
            Layout.fillHeight: false
        }
    }
}
