#include "globalstyle.h"

GlobalStyle::GlobalStyle()
{
}

void GlobalStyle::setBackGroundColor(QCustomPlot *customPlot)
{
    customPlot->setBackground(_backGroundColor);
}

void GlobalStyle::setStylePlot(QCustomPlot *customPlot, bool tickAsTime)
{

    if(tickAsTime)
    {
        QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
        dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
        dateTimeTicker->setTickCount(8);
        customPlot->axisRect()->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
        //        graph->keyAxis()->setTicker(dateTimeTicker);

        //     customPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(QDate(2013, 11, 16)), QCPAxisTickerDateTime::dateTimeToKey(QDate(2015, 5, 2)));
        //     dateTimeTicker->setDateTimeFormat("d. MMM\nyyyy");
        dateTimeTicker->setDateTimeFormat("HH:mm\ndd MMM yyyy");
    }
    else
    {
        QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
        customPlot->axisRect()->axis(QCPAxis::atBottom)->setTicker(fixedTicker);

        //        customPlot->graph(0)->keyAxis()->setTicker(fixedTicker);
    }

    //Set the axis color and line type
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setBasePen(QPen(_axisColorPlot, 1));
    customPlot->axisRect()->axis(QCPAxis::atBottom)->setBasePen(QPen(_axisColorPlot, 1));
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setTickPen(QPen(_axisTickPlot, 1));
    customPlot->axisRect()->axis(QCPAxis::atBottom)->setTickPen(QPen(_axisTickPlot, 1));
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setSubTickPen(QPen(_axisTickPlot, 1));
    customPlot->axisRect()->axis(QCPAxis::atBottom)->setSubTickPen(QPen(_axisTickPlot, 1));
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setTickLabelColor(_axisColorPlot);
    customPlot->axisRect()->axis(QCPAxis::atBottom)->setTickLabelColor(_axisColorPlot);
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setTicks(true);
    customPlot->axisRect()->axis(QCPAxis::atBottom)->setTicks(true);
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setSubTicks(true);
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setTickLabels(true);
    customPlot->axisRect()->axis(QCPAxis::atBottom)->setTickLabels(true);

    //customPlot->xAxis->setTickLabelPadding(10);
    //customPlot->xAxis->setTickLabelRotation(-60);
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setTickLength(0, 4);
    customPlot->axisRect()->axis(QCPAxis::atLeft)->setTickLabelFont(QFont(QFont().family(), 10));
    customPlot->axisRect()->axis(QCPAxis::atBottom)->setTickLabelFont(QFont(QFont().family(), 10));

    //Set the grid plot color and line type
    customPlot->axisRect()->axis(QCPAxis::atBottom)->grid()->setVisible(false);

    customPlot->axisRect()->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    customPlot->axisRect()->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    customPlot->axisRect()->axis(QCPAxis::atLeft)->grid()->setSubGridVisible(false);
    customPlot->axisRect()->axis(QCPAxis::atBottom)->grid()->setSubGridVisible(false);
    customPlot->axisRect()->axis(QCPAxis::atLeft)->grid()->setSubGridPen(QPen(_gridColorPlot, 1, Qt::DotLine));
    customPlot->axisRect()->axis(QCPAxis::atBottom)->grid()->setSubGridPen(QPen(_gridColorPlot, 1, Qt::DotLine));

    //Set the axis grid color and line type
    customPlot->axisRect()->axis(QCPAxis::atLeft)->grid()->setPen(QPen(_gridColorPlot, 1, Qt::DotLine));
    customPlot->axisRect()->axis(QCPAxis::atBottom)->grid()->setPen(QPen(_gridColorPlot, 1, Qt::DotLine));

    //y Axis color and line type
    customPlot->axisRect()->axis(QCPAxis::atLeft)->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->axisRect()->axis(QCPAxis::atBottom)->grid()->setZeroLinePen(Qt::NoPen);

    //rescale the axis
    //   customPlot->rescaleAxes();

    QCPLegend *legend = new QCPLegend();
    QCPLayoutInset *legandLayout = customPlot->axisRect()->insetLayout();
    legandLayout->addElement((QCPLayoutElement*) legend, Qt::AlignBottom|Qt::AlignRight);

    // prepare legend and some graphs:
//     customPlot->legend->setVisible(true);
//     customPlot->graph(0)->setName("Torque");
//     customPlot->graph(1)->setName("Power");
//     customPlot->graph(2)->setName("Efficiency");
//     // create and prepare a text layout element:
//     QCPTextElement *legendTitle = new QCPTextElement(customPlot);
////     legendTitle->setLayer(customPlot->legend->layer()); // place text element on same layer as legend, or it ends up below legend
//     legendTitle->setText("Engine Status");
//     legendTitle->setFont(QFont("sans", 9, QFont::Bold));
     // then we add it to the QCPLegend (which is a subclass of QCPLayoutGrid):
//     if (customPlot->legend->hasElement(0, 0)) // if top cell isn't empty, insert an empty row at top
//       customPlot->legend->insertRow(0);
//     customPlot->legend->addElement(0, 0, legendTitle); // place the text element into the empty cell
    // show legend with slightly transparent background brush:
    //   customPlot->legend->setVisible(true);
    //   customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    //   customPlot->legend->setBrush(QColor(255, 255, 255, 150));

}

//void GlobalStyle::setBackGroundColor(QLabel *label)
//{
//    label->setStyleSheet("background-color:" + _backGroundColor.name()+ "; font: 12pt;");
//}

//void GlobalStyle::setBackGroundColor(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
//                              "stop: 1" + _backGroundColorPushButtonLight.name() +
//                              ", stop: 0 #ffffff); font: 12pt;");
//}

//void GlobalStyle::setBackGroundColorAISelected(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
//                              "stop: 1" + _traceColorAnalogPlot.name() +
//                              ", stop: 0 #ffffff); font: 12pt;");
//}

//void GlobalStyle::setBackGroundColorDISelected(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
//                              "stop: 1" + _traceColorDigitalPlot.name() +
//                              ", stop: 0 #ffffff); font: 12pt;");
//}


void GlobalStyle::setStylePlotWithTwoYAxis(QCustomPlot *customPlot, bool tickAsTime, QCPAxisRect *wideAxisRect)
{
    //set background color
    GlobalStyle::setBackGroundColor(customPlot);

    //set margin
    //    customPlot->axisRect()->setAutoMargins(QCP::msNone);

    //    QCPAxisRect *wideAxisRect = new QCPAxisRect(customPlot);

    if(tickAsTime)
    {
        QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
        dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
        dateTimeTicker->setTickCount(8);
        customPlot->xAxis->setTicker(dateTimeTicker);

        //     customPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(QDate(2013, 11, 16)), QCPAxisTickerDateTime::dateTimeToKey(QDate(2015, 5, 2)));
        //     dateTimeTicker->setDateTimeFormat("d. MMM\nyyyy");
        dateTimeTicker->setDateTimeFormat("HH:mm\ndd MMM yyyy");
    }
    else
    {
        QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
        customPlot->xAxis->setTicker(fixedTicker);
    }

    //Set the axis color and line type
    customPlot->xAxis->setBasePen(QPen(_axisColorPlot, 1));
    customPlot->yAxis->setBasePen(QPen(_axisColorPlot, 1));
    customPlot->xAxis->setTickPen(QPen(_axisTickPlot, 1));
    customPlot->yAxis->setTickPen(QPen(_axisTickPlot, 1));
    customPlot->xAxis->setSubTickPen(QPen(_axisTickPlot, 1));
    customPlot->yAxis->setSubTickPen(QPen(_axisTickPlot, 1));
    customPlot->xAxis->setTickLabelColor(_axisColorPlot);
    customPlot->yAxis->setTickLabelColor(_axisColorPlot);
    customPlot->xAxis->setTicks(true);
    customPlot->yAxis->setTicks(true);
    customPlot->xAxis->setSubTicks(true);
    customPlot->xAxis->setTickLabels(true);
    customPlot->yAxis->setTickLabels(true);

    //customPlot->xAxis->setTickLabelPadding(10);
    //customPlot->xAxis->setTickLabelRotation(-60);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 10));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 10));

    //Set the grid plot color and line type
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->yAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setSubGridVisible(false);
    customPlot->yAxis->grid()->setSubGridVisible(false);
    customPlot->xAxis->grid()->setSubGridPen(QPen(_gridColorPlot, 1, Qt::DotLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(_gridColorPlot, 1, Qt::DotLine));

    //Set the axis grid color and line type
    customPlot->xAxis->grid()->setPen(QPen(_gridColorPlot, 1, Qt::DotLine));
    customPlot->yAxis->grid()->setPen(QPen(_gridColorPlot, 1, Qt::DotLine));

    //y Axis color and line type
    customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);

    //set yaxis2 visible
    //customPlot->yAxis2->setVisible(true);

    //rescale the axis
    customPlot->rescaleAxes();

    // show legend with slightly transparent background brush:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));
    // configure axis rect:
    //    customPlot->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    //    wideAxisRect->setupFullAxesBox(true);
    //    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    //    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    //    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#605000")); // add an extra axis on the left and color its numbers
    //    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    //    customPlot->plotLayout()->addElement(0, 0, wideAxisRect); // insert axis rect in first row
    //    customPlot->plotLayout()->addElement(1, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //customPlot->plotLayout()->setRowStretchFactor(1, 2);
    // prepare axis rects that will be placed in the sublayout:
    //    QCPAxisRect *subRectLeft = new QCPAxisRect(customPlot, false); // false means to not setup default axes
    //    QCPAxisRect *subRectRight = new QCPAxisRect(customPlot, false);
    //    subLayout->addElement(0, 0, subRectLeft);
    //    subLayout->addElement(0, 1, subRectRight);
    //    subRectRight->setMaximumSize(150, 150); // make bottom right axis rect size fixed 150x150
    //    subRectRight->setMinimumSize(150, 150); // make bottom right axis rect size fixed 150x150
    //    // setup axes in sub layout axis rects:
    //    subRectLeft->addAxes(QCPAxis::atBottom | QCPAxis::atLeft);
    //    subRectRight->addAxes(QCPAxis::atBottom | QCPAxis::atRight);
    //    subRectLeft->axis(QCPAxis::atLeft)->ticker()->setTickCount(2);
    //    subRectRight->axis(QCPAxis::atRight)->ticker()->setTickCount(2);
    //    subRectRight->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    //    subRectLeft->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    //    // synchronize the left and right margins of the top and bottom axis rects:
    //    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
    //    subRectLeft->setMarginGroup(QCP::msLeft, marginGroup);
    //    subRectRight->setMarginGroup(QCP::msRight, marginGroup);
    //    wideAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    // move newly created axes on "axes" layer and grids on "grid" layer:
    //    foreach (QCPAxisRect *rect, customPlot->axisRects())
    //    {
    //      foreach (QCPAxis *axis, rect->axes())
    //      {
    //        axis->setLayer("axes");
    //        axis->grid()->setLayer("grid");
    //      }
    //    }

    //    // prepare data:
    //    QVector<QCPGraphData> dataCos(21), dataGauss(50), dataRandom(100);
    //    QVector<double> x3, y3;
    //    qsrand(3);
    //    for (int i=0; i<dataCos.size(); ++i)
    //    {
    //      dataCos[i].key = i/(double)(dataCos.size()-1)*10-5.0;
    //      dataCos[i].value = qCos(dataCos[i].key);
    //    }
    //    for (int i=0; i<dataGauss.size(); ++i)
    //    {
    //      dataGauss[i].key = i/(double)dataGauss.size()*10-5.0;
    //      dataGauss[i].value = qExp(-dataGauss[i].key*dataGauss[i].key*0.2)*1000;
    //    }
    //    for (int i=0; i<dataRandom.size(); ++i)
    //    {
    //      dataRandom[i].key = i/(double)dataRandom.size()*10;
    //      dataRandom[i].value = qrand()/(double)RAND_MAX-0.5+dataRandom[qMax(0, i-1)].value;
    //    }
    //    x3 << 1 << 2 << 3 << 4;
    //    y3 << 2 << 2.5 << 4 << 1.5;

    //    // create and configure plottables:
    //    QCPGraph *mainGraphCos = customPlot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
    //    mainGraphCos->data()->set(dataCos);
    //    mainGraphCos->valueAxis()->setRange(-1, 1);
    //    mainGraphCos->rescaleKeyAxis();
    //    mainGraphCos->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black), QBrush(Qt::white), 6));
    //    mainGraphCos->setPen(QPen(QColor(120, 120, 120), 2));
    //    QCPGraph *mainGraphGauss = customPlot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft, 1));
    //    mainGraphGauss->data()->set(dataGauss);
    //    mainGraphGauss->setPen(QPen(QColor("#8070B8"), 2));
    //    mainGraphGauss->setBrush(QColor(110, 170, 110, 30));
    //    mainGraphCos->setChannelFillGraph(mainGraphGauss);
    //    mainGraphCos->setBrush(QColor(255, 161, 0, 50));
    //    mainGraphGauss->valueAxis()->setRange(0, 1000);
    //    mainGraphGauss->rescaleKeyAxis();

    //    QCPGraph *subGraphRandom = customPlot->addGraph(subRectLeft->axis(QCPAxis::atBottom), subRectLeft->axis(QCPAxis::atLeft));
    //    subGraphRandom->data()->set(dataRandom);
    //    subGraphRandom->setLineStyle(QCPGraph::lsImpulse);
    //    subGraphRandom->setPen(QPen(QColor("#FFA100"), 1.5));
    //    subGraphRandom->rescaleAxes();

    //    QCPBars *subBars = new QCPBars(subRectRight->axis(QCPAxis::atBottom), subRectRight->axis(QCPAxis::atRight));
    //    subBars->setWidth(3/(double)x3.size());
    //    subBars->setData(x3, y3);
    //    subBars->setPen(QPen(Qt::black));
    //    subBars->setAntialiased(false);
    //    subBars->setAntialiasedFill(false);
    //    subBars->setBrush(QColor("#705BE8"));
    //    subBars->keyAxis()->setSubTicks(false);
    //    subBars->rescaleAxes();
    // setup a ticker for subBars key axis that only gives integer ticks:
    //    QSharedPointer<QCPAxisTickerFixed> intTicker(new QCPAxisTickerFixed);
    //    intTicker->setTickStep(1.0);
    //    intTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
    //    subBars->keyAxis()->setTicker(intTicker);

}

void GlobalStyle::setStyleStatisticPlot(QCustomPlot *customPlot, bool tickAsTime)
{
    //set background color
    GlobalStyle::setBackGroundColor(customPlot);

    //set margin
    //    customPlot->axisRect()->setAutoMargins(QCP::msNone);

    if(tickAsTime)
    {
        QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
        dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
        dateTimeTicker->setTickCount(8);
        customPlot->xAxis->setTicker(dateTimeTicker);

        //     customPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(QDate(2013, 11, 16)), QCPAxisTickerDateTime::dateTimeToKey(QDate(2015, 5, 2)));
        //     dateTimeTicker->setDateTimeFormat("d. MMM\nyyyy");
        dateTimeTicker->setDateTimeFormat("HH:mm\ndd MMM yyyy");
    }
    else
    {
        QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
        customPlot->xAxis->setTicker(fixedTicker);
    }

    //Set the axis color and line type
    customPlot->xAxis->setBasePen(QPen(_axisColorPlot, 1));
    customPlot->yAxis->setBasePen(QPen(_axisColorPlot, 1));
    customPlot->xAxis->setTickPen(QPen(_axisTickPlot, 1));
    customPlot->yAxis->setTickPen(QPen(_axisTickPlot, 1));
    customPlot->xAxis->setSubTickPen(QPen(_axisTickPlot, 1));
    customPlot->yAxis->setSubTickPen(QPen(_axisTickPlot, 1));
    customPlot->xAxis->setTickLabelColor(_axisColorPlot);
    customPlot->yAxis->setTickLabelColor(_axisColorPlot);
    customPlot->xAxis->setTicks(true);
    customPlot->yAxis->setTicks(true);
    customPlot->xAxis->setSubTicks(true);
    customPlot->xAxis->setTickLabels(true);
    customPlot->yAxis->setTickLabels(true);

    //customPlot->xAxis->setTickLabelPadding(10);
    //customPlot->xAxis->setTickLabelRotation(-60);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 10));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 10));

    //Set the grid plot color and line type
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->yAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setSubGridVisible(false);
    customPlot->yAxis->grid()->setSubGridVisible(false);
    customPlot->xAxis->grid()->setSubGridPen(QPen(_gridColorPlot, 1, Qt::DotLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(_gridColorPlot, 1, Qt::DotLine));

    //Set the axis grid color and line type
    customPlot->xAxis->grid()->setPen(QPen(_gridColorPlot, 1, Qt::DotLine));
    customPlot->yAxis->grid()->setPen(QPen(_gridColorPlot, 1, Qt::DotLine));

    //y Axis color and line type
    customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);

    //rescale the axis
    customPlot->rescaleAxes();

    // show legend with slightly transparent background brush:
    customPlot->legend->setVisible(false);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));
}

void GlobalStyle::setTraceColorTemperaturePlot(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColorTemperaturePlot));
}

void GlobalStyle::setTraceColorTemperatureMinPlot(QCPGraph *graph, QCPGraph *graphAbove)
{
    graph->setPen(Qt::NoPen);
    graph->setBrush(QColor(TEMPERATURE_UNDER_PLOT_TRACE));
    graph->setChannelFillGraph(graphAbove);
}

void GlobalStyle::setTraceColorHumidityPlot(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColorHumidityPlot));
    graph->setBrush(QColor(HUMIDITY_UNDER_PLOT_TRACE));
}

void GlobalStyle::setTraceColorHumidityMaxPlot(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColorHumidityPlot));
}

void GlobalStyle::setTraceColorHumidityMinPlot(QCPGraph *graph, QCPGraph *graphAbove)
{
    graph->setPen(Qt::NoPen);
    graph->setBrush(QColor(HUMIDITY_UNDER_PLOT_TRACE));
    graph->setChannelFillGraph(graphAbove);
}

void GlobalStyle::setTraceColorPressurePlot(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColorPressurePlot));
}

void GlobalStyle::setTraceColorPressureMinPlot(QCPGraph *graph, QCPGraph *graphAbove)
{
    graph->setPen(Qt::NoPen);
    graph->setBrush(QColor(PRESSURE_UNDER_PLOT_TRACE));
    graph->setChannelFillGraph(graphAbove);
}

void GlobalStyle::setTraceColorConsoPlot(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColorConsoPlot));
}

void GlobalStyle::setTraceColorConsoMinPlot(QCPGraph *graph, QCPGraph *graphAbove)
{
    graph->setPen(Qt::NoPen);
    graph->setBrush(QColor(CONSO_UNDER_PLOT_TRACE));
    graph->setChannelFillGraph(graphAbove);
}

void GlobalStyle::setTraceColorTankTrace1(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColortank1));
}

void GlobalStyle::setTraceColorTankTrace2(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColortank2));
}

void GlobalStyle::setTraceColorTankTrace3(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColortank3));
}

void GlobalStyle::setTraceColorTankTrace4(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColortank4));
}

void GlobalStyle::setTraceColorTankTrace5(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColortank5));
}

void GlobalStyle::setTraceColorTankTrace6(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColortank6));
}

//void GlobalStyle::setTraceColorTriggerPlot(QCPGraph *graph)
//{
//    graph->setPen(QPen(_errorLineInTrouble));
//}

//void GlobalStyle::setTraceColorTriggerPlot(QCPItemStraightLine *line)
//{
//    line->setPen(QPen(_errorLineInTrouble));
//}

//void GlobalStyle::setPushButtonUnselected(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
//                              "stop: 1" + _backGroundColorPushButtonDark.name() +
//                              ", stop: 0 #ffffff); font: 12pt;");
//}

//void GlobalStyle::setPushButtonBlocked(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color:" + _backGroundColor.name()+ "; font: 12pt;");
//}

//void GlobalStyle::setSpinBoxShape(QSpinBox *spinBox)
//{
//    spinBox->setStyleSheet("QSpinBox::up-button { subcontrol-position: left; width: 30px; height: 40px;}"
//                           "QSpinBox::down-button { subcontrol-position: right; width: 30px; height: 40px;}"
//                           "QSpinBox {background-color: " + _backGroundColorPushButtonLight.name()+
//                           ";}" "QSpinBox { border: 3px inset grey; }");
//}

//void GlobalStyle::setDoublespinBoxShape(QDoubleSpinBox *doubleSpinBox)
//{
//    doubleSpinBox->setStyleSheet("QDoubleSpinBox::up-button { subcontrol-position: left; width: 30px; height: 40px;}"
//                                 "QDoubleSpinBox::down-button { subcontrol-position: right; width: 30px; height: 40px;}"
//                                 "QDoubleSpinBox {background-color: " + _backGroundColorPushButtonLight.name()+
//                                 ";} QDoubleSpinBox { border: 3px inset grey; }");
//}

//void GlobalStyle::setStartButtonToGreen(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
//                              "stop: 1" + _traceColorDigitalPlot.name() +
//                              ", stop: 0 #ffffff); font: bold 22pt;");
//}

//void GlobalStyle::setStartButtonToRed(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
//                              "stop: 1" + _backGroundColorErrorFrame.name() +
//                              ", stop: 0 #ffffff); font: bold 22pt;");
//}

//void GlobalStyle::setButtonStatusBarSelect(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color:" + _backGroundColorPushButtonDark.name() +
//                              "; color:" + _backGroundColorPushButtonLight.name() + "; font: 12pt;");
//}

//void GlobalStyle::setButtonStatusBarUnselect(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color:" + _backGroundColorPushButtonLight.name() +
//                              "; color:" + _backGroundColorPushButtonDark.name() + "; font: 12pt;");
//}

////BACKGROUND
QColor GlobalStyle::_backGroundColor(BACKGROUD_COLOR);
//QColor GlobalStyle::_backGroundColorFrame(BACKGROUD_COLOR_FRAME);
//QColor GlobalStyle::_backGroundColorLabel(BACKGROUD_COLOR_LABEL);
//QColor GlobalStyle::_backGroundColorPlot(BACKGROUD_COLOR_PLOT);
//QColor GlobalStyle::_backGroundColorPushButtonLight(BACKGROUD_COLOR_PUSHBUTTON_LIGHT);
//QColor GlobalStyle::_backGroundColorPushButtonDark(BACKGROUD_COLOR_PUSHBUTTON_DARK);

////ERROR
//QColor GlobalStyle::_backGroundColorErrorFrame(BACKGROUD_COLOR_ERROR_FRAME);
//QColor GlobalStyle::_errorLineInTrouble(ERROR_LINE_COLOR_IN_TROUBLE);

////PLOTS
////Grid
QColor GlobalStyle::_gridColorPlot(GRID_COLOR_PLOT);
//Axis
QColor GlobalStyle::_axisColorPlot(AXIS_COLOR_PLOT);
QColor GlobalStyle::_axisTickPlot(AXIS_COLOR_PLOT);

//pen
//Temperature trace
QColor GlobalStyle::_traceColorTemperaturePlot(TEMPERATURE_PLOT_TRACE);

//Humidity trace
QColor GlobalStyle::_traceColorHumidityPlot(HUMIDITY_PLOT_TRACE);

//Pressure trace
QColor GlobalStyle::_traceColorPressurePlot(PRESSURE_PLOT_TRACE);

//conso trace
QColor GlobalStyle::_traceColorConsoPlot(CONSO_PLOT_TRACE);

//tanks trace
QColor GlobalStyle::_traceColortank1(TANK1_PLOT_TRACE);
QColor GlobalStyle::_traceColortank2(TANK2_PLOT_TRACE);
QColor GlobalStyle::_traceColortank3(TANK3_PLOT_TRACE);
QColor GlobalStyle::_traceColortank4(TANK4_PLOT_TRACE);
QColor GlobalStyle::_traceColortank5(TANK5_PLOT_TRACE);
QColor GlobalStyle::_traceColortank6(TANK6_PLOT_TRACE);

//QColor GlobalStyle::_backGroundLabelDIPlotON(DIGITAL_PLOT_TRACE_ON);
//QColor GlobalStyle::_backGroundLabelRedDIPlotON(DIGITAL_RED_PLOT_TRACE_ON);
