import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Item {
    property alias labelNumberSettingDayNumberInputValue: labelNumberSettingDay.numberInputValue
    property alias labelNumberSettingMonthNumberInputValue: labelNumberSettingMonth.numberInputValue
    property alias labelNumberSettingYearsNumberInputValue: labelNumberSettingYears.numberInputValue
    
    property alias radioButtonday: radioButtonday
    property alias radioButtonMonth: radioButtonMonth
    property alias radioButtonYear: radioButtonYear
    
    property date currentDate: new Date()
    property date dateToDisplay: new Date()
    property date lastDayOfdateToDisplay: new Date(currentDate.getFullYear(), currentDate.getMonth()-1, 0);
    
    property bool isTheLastDay: false
    property bool validateDayInProgress : false
    property bool validateMonthInProgress : false
    property bool validateYearInProgress : false

    function checkIsTheLastDayOfMonth(isTheLastDay)
    {
        var lastDayOfMonth = statisticSelectorViewer.lastDayOfdateToDisplay

        if (statisticSelectorViewer.dateToDisplay.getDate()<1)
        {
            statisticSelectorViewer.dateToDisplay.setDate(lastDayOfMonth)
        }
        else
        {
            if (statisticSelectorViewer.dateToDisplay.getDate() === lastDayOfMonth)
            {
                isTheLastDay = false
            }
            else
            {
                isTheLastDay = true
            }
        }
    }
    
    function setDayToDisplay()
    {
        var dateToDisplay = new Date()
        
        statisticSelectorViewer.validateDayInProgress = true
        dateToDisplay.setFullYear(labelNumberSettingYears.numberInputValue)
        dateToDisplay.setMonth(labelNumberSettingMonth.numberInputValue - 1)
        dateToDisplay.setDate(labelNumberSettingDay.numberInputValue)
        
        if(statisticSelectorViewer.isTheLastDay)
        {
            if(dateToDisplay.getDate() == (statisticSelectorViewer.lastDayOfdateToDisplay + 1))
            {
                statisticSelectorViewer.validateMonthInProgress = true
                dateToDisplay.setMonth(dateToDisplay.getMonth() + 1)
                dateToDisplay.setDate(1)
                statisticSelectorViewer.checkIsTheLastDayOfMonth(statisticSelectorViewer.isTheLastDay)
            }
        }
        else
        {
            if(dateToDisplay.getDate() < 1)
            {
                statisticSelectorViewer.validateMonthInProgress = true
                dateToDisplay.setMonth(dateToDisplay.getMonth() - 1)
                statisticSelectorViewer.checkIsTheLastDayOfMonth(statisticSelectorViewer.isTheLastDay)
            }
        }

        if(statisticSelectorViewer.validateMonthInProgress == true)
        {
            statisticSelectorViewer.dateToDisplay.setDate(dateToDisplay.getDate())
            statisticSelectorViewer.dateToDisplay.setMonth(dateToDisplay.getMonth() + 1)
            statisticSelectorViewer.dateToDisplay.setFullYear(dateToDisplay.getFullYear())
            statisticSelectorViewer.setMonthToDisplay()
        }

        statisticSelectorViewer.labelNumberSettingYearsNumberInputValue = dateToDisplay.getFullYear()
        statisticSelectorViewer.labelNumberSettingMonthNumberInputValue = dateToDisplay.getMonth() + 1
        statisticSelectorViewer.labelNumberSettingDayNumberInputValue = dateToDisplay.getDate()
        statisticSelectorViewer.validateYearInProgress = false
        statisticSelectorViewer.validateMonthInProgress = false
        statisticSelectorViewer.validateDayInProgress = false
    }
    
    function setMonthToDisplay()
    {
        var dateToDisplay = new Date(statisticSelectorViewer.dateToDisplay.getFullYear(),
                                     statisticSelectorViewer.dateToDisplay.getMonth() - 1,
                                     statisticSelectorViewer.dateToDisplay.getDate())
        var isTheLastMonth = false

        if(statisticSelectorViewer.validateDayInProgress == false)
        {
            statisticSelectorViewer.validateMonthInProgress = true
            dateToDisplay.setFullYear(labelNumberSettingYears.numberInputValue)
            dateToDisplay.setMonth(labelNumberSettingMonth.numberInputValue - 1)
            dateToDisplay.setDate(labelNumberSettingDay.numberInputValue)
        }

        if(isTheLastMonth)
        {
            if(dateToDisplay.getMonth() > 12)
            {
                statisticSelectorViewer.validateYearInProgress = true
                dateToDisplay.setFullYear(dateToDisplay.getFullYear() + 1)
                dateToDisplay.setMonth(1)
                isTheLastMonth = false
            }
        }
        else
        {
            if(dateToDisplay.getMonth() < 1)
            {
                statisticSelectorViewer.validateYearInProgress = true
                dateToDisplay.setFullYear(dateToDisplay.getFullYear() - 1)
                dateToDisplay.setMonth(12)
                isTheLastMonth = true
            }
        }

        if(statisticSelectorViewer.validateDayInProgress == false)
        {
            statisticSelectorViewer.labelNumberSettingYearsNumberInputValue = dateToDisplay.getFullYear()
            statisticSelectorViewer.labelNumberSettingMonthNumberInputValue = dateToDisplay.getMonth() + 1
            statisticSelectorViewer.labelNumberSettingDayNumberInputValue = dateToDisplay.getDate()
            statisticSelectorViewer.validateYearInProgress = false
            statisticSelectorViewer.validateMonthInProgress = false
        }
    }
    
    Component.onCompleted:
    {
        labelNumberSettingYears.numberInputValue = currentDate.getFullYear()
        labelNumberSettingYears.numberInputStepSize = 1
        labelNumberSettingYears.numberInputFrom = 1900
        labelNumberSettingYears.numberInputTo = 2100
        
        labelNumberSettingMonth.numberInputValue = currentDate.getMonth() + 2
        labelNumberSettingMonth.numberInputStepSize = 1
        labelNumberSettingMonth.numberInputFrom = 0
        labelNumberSettingMonth.numberInputTo = 13
        
        labelNumberSettingDay.numberInputValue = currentDate.getDate()
        labelNumberSettingDay.numberInputStepSize = 1
        labelNumberSettingDay.numberInputFrom = 0
        labelNumberSettingDay.numberInputTo = 32
    }
    
    width: 200
    height: 190
    id : statisticSelectorViewer
    
    GridLayout {
        x: 0
        y: 0
        columnSpacing: 4
        rowSpacing: 5
        rows: 3
        columns: 2
        
        RadioButton
        {
            id: radioButtonYear
            checked: false
            
            onCheckedChanged:
            {
                if(checked)
                {
                    labelNumberSettingYears.enabled = true
                    labelNumberSettingMonth.enabled = false
                    labelNumberSettingDay.enabled = false
                }
            }
        }
        
        LabelNumberSetting {
            id: labelNumberSettingYears
            enabled: true
            Layout.maximumHeight: 60
            Layout.minimumHeight: 60
            Layout.preferredHeight: 60
            Layout.maximumWidth: 150
            Layout.preferredWidth: 150
            Layout.minimumWidth: 150
            labelNumberText: "Year"
            onNumberInputValueChanged:
            {
            }
        }
        
        
        RadioButton
        {
            id: radioButtonMonth
            
            onCheckedChanged:
            {
                if(checked)
                {
                    labelNumberSettingYears.enabled = true
                    labelNumberSettingMonth.enabled = true
                    labelNumberSettingDay.enabled = false
                }
            }
        }
        
        LabelNumberSetting {
            id: labelNumberSettingMonth
            enabled: true
            Layout.maximumHeight: 60
            Layout.minimumHeight: 60
            Layout.preferredHeight: 60
            Layout.maximumWidth: 150
            Layout.minimumWidth: 150
            Layout.preferredWidth: 150
            labelNumberText: "Month"
            onNumberInputValueChanged:
            {
                if(!statisticSelectorViewer.validateMonthInProgress)
                {
                    statisticSelectorViewer.setMonthToDisplay()
                }
            }
            
        }
        
        RadioButton
        {
            id: radioButtonday
            checked: true
            
            onCheckedChanged:
            {
                if(checked)
                {
                    labelNumberSettingYears.enabled = true
                    labelNumberSettingMonth.enabled = true
                    labelNumberSettingDay.enabled = true             }
            }
        }
        
        LabelNumberSetting {
            id: labelNumberSettingDay
            enabled: true
            Layout.fillWidth: false
            Layout.maximumHeight: 60
            Layout.minimumHeight: 60
            Layout.preferredHeight: 60
            Layout.maximumWidth: 150
            Layout.minimumWidth: 150
            Layout.preferredWidth: 150
            labelNumberText: "Day"
            onNumberInputValueChanged:
            {
                if(!statisticSelectorViewer.validateDayInProgress)
                {
                    statisticSelectorViewer.setDayToDisplay()
                }
            }
        }
    }
    
    
    
}
