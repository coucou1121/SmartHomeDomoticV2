import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

import io.qt.GlobalEnumerate 1.0

Rectangle
{
    id: radioButton3Time
    width: 300
    height: 300
    color: "#353131"
    property alias radioButton3TimetankLiquide: radioButton3Time.tankLiquide

    property int tankLiquide: E_TankLiquidInside.WATER

    onRadioButton3TimetankLiquideChanged:
    {
        switch (radioButton3TimetankLiquide)
        {
        case E_TankLiquidInside.WATER :
            radioButtonWater.checked = true
            radioButtonOil.checked = false
            radioButtonOilEco.checked = false
            break;

        case E_TankLiquidInside.OIL :
            radioButtonWater.checked = false
            radioButtonOil.checked = true
            radioButtonOilEco.checked = false
            break;

        case E_TankLiquidInside.ECO_OIL :
            radioButtonWater.checked = false
            radioButtonOil.checked = false
            radioButtonOilEco.checked = true
            break;
        default:
            break;
        }
    }

    ColumnLayout
    {
        id: rowLayoutRadioButton
        spacing: 0
        anchors.fill: parent

        RadioButton
        {
            id: radioButtonWater
            text: "Water"
            spacing: 3
            checked: true

            onCheckedChanged:
            {
                if(checked)
                {
                    radioButton3TimetankLiquide = E_TankLiquidInside.WATER
                }
            }
        }

        RadioButton
        {
            id: radioButtonOil
            text: "Oil"
            spacing: 3
            checked: false

            onCheckedChanged:
            {
                if(checked)
                {
                    radioButton3TimetankLiquide = E_TankLiquidInside.OIL
                }
            }
        }

        RadioButton
        {
            id: radioButtonOilEco
            text: "ECO"
            spacing: 3
            checked: false

            onCheckedChanged:
            {
                if(checked)
                {
                    radioButton3TimetankLiquide = E_TankLiquidInside.ECO_OIL
                }
            }
        }
    }



}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
