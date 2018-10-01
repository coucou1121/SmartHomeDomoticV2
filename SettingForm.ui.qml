import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

import io.qt.GlobalEnumerate 1.0

PageBackground
{

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

    id: settingPage
    width: 980
    height: 800
    title: "Setting"

    GroupBox
    {
        id: groupBoxSettingTank
        x: 17
        y: 56
        topPadding: 0
        bottomPadding: 2
        padding: 0
        title: ""

        GridLayout
        {
            id: gridLayoutSettingTank
            anchors.fill: parent
            rows: 7
            columns: 3

            LabelDevice
            {
                id: labelDeviceTankSettingTitle
                visible: true
                text: "Tank"
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.rowSpan: 1
                Layout.preferredHeight: 50
                Layout.columnSpan: 3
            }

            CheckBox
            {
                id: checkBoxTank1
                objectName: "checkBoxTank1"
                text: qsTr("")
                checked: true
            }

            TextField
            {
                id: textFieldTank1
                text: memotextFieldTank1
            }

            Item {
                id: spacer
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            CheckBox {
                id: checkBoxTank2
                objectName: "checkBoxTank2"
                text: qsTr("")
                checked: true
            }

            TextField {
                id: textFieldTank2
                text: memotextFieldTank2
            }

            Item {
                id: spacer1
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            CheckBox {
                id: checkBoxTank3
                text: qsTr("")
                checked: true
            }

            TextField {
                id: textFieldTank3
                text: memotextFieldTank3
            }

            Item {
                id: spacer2
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            CheckBox {
                id: checkBoxTank4
                text: qsTr("")
                checked: true
            }

            TextField {
                id: textFieldTank4
                text: memotextFieldTank4
            }


            Item {
                id: spacer3
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            CheckBox {
                id: checkBoxTank5
                text: qsTr("")
                checked: true
            }

            TextField {
                id: textFieldTank5
                text: memotextFieldTank5
            }

            Item {
                id: spacer4
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

            CheckBox {
                id: checkBoxTank6
                text: qsTr("")
                checked: true

            }

            TextField {
                id: textFieldTank6
                text: memotextFieldTank6
            }

            Item {
                id: spacer5
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }

        }

    }

    Connections
    {
        target: checkBoxTank1

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK1, checkBoxTank1.checked)
        }
    }

    Connections
    {
        target: checkBoxTank2

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK2, checkBoxTank2.checked)
        }
    }

    Connections
    {
        target: checkBoxTank3

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK3, checkBoxTank3.checked)
        }
    }

    Connections
    {
        target: checkBoxTank4

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK4, checkBoxTank4.checked)
        }
    }

    Connections
    {
        target: checkBoxTank5

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK5, checkBoxTank5.checked)
        }
    }

    Connections
    {
        target: checkBoxTank6

        onClicked: {
            sendTankIsVisible(E_TankObjectName.TANK6, checkBoxTank6.checked)
        }
    }




}
