import QtQuick 2.0
import io.qt.CustomPlotItem 1.0

Item
{
    //property var  plot: children[0]

    width: 980
    height: 200

    function addYValue(valueGraph1, valueGraph2, valueGraph3, valueLimitLine)
    {
        console.log(objectName + " addYValue")
        customPlotItem.addYValue(valueGraph1, valueGraph2, valueGraph3, valueLimitLine)
    }

    function replot()
    {
        console.log(objectName + " replot")
        customPlotItem.replot()
    }

    CustomPlotItem
    {
        id: customPlotItem;
        anchors.fill:parent;
    }

    //    Component.onCompleted: {
    //        // initialize plot
    ////        plot.initPlot();
    ////		setDateFormat(xDate,xDateFormat);
    ////		setAutoRange(autoRange);
    ////		setLabelX(labelX);
    ////		setLabelY(labelY);
    ////		showLegend(legend);
    ////		plot.setDrag(dragX,dragY);
    ////		plot.setZoom(zoomX,zoomY);
    ////        plot.addGraph("test", true, "red", 100, "dot")
    ////        plot.addPoints(1,1)
    ////        plot.addPoints(2,2)
    ////        plot.addPoints(3,3)

    ////        plot.addGraph("test", true, "red", 1, "dot")
    ////        plot.addPoint(0,1,1)
    ////        plot.addPoint(0,2,2)
    ////        replot()
    //    }
}

/*##^## Designer {
    D{i:1;anchors_x:0;anchors_y:0}
}
 ##^##*/
