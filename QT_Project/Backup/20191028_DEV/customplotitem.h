#ifndef CUSTOMPLOTITEM_H
#define CUSTOMPLOTITEM_H

#define HOUR_RECCORDING_TO_DISPLAY_IN_PLOT 24
#define NB_OF_SECONDE_IN_PLOT (HOUR_RECCORDING_TO_DISPLAY_IN_PLOT*3600)
#define NB_OF_PIXELS_IN_PLOT (NB_OF_SECONDE_IN_PLOT/(GlobaleStaticValue::delaiToReadValue/1000))

#include <QObject>
#include <QtQuick>
#include <QDateTime>

#include <QFile>

#include <QMetaType>
#include <QQmlEngine>

#include <globalestaticvalue.h>

#include <globalenumerate.h>
#include <globalstyle.h>
#include <qcustomplot.h>

//class QCustomPlot;

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:

    explicit CustomPlotItem( QQuickItem* parent = nullptr, QObject *plotView = nullptr);
    virtual ~CustomPlotItem();

    void paint( QPainter* painter );

    //set plot style
    Q_INVOKABLE void setupStyle(GlobalEnumerate::E_PlotStyle plotstyle, quint8 nbOfTrace);

    //set plot style
    Q_INVOKABLE void setupGraphLabel(quint8 traceNumber,QString titleText);

    //set plot style
    Q_INVOKABLE void setupTraceIsSelected(quint8 traceNumber,bool isVisible);

    // add 1 point to single graph graphNumber
    Q_INVOKABLE void addPoint(const int graphNumber, const double x, const double y);


    // add 1 point to single graph graphNumber
    Q_INVOKABLE void addYValue(qreal valueGraph0, qreal valueGraph1, qreal valueGraph2,
                               qreal valueGraph3 = 0, qreal valueGraph4 = 0, qreal valueGraph5 = 0,
                               qreal settingTriggerValue = 0,
                               bool tickAsDate = true, quint64 tickNumber = 0, bool isTheFirstData = false);

    //clear graph with values
    Q_INVOKABLE void clearGraphAndValues();

    // replot
    Q_INVOKABLE void replot(bool resize);

    // replot
    Q_INVOKABLE void replotWithSavedData(quint16 year, quint8 month, quint8 day);

    // set graphic range according with time reccording in setting
    Q_INVOKABLE void setRange(const quint64 &range);

//    Q_INVOKABLE void initCustomPlot();

    //direction du draw
    // if true, draw left to right, mode roll on
    // if flase, draw right to left, mode trig
    void setDrawRightToLeft(bool drawRightToLeft);

    void setNbPixels(const quint16 &nbPixels);

    void setSettingTriggerValue(const quint8 &settingTriggerValue);

    void setGraph0Label(const QString &graph0Label);

    void setGraph1Label(const QString &graph1Label);

    void setGraph2Label(const QString &graph2Label);

    void setGraph3Label(const QString &graph3Label);

    void setGraph4Label(const QString &graph4Label);

    void setGraph5Label(const QString &graph5Label);

protected:
    void routeMouseEvents( QMouseEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );

private:

    QDateTime _dateTime;
    QObject *_plotView;
    QObject *_qobjectStatisticViewer;

    QCustomPlot *_customPlot;
    QCPGraph *_graph0;
    QCPGraph *_graph1;
    QCPGraph *_graph2;
    QCPGraph *_graph3;
    QCPGraph *_graph4;
    QCPGraph *_graph5;
    QCPBars *_bar0;
    QCPBars *_bar1;
    QCPBars *_bar2;
    QString _graph0Label;
    QString _graph1Label;
    QString _graph2Label;
    QString _graph3Label;
    QString _graph4Label;
    QString _graph5Label;


    //***************************************
    QCPAxisRect * _wideAxisRect;

    QCPAxis *_AxisGraph0;
    QCPAxis *_AxisGraph1;
    QCPAxis *_AxisGraph2;
    //**********************************************

    QCPItemStraightLine *_line;
    QColor _axisTickPlot;

    quint8 _nbOfTrace;
    qint64 _nbPixels;
    quint64 _range;
    quint64 _CPT;
    double _CPTMin;
    double _CPTMax;
    quint8 _yValue;
    quint16 _yValueMin;
    quint16 _yValueMin0;
    quint16 _yValueMin1;
    quint16 _yValueMin2;
    quint16 _yValueMax;
    quint16 _yValueMax0;
    quint16 _yValueMax1;
    quint16 _yValueMax2;
    qreal _settingTriggerValue;
    bool _plotWithYBorderGap;
    bool _isJsutCreated;
    //int _minValue = 0;

    int _objectInstance;

    QColor _traceSettingColor;

    // Data buffers
    QVector<double> _YData;
    QVector<double> _minusYData;
    QVector<double> _XData;

    QVector<int> _XDataInt;
    QVector<int> _Y1DataInt;
    QVector<int> _Y2DataInt;


    //set curve style
    GlobalEnumerate::E_PlotStyle _myPlotStyle;
    void setupTraceWatherStation();
    void setupTraceAnalogTrace(quint8 nbOfTrace);
    void setupTraceStatisticTrace(GlobalEnumerate::E_PlotStyle plotstyle);

    //automatically set three indepedent traces in the same plot
    //(temperature in red, humidity in blue with shadow, pressure in yellow)
    void setupStyleWeatherStation();

    //reload value from files
    void _reloadValue();

    //plot array pointer
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph0;
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph1;
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph2;
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph3;
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph4;
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph5;

    //plot array iterator
    QCPGraphDataContainer::const_iterator _itBegin;
    QCPGraphDataContainer::const_iterator _itEnd;


private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();
    void _recievedRefreshDataTemperaturePlot();


    void updatePlot();
};

#endif // CUSTOMPLOTITEM_H

#pragma once



