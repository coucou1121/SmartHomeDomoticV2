import QtQuick 2.0
import io.qt.CustomPlotItem 1.0
import io.qt.GlobalEnumerate 1.0

Item
{
    //property var  plot: children[0]

    width: 980
    height: 200
    property alias customPlotItem: customPlotItem
    property bool isReadyToReceiveData: false
    property string trace1Name: ""
    property string trace2Name: ""
    property string trace3Name: ""
    property string trace4Name: ""
    property string trace5Name: ""
    property string trace6Name: ""

    function addYValue(valueGraph1, valueGraph2, valueGraph3,
                       valueGraph4)
    {
        //        console.log(objectName + " addYValue")
        if(isReadyToReceiveData)
        {
            customPlotItem.addYValue(valueGraph1, valueGraph2, valueGraph3, valueGraph4)
        }
    }

    function replot(resize)
    {
        //        console.log(objectName + " replot")
        customPlotItem.replot(resize)
    }

    function replotWithSavedData(year, month, day)
       {
           //        console.log(objectName + " replot")
           customPlotItem.replotWithSavedData(year, month, day)
       }

    function setupStyleWeatherStation()
    {
        //        console.log(objectName + " setupStyleWeatherStation")
        customPlotItem.setupStyle(E_PlotStyle.PLOT_STYLE_WEATHER_STATION, 3)
        isReadyToReceiveData = true
    }

    function setupStyleAnalogTrace(nbTrace)
    {
        //        console.log(objectName + " setupStyleWeatherStation")
        customPlotItem.setupStyle(E_PlotStyle.PLOT_STYLE_ANANLOG_TRACE, nbTrace)
        isReadyToReceiveData = true
    }

    function setupStyleStatisticTrace(nbTrace)
    {
        //        console.log(objectName + " setupStyleWeatherStation")
        customPlotItem.setupStyle(E_PlotStyle.PLOT_STYLE_STATISTIC_TRACE, nbTrace)
        isReadyToReceiveData = true
    }

    function setupStyleTemperatureTrace(nbTrace)
    {
        //        console.log(objectName + " setupStyleWeatherStation")
        customPlotItem.setupStyle(E_PlotStyle.PLOT_STYLE_TEMPERATURE_TRACE, nbTrace)
        isReadyToReceiveData = true
    }

    function setupStyleHumidityTrace(nbTrace)
    {
        //        console.log(objectName + " setupStyleWeatherStation")
        customPlotItem.setupStyle(E_PlotStyle.PLOT_STYLE_HUMIDITY_TRACE, nbTrace)
        isReadyToReceiveData = true
    }

    function setupStylePressureTrace(nbTrace)
    {
        //        console.log(objectName + " setupStyleWeatherStation")
        customPlotItem.setupStyle(E_PlotStyle.PLOT_STYLE_PRESSURE_TRACE, nbTrace)
        isReadyToReceiveData = true
    }

    function setupStyleConsoTrace(nbTrace)
    {
        //        console.log(objectName + " setupStyleWeatherStation")
        customPlotItem.setupStyle(E_PlotStyle.PLOT_STYLE_CONSO_TRACE, nbTrace)
        isReadyToReceiveData = true
    }

    function initTraceName()
    {
        setupTraceName(1, trace1Name)
        setupTraceName(2, trace2Name)
        setupTraceName(3, trace3Name)
        setupTraceName(4, trace4Name)
        setupTraceName(5, trace5Name)
        setupTraceName(6, trace6Name)
    }


    function setupTraceName(tankObjectID, titleText)
    {
        //        console.log(objectName + "setupTraceName")
        customPlotItem.setupGraphLabel(tankObjectID, titleText)
        switch (tankObjectID)
        {
        case 1:
            trace1Name = titleText
            break;
        case 2:
            trace2Name = titleText
            break;
        case 3:
            trace3Name = titleText
            break;
        case 4:
            trace4Name = titleText
            break;
        case 5:
            trace5Name = titleText
            break;
        case 6:
            trace6Name = titleText
            break;
        default:
            break;
        }
    }

    function setupTraceIsSelected(tankObjectID, isVisible)
    {
        if(isReadyToReceiveData)
        {
            customPlotItem.setupTraceIsSelected(tankObjectID, isVisible)
            if(isVisible)
            {
                initTraceName()
            }
        }
    }

    function clearGraphAndValues()
    {

    }

    function setGraphicRange(refreshTime)
    {
        customPlotItem.setRange(refreshTime)
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
