import QtQuick 2.4

StatisticViewForm
{

    width: 900
    height: 800


    Timer
    {
        signal sendRefreshDataTemperaturePlot()
        signal sendRefreshDataHumidity()
        signal sendRefreshDataPressure()

        property alias refreshTimer: timerTemperature.interval

        id: timerTemperature
        objectName: "timerTemperature"

        //       interval: 1 / 60 * 1000 // 60 Hz
        interval: 1000 // 1 Hz
        running: true
        repeat: true
        triggeredOnStart: false
        onTriggered:
        {
//            customPlot.plot.addYValue(1,1)
//            customPlot.plot.addYValue(1,2)
//            customPlotTemp.plot.addYValue(6,5)
//            sendRefreshDataTemperaturePlot()
//            sendRefreshDataHumidity()
//            sendRefreshDataPressure()
            customPlotRoomData.replot()
//            customPlotHumidity.replot()
//            customPlotPressure.replot()
//            qlLinePlot.plot.addPoint(0,3,3)
            //               qlLinePlot.setGraphName(0,"coucou",true)
            //                qlLinePlot.rescale()
 //           qlLinePlot.plot.replot()
 //           console.log("refreshTimer:" + running  + interval)
        }
    }
//    StatisticViewForm
//    {
//        customPlot
//        {

//        }
//    }
}
