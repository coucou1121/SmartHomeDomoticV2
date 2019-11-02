import QtQuick 2.4
import io.qt.GlobalEnumerate 1.0

StatisticViewForm
{
    property bool isReadyToBeInitialise: false
    property bool isInitialised: false
    property int nbOfTankTraceInGraph : 0
    property int nbOfPressureTraceInGraph : 0
    property bool upDateStatisticData: false

    property date currentDate: new Date()
    //    property date loadDate: new Date(currentDate.getFullYear(), currentDate.getMonth(), 0);

    property int loadYear: statisticSelectorViewer.labelNumberSettingYearsNumberInputValue
    property int loadMonth: statisticSelectorViewer.labelNumberSettingMonthNumberInputValue
    property int loadDay: statisticSelectorViewer.labelNumberSettingDayNumberInputValue

    function setTankTraceTitleText(tankObjectID, titleText)
    {
        customPlotTanksData.setupTraceName(tankObjectID,titleText)
    }

    function setupTraceIsSelected(tankObjectID, isVisible)
    {
        customPlotTanksData.setupTraceIsSelected(tankObjectID,isVisible)
    }

    function setTankTraceNomberInGraph(nbTrace)
    {
        nbOfTankTraceInGraph = nbTrace
    }


    function setPressureTraceTitleText(titleText)
    {
        customPlotPressureData.setupPressureTraceName(titleText)
    }

    function setPressureTraceNomberInGraph(nbTrace)
    {
        nbOfPressureTraceInGraph = nbTrace
    }

    function setStatisticValues(tempMin, tempMax, humMin, humMax, preeMin, pressMax, conso)
    {
        console.log("setStatisticValues tempMin : " + nbOfTankTraceInGraph)
        labelDeviceTemperatureMinText = tempMin
        labelDeviceTemperatureMaxText = tempMax
        labelDeviceHumidityMinText = humMin
        labelDeviceHumidityMaxText = humMax
        labelDeviceAtmoPressurMinText = preeMin
        labelDeviceAtmoPressurMaxText = pressMax
        labelDeviceConsoText = conso
    }

    function setGraphicRange(graphicRange)
    {
//        customPlotPressureData.setGraphicRange(graphicRange)
        customPlotTanksData.setGraphicRange(graphicRange)
        customPlotRoomData.setGraphicRange(graphicRange)
    }

    function setOnCalibration(onCalibration)
    {
        if(onCalibration)
        {
            customPlotTanksData.setGraphicRange(100)
//            customPlotRoomData.setGraphicRange(100)
            //timerPlotRefreching.interval = 700
        }
        else
        {
            //timerPlotRefreching.interval = 1000
        }
    }

    signal sendReplotWithSavedData(int year,int month, int day)

    statisticSelectorViewer.onLabelNumberSettingYearsNumberInputValueChanged:
    {
        //       loadDate.setFullYear(statisticSelectorViewer.labelNumberSettingYearsNumberInputValue)
        upDateStatisticData = true
    }

    statisticSelectorViewer.onLabelNumberSettingMonthNumberInputValueChanged:
    {
        //       loadDate.setMonth(statisticSelectorViewer.labelNumberSettingMonthNumberInputValue)
        upDateStatisticData = true
    }

    statisticSelectorViewer.onLabelNumberSettingDayNumberInputValueChanged:
    {
        //       loadDate.setDate(statisticSelectorViewer.labelNumberSettingDayNumberInputValue)
        upDateStatisticData = true
    }

    width: 900
    height: 800
    id: statistiqueValueViewer
    objectName: "statistiqueValueViewer"
    Component.onCompleted:
    {
        console.log("Completed Running!")
//        customPlotPressureData.setupStyleAnalogTracePressure(1)
        customPlotRoomData.setupStyleWeatherStation()
        customPlotStatistics.setupStyleTemperatureTrace(2)
        customPlotStatisticHumidity.setupStyleHumidityTrace(2)
        customPlotStatisticsPressure.setupStylePressureTrace(2)
        customPlotStatisticsConso.setupStyleConsoTrace(2)
        isReadyToBeInitialise = true
    }

    mouseAreaStatisticView.onDoubleClicked:
    {
        if(gridLayoutStatistic.visible)
        {
            //            customPlotStatistics.visible = false
            gridLayoutStatistic.visible = false
            //            statisticSelectorViewer.visible = false
            //            columnLayoutPlotStatistic.visible = false
        }
        else
        {
            //            customPlotStatistics.visible = true
            gridLayoutStatistic.visible = true
            //            statisticSelectorViewer.visible = true
            //            columnLayoutPlotStatistic.visible = true
        }
    }


    Timer
    {
        property alias refreshTimer: timerPlotRefreching.interval

        id: timerPlotRefreching
        objectName: "timerPlotRefreching"

        //       interval: 1 / 60 * 1000 // 60 Hz
        interval: 500 // 1 Hz
        running: true
        repeat: true
        triggeredOnStart: false
        onTriggered:
        {

            if(!isInitialised)
            {
                if(isReadyToBeInitialise && (nbOfTankTraceInGraph>0) && (nbOfPressureTraceInGraph>0))
                {
                    customPlotTanksData.setupStyleTankTrace(nbOfTankTraceInGraph)
                   // customPlotPressureData.setupStyleAnalogTrace(nbOfPressureTraceInGraph)
                    //                    customPlotTanksData.setupStyleStatisticTrace(6)
                }

                if(customPlotTanksData.isReadyToReceiveData)
                {
                    customPlotTanksData.initTraceName()
                    isInitialised = true
                }

//                if(customPlotPressureData.isReadyToReceiveData)
//                {
//                    customPlotPressureData.initTraceName()
//                    isInitialised = true
//                }
            }

//            customPlotPressureData.replot(false)




            customPlotRoomData.replot(false)
            customPlotTanksData.replot(false)

//            if(upDateStatisticData)
//            {
//                console.log("Ask replot saved data")
//                upDateStatisticData = false

//                //                if(!statisticSelectorViewer.radioButtonMonth.checked)
//                //                {
//                //                    loadMonth = 0;
//                //                }
//                //                if(!statisticSelectorViewer.radioButtonday.checked)
//                //                {
//                //                    loadDay = 0;
//                //                }

//                customPlotStatistics.replotWithSavedData(loadYear,
//                                                         loadMonth,
//                                                         loadDay)
//                customPlotStatisticHumidity.replotWithSavedData(loadYear,
//                                                                loadMonth,
//                                                                loadDay)
//                customPlotStatisticsPressure.replotWithSavedData(loadYear,
//                                                                 loadMonth,
//                                                                 loadDay)
//                customPlotStatisticsConso.replotWithSavedData(loadYear,
//                                                              loadMonth,
//                                                              loadDay)

//                sendReplotWithSavedData(loadYear,
//                                        loadMonth,
//                                        loadDay)
//                //                customPlotStatistics.replotWithSavedData(2018, 11, 26)
//                //                sendReplotWithSavedData(2018, 11, 26)


//            }

//            customPlotStatistics.replot(true)
//            customPlotStatisticHumidity.replot(true)
//            customPlotStatisticsPressure.replot(true)
//            customPlotStatisticsConso.replot(true)
        }
    }
}
