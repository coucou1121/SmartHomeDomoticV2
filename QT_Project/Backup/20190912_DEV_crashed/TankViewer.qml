import QtQuick 2.4

import io.qt.GlobalEnumerate 1.0

TankViewerForm
{
    property bool appOnCalibration: false

    width: 900
    height: 800

    function setTankTitleText(tankObjectID, titleText)
    {
        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1TankTitleText = titleText;
            break;
        case E_TankObjectName.TANK2:
            tank2TankTitleText = titleText;
            break;
        case E_TankObjectName.TANK3:
            tank3TankTitleText = titleText;
            break;
        case E_TankObjectName.TANK4:
            tank4TankTitleText = titleText;
            break;
        case E_TankObjectName.TANK5:
            tank5TankTitleText = titleText;
            break;
        case E_TankObjectName.TANK6:
            tank6TankTitleText = titleText;
            break;
        }
    }

    function setTankObjectName(tankObjectID, objectName)
    {
        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1TankObjectName = objectName;
            break;
        case E_TankObjectName.TANK2:
            tank2TankObjectName = objectName;
            break;
        case E_TankObjectName.TANK3:
            tank3TankObjectName = objectName;
            break;
        case E_TankObjectName.TANK4:
            tank4TankObjectName = objectName;
            break;
        case E_TankObjectName.TANK5:
            tank5TankObjectName = objectName;
            break;
        case E_TankObjectName.TANK6:
            tank6TankObjectName = objectName;
            break;
        }
    }

    function setTankIsVisible(tankObjectID, isVisible)
    {
        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1Visible = isVisible;
            tank1.isSelectedOnSetting = isVisible;
            tank1.tankCheckLowlevel()
            break;
        case E_TankObjectName.TANK2:
            tank2Visible = isVisible;
            tank2.isSelectedOnSetting = isVisible;
            tank2.tankCheckLowlevel()
            break;
        case E_TankObjectName.TANK3:
            tank3Visible = isVisible;
            tank3.isSelectedOnSetting = isVisible;
            tank3.tankCheckLowlevel()
            break;
        case E_TankObjectName.TANK4:
            tank4Visible = isVisible;
            tank4.isSelectedOnSetting = isVisible;
            tank4.tankCheckLowlevel()
            break;
        case E_TankObjectName.TANK5:
            tank5Visible = isVisible;
            tank5.isSelectedOnSetting = isVisible;
            tank5.tankCheckLowlevel()
            break;
        case E_TankObjectName.TANK6:
            tank6Visible = isVisible;
            tank6.isSelectedOnSetting = isVisible;
            tank6.tankCheckLowlevel()
            break;
        }
    }

    function setTankVolumeMax(tankObjectID, volumeMax)
    {
        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1TankVolumeMax = volumeMax;
            break;
        case E_TankObjectName.TANK2:
            tank2TankVolumeMax = volumeMax;
            break;
        case E_TankObjectName.TANK3:
            tank3TankVolumeMax = volumeMax;
            break;
        case E_TankObjectName.TANK4:
            tank4TankVolumeMax = volumeMax;
            break;
        case E_TankObjectName.TANK5:
            tank5TankVolumeMax = volumeMax;
            break;
        case E_TankObjectName.TANK6:
            tank6TankVolumeMax = volumeMax;
            break;
        }
    }

    function setWarningLowLevel(tankObjectID, warningLowLevel)
    {
        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1WarningLowLevel = warningLowLevel;
            break;
        case E_TankObjectName.TANK2:
            tank2WarningLowLevel = warningLowLevel;
            break;
        case E_TankObjectName.TANK3:
            tank3WarningLowLevel = warningLowLevel;
            break;
        case E_TankObjectName.TANK4:
            tank4WarningLowLevel = warningLowLevel;
            break;
        case E_TankObjectName.TANK5:
            tank5WarningLowLevel = warningLowLevel;
            break;
        case E_TankObjectName.TANK6:
            tank6WarningLowLevel = warningLowLevel;
            break;
        }
    }

    function setTankVolumeActual(tankObjectID, volumeActual)
    {
        if(!appOnCalibration)
        {
            switch(tankObjectID)
            {
            case E_TankObjectName.TANK1:
                tank1TankVolumeAcutal = volumeActual;
                break;
            case E_TankObjectName.TANK2:
                tank2TankVolumeAcutal = volumeActual;
                break;
            case E_TankObjectName.TANK3:
                tank3TankVolumeAcutal = volumeActual;
                break;
            case E_TankObjectName.TANK4:
                tank4TankVolumeAcutal = volumeActual;
                break;
            case E_TankObjectName.TANK5:
                tank5TankVolumeAcutal = volumeActual;
                break;
            case E_TankObjectName.TANK6:
                tank6TankVolumeAcutal = volumeActual;
                break;
            }
        }
    }

    function setTankLiquideInside(tankObjectID, liquideInside)
    {
        console.log("setTankLiquideInside : " + tankObjectID + ", liquid change!!! " + liquideInside);
        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1TankLiquide = liquideInside;
            break;
        case E_TankObjectName.TANK2:
            tank2TankLiquide = liquideInside;
            break;
        case E_TankObjectName.TANK3:
            tank3TankLiquide = liquideInside;
            break;
        case E_TankObjectName.TANK4:
            tank4TankLiquide = liquideInside;
            break;
        case E_TankObjectName.TANK5:
            tank5TankLiquide = liquideInside;
            break;
        case E_TankObjectName.TANK6:
            tank6TankLiquide = liquideInside;
            break;
        }
    }

    function setHeightVMaxValue(tankObjectID, heightVMaxValue)
    {
        //       console.log("setHeightVMaxValue : " + tankObjectID + ", " + heightVMaxValue);
        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1TankHeightVMax = heightVMaxValue;
            break;
        case E_TankObjectName.TANK2:
            tank2TankHeightVMax = heightVMaxValue;
            break;
        case E_TankObjectName.TANK3:
            tank3TankHeightVMax = heightVMaxValue;
            break;
        case E_TankObjectName.TANK4:
            tank4TankHeightVMax = heightVMaxValue;
            break;
        case E_TankObjectName.TANK5:
            tank5TankHeightVMax = heightVMaxValue;
            break;
        case E_TankObjectName.TANK6:
            tank6TankHeightVMax = heightVMaxValue;
            break;
        }
    }

    function checkTankIsInWarning(tankObjectID)
    {
        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            tank1.memoWarningActive = false;
            tank1.tankCheckLowlevel();
            break;
        case E_TankObjectName.TANK2:
            tank2.memoWarningActive = false;
            tank2.tankCheckLowlevel();
            break;
        case E_TankObjectName.TANK3:
            tank3.memoWarningActive = false;
            tank3.tankCheckLowlevel();
            break;
        case E_TankObjectName.TANK4:
            tank4.memoWarningActive = false;
            tank4.tankCheckLowlevel();
            break;
        case E_TankObjectName.TANK5:
            tank5.memoWarningActive = false;
            tank5.tankCheckLowlevel();
            break;
        case E_TankObjectName.TANK6:
            tank6.memoWarningActive = false;
            tank6.tankCheckLowlevel();
            break;
        }
    }

    function setOnCalibration(onCalibration)
    {
        appOnCalibration = onCalibration
    }
}
