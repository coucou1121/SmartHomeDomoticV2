import QtQuick 2.4

import io.qt.GlobalEnumerate 1.0

TankViewerForm
{
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
           break;
       case E_TankObjectName.TANK2:
           tank2Visible = isVisible;
           break;
       case E_TankObjectName.TANK3:
           tank3Visible = isVisible;
           break;
       case E_TankObjectName.TANK4:
           tank4Visible = isVisible;
           break;
       case E_TankObjectName.TANK5:
           tank5Visible = isVisible;
           break;
       case E_TankObjectName.TANK6:
           tank6Visible = isVisible;
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

    function setTankLiquideInside(tankObjectID, liquideInside)
    {
//       console.log("setTankLiquideInside : " + tankObjectID + ", liquid change!!! " + liquideInside);
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
}
