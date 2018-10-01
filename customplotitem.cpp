#include "customplotitem.h"

static int counter = 0;

CustomPlotItem::CustomPlotItem(QQuickItem* parent, QObject *plotView ) :
    QQuickPaintedItem( parent ),
    _dateTime(QDateTime::currentDateTime()),
    _plotView(plotView),
    _customPlot(new QCustomPlot()),
    _nbPixels(980),
    _CPT(0),
    _CPTMin(QCPAxisTickerDateTime::dateTimeToKey(this->_dateTime)),
    _CPTMax(_CPTMin),
    _objectInstance(0)
{
    counter++;
    this->_objectInstance = counter;

    qmlRegisterType<CustomPlotItem>("io.qt.CustomPlotItem", 1, 0, "CustomPlotItem");

    _customPlot->addGraph();
    _customPlot->addGraph();
    _customPlot->addGraph();

    _graph0 = _customPlot->graph(0);    //humidity
    _graph1 = _customPlot->graph(1);    //temperature
    _graph2 = _customPlot->graph(2);    //pressure

    _graph0->setName("Humidity");
    _graph1->setName("Temperature");
    _graph2->setName("Pressure x 10");

    _line = new QCPItemStraightLine(_customPlot);

    GlobalStyle::setStylePlot(this->_customPlot);
    GlobalStyle::setTraceColorTemperaturePlot(this->_graph1);
    GlobalStyle::setTraceColorHumidityPlot(this->_graph0);
    GlobalStyle::setTraceColorPressurePlot(this->_graph2);

    //    setFlag( QQuickItem::ItemHasContents, true );
    //     setRenderTarget(QQuickPaintedItem::FramebufferObject);
    //     setAcceptHoverEvents(true);
    //    setAcceptedMouseButtons( Qt::AllButtons );

    _arrayPlotContainerPointerGraph0 = _customPlot->graph(0)->data();
    _arrayPlotContainerPointerGraph1 = _customPlot->graph(1)->data();
    _arrayPlotContainerPointerGraph2 = _customPlot->graph(2)->data();

    this->_itBegin = _arrayPlotContainerPointerGraph0->constBegin();
    this->_itEnd = _arrayPlotContainerPointerGraph0->constEnd();

    //    for (int i = 2; i<20; i++)
    //    {
    //        this->_recievedRefreshDataTemperaturePlot();
    //        //        QMetaObject::invokeMethod(this->_plotView, "addYValue",
    //        //                                  Q_ARG(QVariant, i),
    //        //                                  Q_ARG(QVariant, 6)
    //        //                                  );
    //    }
    connect( this->_customPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );

    setDrawRightToLeft(true);
//    this->initCustomPlot();
    //    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize );
    //    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize );
}


CustomPlotItem::~CustomPlotItem()
{
    delete _customPlot;
    _customPlot = nullptr;
}

//void CustomPlotItem::initCustomPlot()
//{
////    setupQuadraticDemo(_customPlot);
////    _customPlot->replot();
//}


void CustomPlotItem::setDrawRightToLeft(bool drawRightToLeft)
{
    this->_customPlot->xAxis->setRangeReversed(!drawRightToLeft);
}

void CustomPlotItem::replot()
{
    //    qDebug() << Q_FUNC_INFO;

    //    setupQuadraticDemo(_customPlot);

    //        this->updatePlot();
    this->_customPlot->replot();
    //    this->_customPlot->update();
    //    this-> _graph0->layer()->replot();
}

void CustomPlotItem::setNbPixels(const quint16 &nbPixels)
{
    _nbPixels = nbPixels;
}


void CustomPlotItem::paint( QPainter* painter )
{
    if (_customPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        //_customPlot->replot();
        _customPlot->toPainter( &qcpPainter );

        painter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotItem::addPoint(const int graphNumber, const double x, const double y)
{
    if (graphNumber < this->_customPlot->graphCount())
        this->_customPlot->graph( graphNumber )->addData( x,y );
}

void CustomPlotItem::mousePressEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseReleaseEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseDoubleClickEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::graphClicked( QCPAbstractPlottable* plottable )
{
    qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotItem::routeMouseEvents( QMouseEvent* event )
{
    if (_customPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent( _customPlot, newEvent );
        QCoreApplication::postEvent( _customPlot, newEvent );
    }
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (_customPlot)
    {
        _customPlot->setGeometry( 0, 0, width(), height() );
    }
}

void CustomPlotItem::_recievedRefreshDataTemperaturePlot()
{
    int highHumidity = 80;
    int lowHumidity = 70;
    int highPressure = 105;
    int lowPressure = 95;
    int highTemperature = 10;
    int lowTemperature = 30;

    int temperature = qrand() % ((highTemperature + 1) - lowTemperature) + lowTemperature;
    int humidity = qrand() % ((highHumidity + 1) - lowHumidity) + lowHumidity;
    int pressure = qrand() % ((highPressure + 1) - lowPressure) + lowPressure;

    QMetaObject::invokeMethod(this->_plotView, "addYValue",
                              Q_ARG(QVariant, temperature),
                              Q_ARG(QVariant, humidity),
                              Q_ARG(QVariant, pressure),
                              Q_ARG(QVariant, 6)
                              );

}

void CustomPlotItem::updatePlot()
{
    // add data on th plot
    this-> _graph0->setData(_arrayPlotContainerPointerGraph0);


    // make key axis range scroll with the data:
    this->_customPlot->xAxis->setRange(_CPT, this->_nbPixels, Qt::AlignRight);

    this->_customPlot->yAxis->rescale();

    // Update the plot widget
    //ui->widget_AI->replot();
}

void CustomPlotItem::addYValue(qreal valueGraph0, qreal valueGraph1, qreal valueGraph2, qreal settingTriggerValue)
{
    qDebug() << this->_dateTime;

//    QCPGraphDataContainer::const_iterator itBegin = _arrayPlotContainerPointerGraph0->constBegin();

    QDateTime dateTimeNow = QDateTime::currentDateTime();

//    _CPT = dateTimeNow.currentMSecsSinceEpoch()/100;
    _CPT = QCPAxisTickerDateTime::dateTimeToKey(dateTimeNow);
    qDebug() << "CPT : " << _CPT << "it: " << this->_itBegin << "itEnd: " << this->_itEnd;


    //_CPT++;
    _settingTriggerValue = settingTriggerValue;

    _line->point1->setCoords(0, _settingTriggerValue);
    _line->point2->setCoords(_CPTMax, _settingTriggerValue);


//    _arrayPlotContainerPointerGraph0->add(QCPGraphData(_CPT, valueGraph1));
//    _arrayPlotContainerPointerGraph1->add(QCPGraphData(_CPT, valueGraph0));
//    _arrayPlotContainerPointerGraph2->add(QCPGraphData(_CPT, valueGraph2));

    _arrayPlotContainerPointerGraph0->add(QCPGraphData(QCPAxisTickerDateTime::dateTimeToKey(dateTimeNow), valueGraph1));
    _arrayPlotContainerPointerGraph1->add(QCPGraphData(QCPAxisTickerDateTime::dateTimeToKey(dateTimeNow), valueGraph0));
    _arrayPlotContainerPointerGraph2->add(QCPGraphData(QCPAxisTickerDateTime::dateTimeToKey(dateTimeNow), valueGraph2));

    this->_itEnd = _arrayPlotContainerPointerGraph0->constEnd();

    if(_arrayPlotContainerPointerGraph0->size() >= _nbPixels)
    {
//        _CPTMin = _CPT - _nbPixels;
//        _CPTMax = _CPT;
//        _arrayPlotContainerPointerGraph0->remove(_CPTMin);
//        _line->point1->setCoords(_CPTMin, _settingTriggerValue);
//        _line->point2->setCoords(_CPTMax, _settingTriggerValue);

         _arrayPlotContainerPointerGraph0->remove(this->_itBegin->key);
         _arrayPlotContainerPointerGraph1->remove(this->_itBegin->key);
         _arrayPlotContainerPointerGraph2->remove(this->_itBegin->key);

         this->_itBegin = _arrayPlotContainerPointerGraph0->constBegin();

    }

    qDebug() << _objectInstance << Q_FUNC_INFO << _arrayPlotContainerPointerGraph0->size();
    qDebug() << _objectInstance << Q_FUNC_INFO << _arrayPlotContainerPointerGraph1->size();
    qDebug() << _objectInstance << Q_FUNC_INFO << _arrayPlotContainerPointerGraph2->size();

    updateCustomPlotSize();
//    replot();
}

void CustomPlotItem::onCustomReplot()
{
    qDebug() << _objectInstance << Q_FUNC_INFO;
    _customPlot->yAxis->rescale();
//    _customPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(this->_dateTime),
//                                 QCPAxisTickerDateTime::dateTimeToKey(dateTimeNow));
//    _customPlot->xAxis->setRange(this->_itBegin->key*1000,this->_itEnd->key*1000);
    _customPlot->xAxis->rescale();
//    _customPlot->xAxis->setRange( this->_CPTMin, this->_CPTMax);
    update();
}

void CustomPlotItem::setupQuadraticDemo( QCustomPlot* customPlot )
{
    //    qDebug() << Q_FUNC_INFO << _CPT;
    qreal x = 0;

    x =  (qrand() % 10) + 1;
    this->addYValue(x,x,x,3);


    // give the axes some labels:
    customPlot->xAxis->setLabel( "x" );
    customPlot->yAxis->setLabel( "y" );

}
