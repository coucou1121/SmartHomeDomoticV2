import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

import io.qt.GlobalEnumerate 1.0

Item
{

    property alias tankObjectName: tank.objectName
    property alias tankTitleText: tankTitle.text
    property alias radioButton3timesTankLiquide: radioButton3times.tankLiquide
    property alias rectangleUnderTitleWarningVisible: rectangleUnderTitleWarning.visible

    property int tankVolumeMax: 5000
    property real warningLowLevel: 500
    property real tankVolumeAcutal: 0
 //   property string warningLowLevelText: objectName + " : Low level reached"
    property int  tankHeightVMax: 1500
    property int tankLiquide : radioButton3timesTankLiquide
    property bool warningActive: false
    property bool isVisibleAtStartup : true

    signal sendWarningLowLevel(string objectName, string objectTitle, int errorNumber, bool warningActive)
    signal sendTankVolumeMaxChanged(string  objectName, int volumeMax)
    signal sendTankWarningLowLevelChanged(string  objectName, int warningLowLevel)
    signal sendTankLiquideFillupChanged(string  objectName, int tankLiquide)
    signal sendTankHeightMaxLevelChanged(string  objectName, int tankHeightVMax)

//    function setObjectName(value)
//    {
//        tank.objectName = value;
//    }

//    function setVolumeMax(value)
//    {
//        labelNumberSettingVolumeNumberInputTo = value;
//    }

//    function setWarningLowLevel(value)
//    {
//        labelNumberSettingLowLevelNumberInputTo = value;
//    }

//    function setHeightVMax(value)
//    {
//        sliderWithDisplayValue.value = value;
//    }

    function setWaterInside()
    {
        tankLevelOil.visible = false
        tankLevelOilEco.visible = false
        tankLevelWater.visible = true
//        radioButton3timesTankLiquide = E_TankLiquidInside.WATER
    }

    function setOilInside()
    {
        tankLevelOil.visible = true
        tankLevelOilEco.visible = false
        tankLevelWater.visible = false
 //       radioButton3timesTankLiquide = E_TankLiquidInside.OIL
    }

    function setOilEcoInside()
    {
        tankLevelOil.visible = false
        tankLevelOilEco.visible = true
        tankLevelWater.visible = false
 //       radioButton3timesTankLiquide = E_TankLiquidInside.ECO_OIL
    }

    function tanklevelCalulation(volumeMax, volumeAcutal)
    {
        var tankLevel = (tankEmpty.width * volumeAcutal)/volumeMax;

        if(tankLevel >= tankEmpty.width)
        {
            tankLevel = tankEmpty.width
        }

        return tankLevel.toString()
    }


    //slot
    function tankCheckLowlevel()
    {
        if(tankVolumeAcutal <= warningLowLevel)
        {
            warningActive = true
        }
        else
        {
            warningActive = false
        }
        rectangleUnderTitleWarningVisible = warningActive
//        console.log("tankCheckLowlevel : " + tank.objectName + " " + warningActive)
        tank.sendWarningLowLevel(tank.objectName, tankTitleText, E_ErrorMessage.ERR_LOW_LEVEL_REACHED, warningActive)
    }


    onRadioButton3timesTankLiquideChanged:
    {
//        console.log(objectName.toString() + ", liquid change!!");
        switch (radioButton3timesTankLiquide)
        {
        case E_TankLiquidInside.WATER :
            tank.setWaterInside()
            sendTankLiquideFillupChanged(objectName, E_TankLiquidInside.WATER)
            break;

        case E_TankLiquidInside.OIL :
            tank.setOilInside()
            sendTankLiquideFillupChanged(objectName, E_TankLiquidInside.OIL)
            break;

        case E_TankLiquidInside.ECO_OIL :
            tank.setOilEcoInside()
            sendTankLiquideFillupChanged(objectName, E_TankLiquidInside.ECO_OIL)
            break;
        default:
            break;
        }
    }

//    onTankLiquideChanged:
//    {
//        console.log(objectName.toString() + ", liquid change!!!");
//        switch (tank.tankLiquide)
//        {
//        case E_TankLiquidInside.WATER :
//            tank.setWaterInside()
//            sendTankLiquideFillupChanged(objectName, E_TankLiquidInside.WATER)
//            break;

//        case E_TankLiquidInside.OIL :
//            tank.setOilInside()
//            sendTankLiquideFillupChanged(objectName, E_TankLiquidInside.OIL)
//            break;

//        case E_TankLiquidInside.ECO_OIL :
//            tank.setOilEcoInside()
//            sendTankLiquideFillupChanged(objectName, E_TankLiquidInside.ECO_OIL)
//            break;
//        default:
//            break;
//        }
//    }

    onTankVolumeMaxChanged:
    {
 //       console.log(objectName + " onTankVolumeMaxChanged")
        sendTankVolumeMaxChanged(tankObjectName, tankVolumeMax)
    }

    onWarningLowLevelChanged:
    {
 //       console.log(objectName + " onWarningLowLevelChanged")
        sendTankWarningLowLevelChanged(tankObjectName, warningLowLevel)
    }

    y: 0
    id: tank
    objectName: "no name"
    width: 320
    height: 250
    clip: true
    rotation: 0

    MouseArea
    {
        id: mouseArea
        clip: false
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        z: 1
        anchors.fill: parent

        onClicked:
        {

        }

        onDoubleClicked:
        {
            if(labelNumberSettingVolume.visible)
            {
                labelNumberSettingVolume.visible = false
                labelNumberSettingLowLevel.visible = false
                radioButton3times.visible = false
                sliderWithDisplayValue.visible = false
            }
            else
            {
                labelNumberSettingVolume.visible = true
                labelNumberSettingLowLevel.visible = true
                radioButton3times.visible = true
                sliderWithDisplayValue.visible = true
            }

        }

        RadioButton3times
        {
            id: radioButton3times
            x: 17
            y: 21
            z:3
            width: 160
            height: 134

            visible: isVisibleAtStartup

            rotation: 90
        }

        LabelNumberSetting
        {
            id: labelNumberSettingVolume
            x: 189
            y: 59
            width: 160
            height: 61
            z: 3

            rotation: 90

            visible: isVisibleAtStartup

            labelNumberText: "Volume [lt]"
            numberInputValue: tank.tankVolumeMax

            onNumberInputValueChanged:
            {
                tank.tankVolumeMax = numberInputValue

                if(labelNumberSettingLowLevel.numberInputValue > tank.tankVolumeMax)
                {
                    labelNumberSettingLowLevel.decreaseNumber()

                }

                labelNumberSettingLowLevel.numberInputTo = tank.tankVolumeMax
                tankCheckLowlevel()
            }


        }

        LabelNumberSetting
        {
            id: labelNumberSettingLowLevel
            x: 121
            y: 58
            z: 3

            rotation: 90
            width: 160
            height: 61

            visible: isVisibleAtStartup

            labelNumberText: "Low Level [lt]"

            numberInputValue: tank.warningLowLevel

            onNumberInputValueChanged:
            {
                tank.warningLowLevel = numberInputValue
                tankCheckLowlevel()
            }
        }

        SliderWithDisplayValue
        {
            id: sliderWithDisplayValue
            x: 0
            y: 171
            z: 3
            width: 300
            height: 79

            visible: isVisibleAtStartup

            buttonTextText: tankHeightVMax


            onValueChanged:
            {
                sendTankHeightMaxLevelChanged(tank.objectName, value)
            }
        }
    }


    Rectangle
    {
        id: tankEmpty
        height: 250
        anchors.rightMargin: 50
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.left: parent.left
        z: -1
        Layout.fillHeight: true
        Layout.fillWidth: true
        border.width: 0
        rotation: 0
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#808080"
            }

            GradientStop {
                position: 0.5
                color: "#cccccc"
            }

            GradientStop {
                position: 0.993
                color: "#333333"
            }

            GradientStop {
                position: 1
                color: "#333333"
            }

        }
    }


    Rectangle
    {
        id: tankLevelOilEco
        width: tanklevelCalulation(tankVolumeMax,tankVolumeAcutal)
        visible: false
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 0
        border.width: 0
        Layout.preferredWidth: 100
        transformOrigin: Item.Center
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#50b450"
            }

            GradientStop {
                position: 0.5
                color: "#b8e1b8"
            }

            GradientStop {
                position: 0.993
                color: "#333333"
            }

            GradientStop {
                position: 1
                color: "#1e471e"
            }
        }
        rotation: 0
    }

    Rectangle
    {
        id: tankLevelOil
        width: tanklevelCalulation(tankVolumeMax,tankVolumeAcutal)
        visible: false
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 0
        border.width: 0
        Layout.preferredWidth: 100
        transformOrigin: Item.Center
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#b4b050"
            }

            GradientStop {
                position: 0.5
                color: "#e1e0b8"
            }

            GradientStop {
                position: 0.993
                color: "#333333"
            }

            GradientStop {
                position: 1
                color: "#47451e"
            }
        }
        rotation: 0
    }

    Rectangle
    {
        id: tankLevelWater
        width: tanklevelCalulation(tankVolumeMax,tankVolumeAcutal)
        visible: true
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 0
        border.width: 0
        Layout.preferredWidth: 100
        transformOrigin: Item.Center
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#50a2b4"
            }

            GradientStop {
                position: 0.5
                color: "#b8dae1"
            }

            GradientStop {
                position: 0.993
                color: "#333333"
            }

            GradientStop {
                position: 1
                color: "#1e3f47"
            }
        }
        rotation: 0
    }

    LabelDevice
    {
        id: tankTitle
        text: "no name"
        anchors.rightMargin: -58
        anchors.leftMargin: 208
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        rotation: 90
    }

    RowLayout
    {
        id: rowLayoutVolumeTankText
        x:  if(tank.tankVolumeAcutal>750)
            {
                tankLevelOil.width-width/2-15
            }
            else
            {
                -35
            }
        rotation: 90
        width: 100
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        LabelDevice
        {
            id: labelVolumeQuantity
            width: 50
            text: tankVolumeAcutal
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            rotation: 0
        }

        LabelDevice
        {
            id: labelVolumeUnity
            width: 50
            text: "lt"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            rotation: 0
        }
    }

    Rectangle {
        id: rectangleUnderTitle
        x: 55
        y: 0
        width: 265
        color: "#ffffff"
        radius: width*0.5
        anchors.right: parent.right
        anchors.bottomMargin: -31
        anchors.topMargin: -29
        clip: false
        z: -2
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#808080"
            }

            GradientStop {
                position: 0.5
                color: "#cccccc"
            }

            GradientStop {
                position: 0.993
                color: "#333333"
            }

            GradientStop {
                position: 1
                color: "#333333"
            }
        }
    }

    Rectangle {
        id: rectangleUnderTitleWarning
        x: 52
        y: -5
        width: 265
        color: "#ffffff"
        radius: width*0.5
        visible: false
        anchors.right: parent.right
        anchors.topMargin: -29
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ff0000"
            }

            GradientStop {
                position: 0.5
                color: "#ff9999"
            }

            GradientStop {
                position: 0.993
                color: "#333333"
            }

            GradientStop {
                position: 1
                color: "#660000"
            }
        }
        anchors.bottomMargin: -31
        anchors.bottom: parent.bottom
        clip: false
        z: -2
        anchors.top: parent.top
    }

}
