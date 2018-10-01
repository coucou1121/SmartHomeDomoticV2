import QtQuick 2.0
import QtCharts 2.1

import io.qt.DataSource 1.0
import io.qt.CustomPlotItem 1.0
import io.qt.QlLinePlotItem 1.0


Item
{
    width: 988
    height: 800

//    property alias refreshTimer : timer.interval

    // append single point to graphs
 //   function addYValue(value)
//    {
//        customPlot.plot.addYValue(value, 5);
//        dataXY.push({'x':x, 'y':y
//                        ,
//			'yMin':y.reduceRight(function(prev,cur){ return isNaN(cur) ? prev : (cur < prev) ? cur : prev; }, Infinity),
//			'yMax':y.reduceRight(function(prev,cur){ return isNaN(cur) ? prev : (cur > prev) ? cur : prev; }, -Infinity),
//        });
        //console.log(dataXY[0])
 //       console.log("dataXY.length:", dataXY.length)
//        xPrev = x; // remember previous X,Y
//        yPrev = y;
//    }

//    Timer
//    {
//        id: timer
//        //       interval: 1 / 60 * 1000 // 60 Hz
//        interval: 500 // 2 Hz
//        running: true
//        repeat: true
//        triggeredOnStart: false
//        onTriggered:
//        {
////            customPlot.plot.addYValue(1,1)
////            customPlot.plot.addYValue(1,2)
//            customPlot.plot.addYValue(6,5)
//            customPlot.plot.replot()
////            qlLinePlot.plot.addPoint(0,3,3)
//            //               qlLinePlot.setGraphName(0,"coucou",true)
//            //                qlLinePlot.rescale()
// //           qlLinePlot.plot.replot()
// //           console.log("refreshTimer:" + running  + interval)
//        }
//    }

//    QlLinePlot
//    {
//        id: qlLinePlot
//        x: 628
//        y: 406
//        width: 300
//        height: 300
//    }



//    CustomPlot
//    {
//        id: customPlot
//        x: 29
//        y: 32
//        width: 764
//        height: 660
//    }



}
