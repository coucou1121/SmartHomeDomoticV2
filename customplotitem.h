#ifndef CUSTOMPLOTITEM_H
#define CUSTOMPLOTITEM_H

#include <QObject>
#include <QtQuick>

#include <QMetaType>
#include <QQmlEngine>

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

    // add 1 point to single graph graphNumber
    Q_INVOKABLE void addPoint(const int graphNumber, const double x, const double y);


    // add 1 point to single graph graphNumber
    Q_INVOKABLE void addYValue(qreal valueGraph0, qreal valueGraph1, qreal valueGraph2, qreal settingTriggerValue);

    // replot
    Q_INVOKABLE void replot();

//    Q_INVOKABLE void initCustomPlot();

    //direction du draw
    // if true, draw left to right, mode roll on
    // if flase, draw right to left, mode trig
    void setDrawRightToLeft(bool drawRightToLeft);

    void setNbPixels(const quint16 &nbPixels);

    void setSettingTriggerValue(const quint8 &settingTriggerValue);

protected:
    void routeMouseEvents( QMouseEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );

    void setupQuadraticDemo( QCustomPlot* customPlot );

private:

    QDateTime _dateTime;
    QObject *_plotView;

    QCustomPlot *_customPlot;
    QCPGraph *_graph0;
    QCPGraph *_graph1;
    QCPGraph *_graph2;
    QCPItemStraightLine *_line;
    QColor _axisTickPlot;

    quint16 _nbPixels;
    double _CPT;
    double _CPTMin;
    double _CPTMax;
    quint8 _yValue;
    qreal _settingTriggerValue;
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

    //set plot style
    void setupStyle(QCustomPlot *customPlot);

    //set curve style
    void setupTrace(QCPGraph *graph);

    //plot array pointer
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph0;
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph1;
    QSharedPointer<QCPGraphDataContainer> _arrayPlotContainerPointerGraph2;

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



