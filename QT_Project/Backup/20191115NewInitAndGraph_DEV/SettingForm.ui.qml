import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

import io.qt.GlobalEnumerate 1.0

PageBackground {

    property alias checkBoxTank1Checked: checkBoxTank1.checked
    property alias checkBoxTank2Checked: checkBoxTank2.checked
    property alias checkBoxTank3Checked: checkBoxTank3.checked
    property alias checkBoxTank4Checked: checkBoxTank4.checked
    property alias checkBoxTank5Checked: checkBoxTank5.checked
    property alias checkBoxTank6Checked: checkBoxTank6.checked

    property alias textFieldTank1Text: textFieldTank1.text
    property alias textFieldTank2Text: textFieldTank2.text
    property alias textFieldTank3Text: textFieldTank3.text
    property alias textFieldTank4Text: textFieldTank4.text
    property alias textFieldTank5Text: textFieldTank5.text
    property alias textFieldTank6Text: textFieldTank6.text

    property alias textFieldTank6: textFieldTank6
    property alias textFieldTank5: textFieldTank5
    property alias textFieldTank4: textFieldTank4
    property alias textFieldTank3: textFieldTank3
    property alias textFieldTank2: textFieldTank2
    property alias textFieldTank1: textFieldTank1

    property alias checkBoxTank6: checkBoxTank6
    property alias checkBoxTank5: checkBoxTank5
    property alias checkBoxTank4: checkBoxTank4
    property alias checkBoxTank3: checkBoxTank3
    property alias checkBoxTank2: checkBoxTank2
    property alias checkBoxTank1: checkBoxTank1

    property alias labelNumberSettingGraphicReccordTime: labelNumberSettingGraphicReccordTime
    property alias labelNumberVolumePIDCoef: labelNumberVolumePIDCoef
    property alias checkBoxCalibrationChecked: checkBoxCalibration.checked
    property alias buttonSettingCloseApplication: buttonSettingCloseApplication
    property alias groupBoxSettingStatisticEnabled: groupBoxSettingStatistic.enabled

    property alias spinBoxPressurreTank1: spinBoxPressurreTank1
    property alias spinBoxPressurreTank2: spinBoxPressurreTank2
    property alias spinBoxPressurreTank3: spinBoxPressurreTank3
    property alias spinBoxPressurreTank4: spinBoxPressurreTank4
    property alias spinBoxPressurreTank5: spinBoxPressurreTank5
    property alias spinBoxPressurreTank6: spinBoxPressurreTank6

    id: settingPage
    width: 980
    height: 800
    title: "Setting"

    GroupBox {
        id: groupBoxSettingTank
        x: 17
        y: 56
        topPadding: 0
        bottomPadding: 5
        padding: 0
        title: ""

        GridLayout {
            anchors.rightMargin: 5
            anchors.fill: parent
            rows: 7
            columns: 3

            LabelDevice {
                id: labelDeviceTankSettingTitle
                visible: true
                text: "Tank"
                Layout.preferredWidth: 252
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.rowSpan: 1
                Layout.preferredHeight: 50
                Layout.columnSpan: 2
            }

            LabelDevice {
                id: labelDeviceTankPressure
                text: "Patm Offset"
                Layout.maximumWidth: 120
                Layout.minimumWidth: 120
                Layout.preferredWidth: 120
                verticalAlignment: Text.AlignBottom
                font.pointSize: 12
                Layout.preferredHeight: 50
                Layout.rowSpan: 1
                Layout.fillHeight: false
                Layout.fillWidth: true
                visible: true
            }

            CheckBox {
                id: checkBoxTank1
                objectName: "checkBoxTank1"
                text: qsTr("")
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.preferredHeight: 40
                Layout.maximumWidth: 46
                Layout.minimumWidth: 46
                Layout.preferredWidth: 46
                enabled: true
                autoExclusive: false
                checked: true
            }

            TextField {
                id: textFieldTank1
                text: memotextFieldTank1
                Layout.fillWidth: true
            }

            SpinBox {
                id: spinBoxPressurreTank1
                Layout.minimumHeight: 40
                Layout.maximumHeight: 40
                Layout.maximumWidth: 120
                Layout.minimumWidth: 120
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                from: -100
                to: 1000
                stepSize: 1
            }

            CheckBox {
                id: checkBoxTank2
                objectName: "checkBoxTank2"
                text: qsTr("")
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.preferredHeight: 401
                Layout.maximumWidth: 46
                Layout.minimumWidth: 46
                Layout.preferredWidth: 46
                enabled: true
                autoExclusive: false
                checked: true
            }

            TextField {
                id: textFieldTank2
                text: memotextFieldTank2
                Layout.fillWidth: true
            }

            SpinBox {
                id: spinBoxPressurreTank2
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.maximumWidth: 120
                Layout.minimumWidth: 120
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                from: -100
                to: 1000
                stepSize: 1
            }

            CheckBox {
                id: checkBoxTank3
                text: qsTr("")
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.preferredHeight: 40
                Layout.maximumWidth: 46
                Layout.minimumWidth: 46
                Layout.preferredWidth: 46
                enabled: true
                checked: true
            }

            TextField {
                id: textFieldTank3
                text: memotextFieldTank3
                Layout.fillWidth: true
            }

            SpinBox {
                id: spinBoxPressurreTank3
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.maximumWidth: 120
                Layout.minimumWidth: 120
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                from: -100
                to: 1000
                stepSize: 1
            }

            CheckBox {
                id: checkBoxTank4
                text: qsTr("")
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.preferredHeight: 40
                Layout.maximumWidth: 46
                Layout.minimumWidth: 46
                Layout.preferredWidth: 46
                enabled: true
                checked: true
            }

            TextField {
                id: textFieldTank4
                text: memotextFieldTank4
                Layout.fillWidth: true
            }

            SpinBox {
                id: spinBoxPressurreTank4
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.maximumWidth: 120
                Layout.minimumWidth: 120
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                from: -100
                to: 1000
                stepSize: 1
            }

            CheckBox {
                id: checkBoxTank5
                text: qsTr("")
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.preferredHeight: 40
                Layout.maximumWidth: 46
                Layout.minimumWidth: 46
                Layout.preferredWidth: 46
                enabled: true
                checked: true
            }

            TextField {
                id: textFieldTank5
                text: memotextFieldTank5
                Layout.fillWidth: true
            }

            SpinBox {
                id: spinBoxPressurreTank5
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.maximumWidth: 120
                Layout.minimumWidth: 120
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                from: -100
                to: 1000
                stepSize: 1
            }

            CheckBox {
                id: checkBoxTank6
                text: qsTr("")
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.preferredHeight: 40
                Layout.maximumWidth: 46
                Layout.minimumWidth: 46
                Layout.preferredWidth: 46
                checked: true
            }

            TextField {
                id: textFieldTank6
                text: memotextFieldTank6
                Layout.fillWidth: true
            }

            SpinBox {
                id: spinBoxPressurreTank6
                Layout.maximumHeight: 40
                Layout.minimumHeight: 40
                Layout.maximumWidth: 120
                Layout.minimumWidth: 120
                Layout.preferredHeight: 40
                Layout.preferredWidth: 120
                from: -100
                to: 1000
                stepSize: 1
            }
        }
    }

    Connections {
        target: checkBoxTank1

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK1, checkBoxTank1.checked)
            checkBoxTank2.enabled = checkBoxTank1Checked ? true : false
        }
    }

    Connections {
        target: checkBoxTank2

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK2, checkBoxTank2.checked)
            checkBoxTank3.enabled = checkBoxTank2Checked ? true : false
            checkBoxTank1.enabled = checkBoxTank2Checked ? false : true
        }
    }

    Connections {
        target: checkBoxTank3

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK3, checkBoxTank3.checked)
            checkBoxTank4.enabled = checkBoxTank3Checked ? true : false
            checkBoxTank2.enabled = checkBoxTank3Checked ? false : true
        }
    }

    Connections {
        target: checkBoxTank4

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK4, checkBoxTank4.checked)
            checkBoxTank5.enabled = checkBoxTank4Checked ? true : false
            checkBoxTank3.enabled = checkBoxTank4Checked ? false : true
        }
    }

    Connections {
        target: checkBoxTank5

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK5, checkBoxTank5.checked)
            checkBoxTank6.enabled = checkBoxTank5Checked ? true : false
            checkBoxTank4.enabled = checkBoxTank5Checked ? false : true
        }
    }

    Connections {
        target: checkBoxTank6

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK6, checkBoxTank6.checked)
            checkBoxTank5.enabled = checkBoxTank6Checked ? false : true
        }
    }

    GroupBox {
        id: groupBoxSettingStatistic
        x: 432
        y: 56
        width: 250
        height: 125
        enabled: true
        padding: 0
        rightPadding: 10
        leftPadding: 10
        bottomPadding: 0
        topPadding: 0
        title: qsTr("")

        ColumnLayout {
            id: columnLayoutSettingStatistic
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left

            LabelDevice {
                id: labelDevice
                height: 50
                text: "Statistic"
                Layout.maximumHeight: 50
                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: true
            }

            LabelNumberSetting {
                id: labelNumberSettingGraphicReccordTime
                height: 60
                Layout.maximumHeight: 60
                Layout.minimumHeight: 60
                Layout.preferredHeight: 60
                Layout.fillWidth: true
                textFormat: Text.PlainText
                numberInputTo: 24
                numberInputStepSize: 1
                numberInputFrom: 1
                labelNumberText: "Reccord Time [hours]"
            }
        }
    }

    CheckBox {
        id: checkBoxCalibration
        x: 142
        y: 13
        width: 145
        height: 24
        text: qsTr("On calibration")
    }

    Button {
        id: buttonSettingCloseApplication
        x: 17
        y: 0
        width: 50
        height: 50
        text: ""
        highlighted: false

        //        background: Rectangle
        //        {
        //            implicitWidth: buttonSettingCloseApplication.width
        //            implicitHeight: buttonSettingCloseApplication.height
        //            color: "#a20000"
        //            border.color: "#26282a"
        //            border.width: 1
        //            radius: 4
        //        }
        background: Image {
            id: imgClose
            anchors.fill: parent
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 74
            Layout.preferredWidth: 113
            Layout.fillHeight: true
            Layout.fillWidth: true
            source: "Picture/round_close_button.png"
        }
    }

    GroupBox {
        id: groupBoxSettingStatistic1
        x: 432
        y: 187
        width: 250
        height: 125
        enabled: true
        leftPadding: 10
        bottomPadding: 0
        padding: 0
        rightPadding: 10
        title: qsTr("")
        ColumnLayout {
            id: columnLayoutSettingStatistic1
            anchors.right: parent.right
            LabelDevice {
                id: labelDevice1
                height: 50
                text: "Volume PID Coef"
                Layout.maximumHeight: 50
                Layout.preferredHeight: 50
                Layout.minimumHeight: 50
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: true
            }

            LabelNumberSetting {
                id: labelNumberVolumePIDCoef
                height: 60
                numberInputValue: 0
                textFormat: Text.PlainText
                numberInputFrom: -100
                Layout.maximumHeight: 60
                Layout.preferredHeight: 60
                Layout.minimumHeight: 60
                labelNumberText: "PID Coef / 100"
                numberInputTo: 100
                Layout.fillWidth: true
                numberInputStepSize: 1
            }
            anchors.top: parent.top
            anchors.left: parent.left
        }
        topPadding: 0
    }
}
