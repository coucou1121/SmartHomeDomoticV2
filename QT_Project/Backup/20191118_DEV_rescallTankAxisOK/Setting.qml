import QtQuick 2.4

import io.qt.Setting 1.0

import io.qt.GlobalEnumerate 1.0

SettingForm
{
    signal sendTankIsVisible(int tankObjectID, bool isVisible)
    signal sendTankTitleChanged(int tankObjectID, string title)
    signal sendTankOffsetPressureChanged(int tankObjectID, int offsetValue)
    signal sendGraphReccordTimesChanged(int reccordTime)
    signal sendOnCalibrationMode(bool onCalibration)
    signal sendCloseApplication()
    signal sendVolumePIDChanged(int PIDValue)
    signal sendVolumeATMChanged()

    property string memotextFieldTank1: "1"
    property string memotextFieldTank2: "2"
    property string memotextFieldTank3: "3"
    property string memotextFieldTank4: "4"
    property string memotextFieldTank5: "5"
    property string memotextFieldTank6: "6"

    buttonSettingCloseApplication.onReleased:
    {
        sendCloseApplication()
    }


    labelNumberSettingGraphicReccordTime.numberInputFrom: 1
    labelNumberSettingGraphicReccordTime.numberInputTo:24
    labelNumberSettingGraphicReccordTime.numberInputValue: 24
    labelNumberSettingGraphicReccordTime.numberInputStepSize: 1
    labelNumberVolumePIDCoef.numberInputValue: 0

    textFieldTank1.onFocusChanged:
    {
        memotextFieldTank1 = textFieldTank1Text
    }

    textFieldTank2.onFocusChanged:
    {
        memotextFieldTank2 = textFieldTank2Text
    }

    textFieldTank3.onFocusChanged:
    {
        memotextFieldTank3 = textFieldTank3Text
    }

    textFieldTank4.onFocusChanged:
    {
        memotextFieldTank4 = textFieldTank4Text
    }

    textFieldTank5.onFocusChanged:
    {
        memotextFieldTank5 = textFieldTank5Text
    }

    textFieldTank6.onFocusChanged:
    {
        memotextFieldTank6 = textFieldTank6Text
    }

    textFieldTank1.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK1, textFieldTank1Text)
    }

    textFieldTank2.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK2, textFieldTank2Text)
    }

    textFieldTank3.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK3, textFieldTank3Text)
    }

    textFieldTank4.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK4, textFieldTank4Text)
    }

    textFieldTank5.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK5, textFieldTank5Text)
    }

    textFieldTank6.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK6, textFieldTank6Text)
    }

    textFieldTank1.onAccepted:
    {
        textFieldTank1.focus=false
    }

    textFieldTank2.onAccepted:
    {
        textFieldTank2.focus=false
    }

    textFieldTank3.onAccepted:
    {
        textFieldTank3.focus=false
    }

    textFieldTank4.onAccepted:
    {
        textFieldTank4.focus=false
    }

    textFieldTank5.onAccepted:
    {
        textFieldTank5.focus=false
    }

    textFieldTank6.onAccepted:
    {
        textFieldTank6.focus=false
    }

    spinBoxPressurreTank1.onValueChanged:
    {
        sendTankOffsetPressureChanged(E_TankObjectName.TANK1, spinBoxPressurreTank1.value)
    }

    spinBoxPressurreTank2.onValueChanged:
    {
        sendTankOffsetPressureChanged(E_TankObjectName.TANK2, spinBoxPressurreTank2.value)
    }

    spinBoxPressurreTank3.onValueChanged:
    {
        sendTankOffsetPressureChanged(E_TankObjectName.TANK3, spinBoxPressurreTank3.value)
    }

    spinBoxPressurreTank4.onValueChanged:
    {
        sendTankOffsetPressureChanged(E_TankObjectName.TANK4, spinBoxPressurreTank4.value)
    }

    spinBoxPressurreTank5.onValueChanged:
    {
        sendTankOffsetPressureChanged(E_TankObjectName.TANK5, spinBoxPressurreTank5.value)
    }

    spinBoxPressurreTank6.onValueChanged:
    {
        sendTankOffsetPressureChanged(E_TankObjectName.TANK6, spinBoxPressurreTank6.value)
    }

    Keys.onEscapePressed:
    {
        textFieldTank1Text = memotextFieldTank1
        textFieldTank2Text = memotextFieldTank2
        textFieldTank3Text = memotextFieldTank3
        textFieldTank4Text = memotextFieldTank4
        textFieldTank5Text = memotextFieldTank5
        textFieldTank6Text = memotextFieldTank6
        textFieldTank1.focus=false
        textFieldTank2.focus=false
        textFieldTank3.focus=false
        textFieldTank4.focus=false
        textFieldTank5.focus=false
        textFieldTank6.focus=false
    }

    labelNumberSettingGraphicReccordTime.onNumberInputValueChanged:
    {
        sendGraphReccordTimesChanged(labelNumberSettingGraphicReccordTime.numberInputValue)
    }

    labelNumberVolumePIDCoef.onNumberInputValueChanged:
    {
        sendVolumePIDChanged(labelNumberVolumePIDCoef.numberInputValue)
    }

    labelDeviceATMMinValue.onTextChanged:
    {
        sendVolumeATMChanged()
    }

    labelDeviceATMAvgValue.onTextChanged:
    {
        sendVolumeATMChanged()
    }

    labelDeviceATMMaxValue.onTextChanged:
    {
        sendVolumeATMChanged()
    }

    onCheckBoxCalibrationCheckedChanged:
    {
//        console.log("onCheckBoxCalibrationCheckedChanged : " + checkBoxCalibrationChecked)

        if(checkBoxCalibrationChecked)
        {
            sendGraphReccordTimesChanged(0)
            groupBoxSettingStatisticEnabled = false
        }
        else
        {
            groupBoxSettingStatisticEnabled = true
            sendGraphReccordTimesChanged(labelNumberSettingGraphicReccordTime.numberInputValue)
        }

        sendOnCalibrationMode(checkBoxCalibrationChecked)
    }


    function memoriseOtherTitleText()
    {
        if(!textFieldTank1.activeFocus)
        {
            memotextFieldTank1 = textFieldTank1Text

        }
        if(!textFieldTank2.activeFocus)
        {
            memotextFieldTank2 = textFieldTank2Text

        }
        if(!textFieldTank3.activeFocus)
        {
            memotextFieldTank3 = textFieldTank3Text

        }

        if(!textFieldTank4.activeFocus)
        {
            memotextFieldTank4 = textFieldTank4Text

        }

        if(!textFieldTank5.activeFocus)
        {
            memotextFieldTank5 = textFieldTank5Text

        }

        if(!textFieldTank6.activeFocus)
        {
            memotextFieldTank6 = textFieldTank6Text

        }
    }

    function setTankTitleText(tankObjectID, titleText)
    {
        console.log("setTankTitleText ID: " + tankObjectID + "titleText : " + titleText)

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            textFieldTank1Text = titleText;
            memotextFieldTank1 = titleText;
            break;
        case E_TankObjectName.TANK2:
            textFieldTank2Text = titleText;
            memotextFieldTank2 = titleText;
            break;
        case E_TankObjectName.TANK3:
            textFieldTank3Text = titleText;
            memotextFieldTank3 = titleText;
            break;
        case E_TankObjectName.TANK4:
            textFieldTank4Text = titleText;
            memotextFieldTank4 = titleText;
            break;
        case E_TankObjectName.TANK5:
            textFieldTank5Text = titleText;
            memotextFieldTank5 = titleText;
            break;
        case E_TankObjectName.TANK6:
            textFieldTank6Text = titleText;
            memotextFieldTank6 = titleText;
            break;
        }
    }

    function setTankIsVisible(tankObjectID, isVisible)
    {
        console.log("setTankIsVisible ID: " + tankObjectID + " ,is visible : " + isVisible)

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            checkBoxTank1Checked = isVisible;
            checkBoxTank2.enabled = checkBoxTank1Checked ? true : false
            break;
        case E_TankObjectName.TANK2:
            checkBoxTank2Checked = isVisible;
            checkBoxTank3.enabled = checkBoxTank2Checked ? true : false
            checkBoxTank1.enabled = checkBoxTank2Checked ? false : true
            break;
        case E_TankObjectName.TANK3:
            checkBoxTank3Checked = isVisible;
            checkBoxTank4.enabled = checkBoxTank3Checked ? true : false
            checkBoxTank2.enabled = checkBoxTank3Checked ? false : true
            break;
        case E_TankObjectName.TANK4:
            checkBoxTank4Checked = isVisible;
            checkBoxTank5.enabled = checkBoxTank4Checked ? true : false
            checkBoxTank3.enabled = checkBoxTank4Checked ? false : true
            break;
        case E_TankObjectName.TANK5:
            checkBoxTank5Checked = isVisible;
            checkBoxTank6.enabled = checkBoxTank5Checked ? true : false
            checkBoxTank4.enabled = checkBoxTank5Checked ? false : true
            break;
        case E_TankObjectName.TANK6:
            checkBoxTank6Checked = isVisible;
            checkBoxTank5.enabled = checkBoxTank6Checked ? false : true
            break;
        }
    }

    function setOffsetPressure(tankObjectID, offsetValue)
    {
//        console.log("setOffsetPressure ID: " + tankObjectID + " ,offsetValue : " + offsetValue)

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            spinBoxPressurreTank1.value = offsetValue
            break;
        case E_TankObjectName.TANK2:
            spinBoxPressurreTank2.value = offsetValue
            break;
        case E_TankObjectName.TANK3:
            spinBoxPressurreTank3.value = offsetValue
            break;
        case E_TankObjectName.TANK4:
            spinBoxPressurreTank4.value = offsetValue
            break;
        case E_TankObjectName.TANK5:
            spinBoxPressurreTank5.value = offsetValue
            break;
        case E_TankObjectName.TANK6:
            spinBoxPressurreTank6.value = offsetValue
            break;
        }
    }

    function setVolumePIDCoef(PIDValue)
    {
//        console.log("setOffVolumePIDCoef ID: " + PIDValue)

        labelNumberVolumePIDCoef.numberInputValue = PIDValue
    }

    function setGraphicReccordTime(reccordTime)
    {
//        console.log("setGraphicReccordTime ID: " + reccordTime)

        labelNumberSettingGraphicReccordTime.numberInputValue = reccordTime
    }

    function setATMValue(ATMMin, ATMAvg, ATMMax)
    {
//        console.log("setGraphicReccordTime ID: " + reccordTime)
        labelDeviceATMMinValueText = ATMMin
        labelDeviceATMAvgValueText = ATMAvg
        labelDeviceATMMaxValueText = ATMMax
    }
}
