import QtQuick 2.4

import io.qt.GlobalEnumerate 1.0

HomeViewerForm
{
    property int linePosition: 0
    property int cursorPosition : textEditAtStartup.cursorPosition
    property int lineCounter : textEditAtStartup.lineCount
    property int nbMaxLineInTextEdit: 16
    property int memoCursorPosition : 0
    property variant textLenghtArray: []
    property int nbTankIsVisible : 0
    property bool tank1isVisible: false
    property bool tank2isVisible: false
    property bool tank3isVisible: false
    property bool tank4isVisible: false
    property bool tank5isVisible: false
    property bool tank6isVisible: false

    function setAllTitleText(homeViewerDevice, titleText)
    {
        //        console.log("setTankIsVisible ID: " + tankObjectID + " ,is visible" + isVisible)

        switch(homeViewerDevice)
        {
        case E_HomePageObject.HOMEBME280:
            textBME280Text = titleText;
            break;
        case E_HomePageObject.HOMETANK1:
            tank1textNameText = titleText;
            break;
        case E_HomePageObject.HOMETANK2:
            tank2textNameText = titleText;
            break;
        case E_HomePageObject.HOMETANK3:
            tank3textNameText = titleText;
            break;
        case E_HomePageObject.HOMETANK4:
            tank4textNameText = titleText;
            break;
        case E_HomePageObject.HOMETANK5:
            tank5textNameText = titleText;
            break;
        case E_HomePageObject.HOMETANK6:
            tank6textNameText = titleText;
            break;
        case E_HomePageObject.HOMESENSOR1:
            textSensor1Text = titleText;
            break;
        case E_HomePageObject.HOMESENSOR2:
            textSensor2Text = titleText;
            break;
        case E_HomePageObject.HOMESENSOR3:
            textSensor3Text = titleText;
            break;
        case E_HomePageObject.HOMESENSOR4:
            textSensor4Text = titleText;
            break;
        case E_HomePageObject.HOMESENSOR5:
            textSensor5Text = titleText;
            break;
        case E_HomePageObject.HOMESENSOR6:
            textSensor6Text = titleText;
            break;
        case E_HomePageObject.HOMEAD1115_1:
            textAD1Text = titleText;
            break;
        case E_HomePageObject.HOMEAD1115_2:
            textAD2Text = titleText;
            break;
        default :
            break;
        }
    }

    function addTextToDisplay(errorText)
    {
        memoCursorPosition = cursorPosition;
        textEditAtStartup.insert(cursorPosition,errorText + "\n")
        textLenghtArray.push(cursorPosition - memoCursorPosition)

        //        console.log("addTextToDisplay" + errorText + " at line " +
        //                    linePosition + ", cursor " + cursorPosition +
        //                    ", nb line : " + lineCounter + ", nb cara : " + (cursorPosition - memoCursorPosition))


        if(lineCounter>nbMaxLineInTextEdit + 1)
        {
            textEditAtStartup.remove(0,textLenghtArray[0])
            textLenghtArray.splice(0,1)
        }

//        console.log("Array size " + textLenghtArray.length + ", first element : " + textLenghtArray[0])

    }

    function setTankTitleText(tankObjectID, titleText)
    {
        //        console.log("setTankTitleText" + titleText)

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1textNameText = titleText
            break;
        case E_TankObjectName.TANK2:
            tank2textNameText = titleText;
            break;
        case E_TankObjectName.TANK3:
            tank3textNameText = titleText;
            break;
        case E_TankObjectName.TANK4:
            tank4textNameText = titleText;
            break;
        case E_TankObjectName.TANK5:
            tank5textNameText = titleText;
            break;
        case E_TankObjectName.TANK6:
            tank6textNameText = titleText;
            break;
        }
    }

    function setTankIsVisible(tankObjectID, isVisible)
    {

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1rectangleVisible = isVisible;
            rectangleSensor1Visible = isVisible;
            tank1isVisible = isVisible;
            break;
        case E_TankObjectName.TANK2:
            tank2rectangleVisible = isVisible;
            rectangleSensor2Visible = isVisible;
            tank2isVisible = isVisible;
            break;
        case E_TankObjectName.TANK3:
            tank3rectangleVisible = isVisible;
            rectangleSensor3Visible = isVisible;
            tank3isVisible = isVisible;
            break;
        case E_TankObjectName.TANK4:
            tank4rectangleVisible = isVisible;
            rectangleSensor4Visible = isVisible;
            tank4isVisible = isVisible;
            break;
        case E_TankObjectName.TANK5:
            tank5rectangleVisible = isVisible;
            rectangleSensor5Visible = isVisible;
            tank5isVisible = isVisible;
            break;
        case E_TankObjectName.TANK6:
            tank6rectangleVisible = isVisible;
            rectangleSensor6Visible = isVisible;
            tank6isVisible = isVisible;
            break;
        }

        checkWitchADShouldBeVisible();

    }

    function checkWitchADShouldBeVisible()
    {
        nbTankIsVisible = 0;
        nbTankIsVisible = tank1isVisible + tank2isVisible + tank3isVisible +
                          tank4isVisible + tank5isVisible + tank6isVisible;
        rectangleAD1Visible = nbTankIsVisible;
        rectangleAD2Visible = nbTankIsVisible > 4 ? true : false;
    }

    function changeColorBME280(color)
    {
        rectangleBME280Color = color;
    }

    function changeColorAD1115_1(color)
    {
        rectangleAD1Color = color;
    }

    function changeColorAD1115_2(color)
    {
        rectangleAD2Color = color;
    }

    function setTankVolumeActual(tankObjectID, volumeActual)
    {
        //        console.log("setTankTitleText" + titleText)

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1textQuantityText = volumeActual
            break;
        case E_TankObjectName.TANK2:
            tank2textQuantityText = volumeActual;
            break;
        case E_TankObjectName.TANK3:
            tank3textQuantityText = volumeActual;
            break;
        case E_TankObjectName.TANK4:
            tank4textQuantityText = volumeActual;
            break;
        case E_TankObjectName.TANK5:
            tank5textQuantityText = volumeActual;
            break;
        case E_TankObjectName.TANK6:
            tank6textQuantityText = volumeActual;
            break;
        }
    }

    function setTankColor(tankObjectID, tankColor)
    {
        //        console.log("setTankTitleText" + titleText)

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1rectangleColor = tankColor
            break;
        case E_TankObjectName.TANK2:
            tank2rectangleColor = tankColor;
            break;
        case E_TankObjectName.TANK3:
            tank3rectangleColor = tankColor;
            break;
        case E_TankObjectName.TANK4:
            tank4rectangleColor = tankColor;
            break;
        case E_TankObjectName.TANK5:
            tank5rectangleColor = tankColor;
            break;
        case E_TankObjectName.TANK6:
            tank6rectangleColor = tankColor;
            break;
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
