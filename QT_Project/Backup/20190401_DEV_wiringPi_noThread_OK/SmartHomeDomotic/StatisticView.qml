import QtQuick 2.4
import io.qt.GlobalEnumerate 1.0

StatisticViewForm
{
    //    property bool isReadyToBeInitialise: false
    property bool isInitialised: false
    property int nbOfTraceInGraph : 1
    property bool upDateStatisticData: false

    property date currentDate: new Date()
    //    property date loadDate: new Date(currentDate.getFullYear(), currentDate.getMonth(), 0);

    property int loadYear: statisticSelectorViewer.labelNumberSettingYearsNumberInputValue
    property int loadMonth: statisticSelectorViewer.labelNumberSettingMonthNumberInputValue
    property int loadDay: statisticSelectorViewer.labelNumberSettingDayNumberInputValue

    signal sendReplotWithSavedData(int year,int month, int day)

    function setTankTraceTitleText(tankObjectID, titleText)
    {
        qcustomPlotTanksData.setupTraceName(tankObjectID,titleText)
    }

    function setupTraceIsSelected(tankObjectID, isVisible)
    {
        qcustomPlotTanksData.setupTraceIsSelected(tankObjectID,isVisible)
    }

    function setTankTraceNomberInGraph(nbTrace)
    {
        nbOfTraceInGraph = nbTrace
    }

    function setStatisticValues(tempMin, tempMax, humMin, humMax, preeMin, pressMax, conso)
    {
        //        console.log("setStatisticValues tempMin : " + nbOfTraceInGraph)
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
        qcustomPlotTanksData.setGraphicRange(graphicRange)
        qcustomPlotRoomData.setGraphicRange(graphicRange)
    }

    function setOnClaibration(onCalibration)
    {
        if(onCalibration)
        {
            qcustomPlotTanksData.setGraphicRange(100)
            qcustomPlotRoomData.setGraphicRange(100)
            //timerPlotRefreching.interval = 700
        }
        else
        {
            //timerPlotRefreching.interval = 1000
        }
    }


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
    objectName: "statistiqueValueViewers"

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
        interval: 1000 // 1 Hz
        running: true
        repeat: true
        triggeredOnStart: false
        onTriggered:
        {

            if(!isInitialised)
            {
                //                if(isReadyToBeInitialise && (nbOfTraceInGraph>0))
                //                {
                //                    //qcustomPlotTanksData.setupStyleAnalogTrace(nbOfTraceInGraph)
                //                    //                    qcustomPlotTanksData.setupStyleStatisticTrace(6)
                //                }

                if(qcustomPlotTanksData.isReadyToReceiveData
                        &&     qcustomPlotRoomData.isReadyToReceiveData
                        &&     qcustomPlotStatisticsTemperature.isReadyToReceiveData
                        &&     qcustomPlotStatisticsHumidity.isReadyToReceiveData
                        &&     qcustomPlotStatisticsPressure.isReadyToReceiveData
                        &&     qcustomPlotStatisticsConso.isReadyToReceiveData)
                {
                    //                    qcustomPlotTanksData.initTraceName()
                    isInitialised = true
                }
            }


            if(upDateStatisticData)
            {
                console.log("Ask replot saved data")
                upDateStatisticData = false

                //                if(!statisticSelectorViewer.radioButtonMonth.checked)
                //                {
                //                    loadMonth = 0;
                //                }
                //                if(!statisticSelectorViewer.radioButtonday.checked)
                //                {
                //                    loadDay = 0;
                //                }

                qcustomPlotStatisticsTemperature.replotWithSavedData(loadYear,
                                                                     loadMonth,
                                                                     loadDay)
                qcustomPlotStatisticsHumidity.replotWithSavedData(loadYear,
                                                                  loadMonth,
                                                                  loadDay)
                qcustomPlotStatisticsPressure.replotWithSavedData(loadYear,
                                                                  loadMonth,
                                                                  loadDay)
                qcustomPlotStatisticsConso.replotWithSavedData(loadYear,
                                                               loadMonth,
                                                               loadDay)

                sendReplotWithSavedData(loadYear,
                                        loadMonth,
                                        loadDay)
                //                customPlotStatistics.replotWithSavedData(2018, 11, 26)
                //                sendReplotWithSavedData(2018, 11, 26)


            }

            qcustomPlotRoomData.replot(false)
            qcustomPlotTanksData.replot(false)

            qcustomPlotStatisticsTemperature.replot(true)
            qcustomPlotStatisticsHumidity.replot(true)
            qcustomPlotStatisticsPressure.replot(true)
            qcustomPlotStatisticsConso.replot(true)
        }
    }
}
