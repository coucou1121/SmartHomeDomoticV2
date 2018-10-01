#include "globalstyle.h"

GlobalStyle::GlobalStyle()
{
}

//void GlobalStyle::setbackGroundColorLabel(QLabel *label)
//{
//    label->setStyleSheet("background-color:" + _backGroundColorPushButtonDark.name() +
//                              "; color:" + _backGroundColorPushButtonLight.name() + "; font: 12pt;");
//}

//void GlobalStyle::setbackGroundColorLabel(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color:" + _backGroundColorPushButtonDark.name() +
//                              "; color:" + _backGroundColorPushButtonLight.name() + "; font: 12pt;");
//}

//void GlobalStyle::setbackGroundColorLabelUnselected(QLabel *label)
//{
//    label->setStyleSheet("background-color:" + _backGroundColorPushButtonLight.name() +
//                              "; color:" + _backGroundColorPushButtonDark.name() + "; font: 12pt;");
//}

//void GlobalStyle::setbackGroundColorLabelUnselected(QPushButton *pushButton)
//{
//    pushButton->setStyleSheet("background-color:" + _backGroundColorPushButtonLight.name() +
//                              "; color:" + _backGroundColorPushButtonDark.name() + "; font: 12pt;");
//}

//void GlobalStyle::setbackGroundColorLabelPlot(QLabel *label)
//{
//    label->setStyleSheet("background-color:" + _backGroundColorLabel.name() + "; font: 12pt;");
//}

//void GlobalStyle::setbackGroundColorLabelPlotSmall(QLabel *label)
//{
//    label->setStyleSheet("background-color:" + _backGroundColorLabel.name() + "; font: 10pt;");
//}

//void GlobalStyle::setbackGroundColorFrame(QFrame *frame)
//{
//    frame->setStyleSheet("background-color:" + _backGroundColorLabel.name() + "; font: 12pt;");
//}

//void GlobalStyle::setbackGroundColorFrame(QWidget *widget)
//{
//    widget->setStyleSheet("background-color:" + _backGroundColorLabel.name() + "; font: 12pt;");
//}

//void GlobalStyle::setBackGroundColorPlot(QCPAxisRect *qcpAxisRect)
//{
//    qcpAxisRect->setBackground(_backGroundColorPlot);
//}

//void GlobalStyle::setBackGroundColorDILabel(QLabel *label)
//{
//    label->setStyleSheet("background-color:" + _backGroundLabelDIPlotON.name() + ";");
//}

//void GlobalStyle::setBackGroundColorRedDILabel(QLabel *label)
//{
//    label->setStyleSheet("background-color:" + _backGroundLabelRedDIPlotON.name() + ";");
//}

//void GlobalStyle::setErrorColor(QLabel *label)
//{
//    label->setStyleSheet("background-color:" + _backGroundColorErrorFrame.name()+ ";");
//}

//void GlobalStyle::setErrorColor(QFrame *frame)
//{
//    frame->setStyleSheet("background-color:" + _errorLineInTrouble.name()+ ";");
//}

void GlobalStyle::setBackGroundColor(QCustomPlot *customPlot)
{
    customPlot->setBackground(_backGroundColor);
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

void GlobalStyle::setStylePlot(QCustomPlot *customPlot)
{

    //set background color
    GlobalStyle::setBackGroundColor(customPlot);

    //set margin
//    customPlot->axisRect()->setAutoMargins(QCP::msNone);

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
     customPlot->xAxis->setTicker(dateTimeTicker);

//     customPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(QDate(2013, 11, 16)), QCPAxisTickerDateTime::dateTimeToKey(QDate(2015, 5, 2)));
//     dateTimeTicker->setDateTimeFormat("d. MMM\nyyyy");
     dateTimeTicker->setDateTimeFormat("HH:mm:ss\ndd MMM yyyy");

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

   //Set the grid plot color and line type
   customPlot->xAxis->grid()->setVisible(false);
   customPlot->yAxis->grid()->setVisible(false);
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
   customPlot->legend->setVisible(true);
   customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
   customPlot->legend->setBrush(QColor(255, 255, 255, 150));
}

void GlobalStyle::setTraceColorTemperaturePlot(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColorTemperaturePlot));
}

void GlobalStyle::setTraceColorHumidityPlot(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColorHumidityPlot));
    graph->setBrush(QColor(HUMIDITY_UNDER_PLOT_TRACE));
}

void GlobalStyle::setTraceColorPressurePlot(QCPGraph *graph)
{
    graph->setPen(QPen(_traceColorPressurePlot));
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


//QColor GlobalStyle::_backGroundLabelDIPlotON(DIGITAL_PLOT_TRACE_ON);
//QColor GlobalStyle::_backGroundLabelRedDIPlotON(DIGITAL_RED_PLOT_TRACE_ON);
