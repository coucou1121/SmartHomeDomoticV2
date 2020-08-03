import QtQuick 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle
{
    property alias buttonTextText: sliderVolumeMax.value

    property int value: (sliderVolumeMax.visualPosition*sliderVolumeMax.to).toFixed(0)

    id: slider

    width: 300
    height: 80
    color: "#00000000"
    border.color: "#00000000"
    border.width: 0


 //   Accessible.role: Accessible.Slider

    GridLayout
    {
        anchors.leftMargin: 2
        anchors.bottomMargin: 0
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        rows: 2
        columns: 4

        Slider
        {
            id: sliderVolumeMax
            Layout.columnSpan: 3
            Layout.preferredHeight: 30
            Layout.preferredWidth: 219
            padding: 5
            stepSize: 1
            from: 0
            to: 2000
            value: 1500

            ToolTip
            {
                id: toolTipText
                parent: sliderVolumeMax.handle
                visible: sliderVolumeMax.pressed
                text: (sliderVolumeMax.visualPosition*sliderVolumeMax.to).toFixed(0)
            }
        }

        LabelNumber
        {
            id: labelNumberHatVMAx
            Layout.rowSpan: 2
            Layout.preferredHeight: 80
            Layout.preferredWidth: 80
            rotation: 90
            labelNumberText: "height\n[mm]"
            textNumberText: slider.value
        }

        Button
        {
            id: buttonInc
            width: 50
            height: 30
            text: qsTr("-")
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: false
            rotation: 90
            Layout.fillHeight: false
            Layout.preferredHeight: 32
            Layout.preferredWidth: 30
            padding: 5
            leftPadding: 0
            rightPadding: 0
            bottomPadding: 0
            topPadding: 0
            checked: false
            enabled: true
            spacing: 0
            highlighted: false
            checkable: true
            font.pixelSize: 20
            onClicked: sliderVolumeMax.decrease()

        }

        Item
        {
            id: spacer
            Layout.preferredWidth: 14
            Layout.preferredHeight: 14
        }

        Button
        {
            id: buttonDec
            width: 50
            height: 30
            text: qsTr("+")
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            rotation: 90
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.preferredHeight: 30
            Layout.preferredWidth: 30
            checked: false
            spacing: 0
            topPadding: 0
            rightPadding: 0
            highlighted: false
            enabled: true
            bottomPadding: 0
            leftPadding: 0
            checkable: true
            padding: 5
            font.pixelSize: 20
            onClicked: sliderVolumeMax.increase()
        }
    }
}

/*##^## Designer {
    D{i:29;anchors_x:0;anchors_y:0}
}
 ##^##*/
