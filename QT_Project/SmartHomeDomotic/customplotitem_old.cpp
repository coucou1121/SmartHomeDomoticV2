#include "customplotitem.h"

static int counter = 0;

CustomPlotItem::CustomPlotItem(QQuickItem* parent, QObject *plotView ) :
    QQuickPaintedItem( parent ),
    _dateTime(QDateTime::currentDateTime()),
    _plotView(plotView),
    _customPlot(new QCustomPlot()),
    _graph0Label(""),
    _graph1Label(""),
    _graph2Label(""),
    _graph3Label(""),
    _graph4Label(""),
    _graph5Label(""),
    _nbPixels(NB_OF_PIXELS_IN_PLOT),
    _range(NB_OF_PIXELS_IN_PLOT*(GlobaleStaticValue::delaiToReadValue/1000)),
    _nbOfTrace(0),
    _CPT(0),
    _CPTMin(QCPAxisTickerDateTime::dateTimeToKey(this->_dateTime)),
    _CPTMax(_CPTMin),
    _yValueMin(2000),
    _yValueMax(0),
    _plotWithYBorderGap(true),
    _objectInstance(0),
    _myPlotStyle(GlobalEnumerate::PLOT_STYLE_WEATHER_STATION)
{
    counter++;
    this->_objectInstance = counter;
    
    qmlRegisterType<CustomPlotItem>("io.qt.CustomPlotItem", 1, 0, "CustomPlotItem");
    
    
    connect( this->_customPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );
    
    setDrawRightToLeft(true);
}


CustomPlotItem::~CustomPlotItem()
{
    delete _customPlot;
    _customPlot = nullptr;
}

void CustomPlotItem::setDrawRightToLeft(bool drawRightToLeft)
{
    this->_customPlot->xAxis->setRangeReversed(!drawRightToLeft);
}

void CustomPlotItem::replot(bool resize)
{
    //    qDebug() << Q_FUNC_INFO;
    
    //    setupQuadraticDemo(_customPlot);
    if(resize)
    {
        _customPlot->xAxis->rescale();
    }
    
    //        this->updatePlot();
    this->_customPlot->replot();

    updateCustomPlotSize();

    //    this->_customPlot->update();
    //    this-> _graph0->layer()->replot();
}

void CustomPlotItem::replotWithSavedData(quint16 year, quint8 month, quint8 day)
{
    QDateTime dateTimeToAnalyse =  QDateTime::currentDateTime();
    QDate dateToAnalyse;
    dateToAnalyse.setDate(year,month,day);
    dateTimeToAnalyse.setDate(dateToAnalyse);
    
    QString directoryfileName = GlobaleStaticValue::saveDataMain;
    QString fileName = "";
    
    if(month != 0)
    {
        directoryfileName += dateTimeToAnalyse.toString("yyyy") + "/";
        fileName += dateTimeToAnalyse.toString("yyyy-MM");
    }
    
    if(day != 0)
    {
        directoryfileName += dateTimeToAnalyse.toString("MM") + "/";
        fileName = dateTimeToAnalyse.toString("yyyy-MM-dd");
    }
    
    QFile fileToAnalyse(directoryfileName +  "/" + fileName + ".csv");
    
    QTextStream streamAnalyse(&fileToAnalyse);
    
    QStringList listeOfData;
    
    qint8 lineNumber = 0;
    double tempMin = 200;
    double tempMax = 0;
    double humMin = 200;
    double humMax = 0 ;
    double pressMin = 2000;
    double pressMax = 0;
    qint16 volumeChan0 = 0;
    qint16 volumeChan1 = 0;
    qint16 volumeChan2 = 0;
    qint16 volumeChan3 = 0;
    qint16 volumeTotal = 0;
    qint16 volumeConsoTotal = 0;

    double memoTempMin = 200;
    double memoTempMax = 0;
    double memoHumMin = 200;
    double memoHumMax = 0 ;
    double memoPressMin = 2000;
    double memoPressMax = 0;
    qint16 memoVolumeTotal = 0;
    qint16 memoConsoTotalDayBefore = 0;
    
    bool isTheFirstData = true;
    
    if (fileToAnalyse.open(QFile::ReadOnly))
    {
        while (!streamAnalyse.atEnd())
        {
            QString s=fileToAnalyse.readLine(); // reads line from file
            listeOfData.append(s.split(",")); // appends first column to list, ',' is separator
            //            qDebug() << "_updateDataForTheDay" << listeOfData.count() << listeOfData[1];
            
            //Analyse the data
            lineNumber = listeOfData[0].toInt();
            
            tempMin = listeOfData[1].toDouble();
            tempMax = listeOfData[2].toDouble();
            
            humMin = listeOfData[3].toDouble();
            humMax = listeOfData[4].toDouble();
            
            pressMin = listeOfData[5].toDouble();
            pressMax = listeOfData[6].toDouble();
            
            volumeChan0 = listeOfData[7].toInt();
            volumeChan1 = listeOfData[8].toInt();
            volumeChan2 = listeOfData[9].toInt();
            volumeChan3 = listeOfData[10].toInt();

            volumeTotal = listeOfData[11].toInt();
            volumeConsoTotal = listeOfData[12].toInt();

            listeOfData.clear();
            
            memoTempMin = tempMin < memoTempMin ? tempMin :  memoTempMin;
            memoTempMax = tempMax > memoTempMin ? tempMax :  memoTempMin;
            memoHumMin = humMin < memoHumMin ? humMin :  memoHumMin;
            memoHumMax = humMax > memoHumMax ? humMax :  memoHumMax;
            memoPressMin = pressMin < memoPressMin ? pressMin :  memoPressMin;
            memoPressMax = pressMax > memoPressMax ? pressMax :  memoPressMax;
            memoPressMax = pressMax > memoPressMax ? pressMax :  memoPressMax;
            memoVolumeTotal = volumeTotal > memoVolumeTotal ? volumeTotal : memoVolumeTotal;

            switch (this->_myPlotStyle)
            {
            case GlobalEnumerate::PLOT_STYLE_TEMPERATURE_TRACE:
                this->addYValue(tempMin, tempMax, 0, 0, 0, 0,volumeTotal,
                                false, lineNumber, isTheFirstData);
                break;
            case GlobalEnumerate::PLOT_STYLE_HUMIDITY_TRACE:
                this->addYValue(humMin, humMax, 0, 0, 0, 0,volumeTotal,
                                false, lineNumber, isTheFirstData);
                break;
            case GlobalEnumerate::PLOT_STYLE_PRESSURE_TRACE:
                this->addYValue(pressMin, pressMax, 0, 0, 0, 0,volumeTotal,
                                false, lineNumber, isTheFirstData);
                break;
            case GlobalEnumerate::PLOT_STYLE_CONSO_TRACE:
                this->addYValue(0, volumeConsoTotal, 0, 0, 0, 0,volumeTotal,
                                false, lineNumber, isTheFirstData);
                break;
            default:
                this->addYValue(tempMin, tempMax, humMin,
                                humMax, pressMin/10, pressMax/10,
                                volumeTotal, false, lineNumber, isTheFirstData);
                break;
            }
            isTheFirstData = false;
        }
    }
    else
    {
        qDebug() << "cannot open fileToAnalyse" << fileName;
    }
    fileToAnalyse.close();
    
    //    QMetaObject::invokeMethod(this->_qobjectStatisticViewer, "setStatisticValues",
    //                              Q_ARG(QVariant, QString::number(memoTempMin,'f', 2)),
    //                              Q_ARG(QVariant, QString::number(memoTempMax,'f', 2)),
    //                              Q_ARG(QVariant, QString::number(memoHumMin,'f', 2)),
    //                              Q_ARG(QVariant, QString::number(memoHumMax,'f', 2)),
    //                              Q_ARG(QVariant, QString::number(memoPressMin,'f', 1)),
    //                              Q_ARG(QVariant, QString::number(memoPressMax,'f', 1)),
    //                              Q_ARG(QVariant, QString::number(memoConsoTotal,'f', 0))
    //                              );
    
    
    //    //update screen values for today
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceTemperatureMinDayText", QString::number(memoTempMin, 'f', 2));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceTemperatureMaxDayText", QString::number(memoTempMax, 'f', 2));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceHumidityMinDayText", QString::number(memoHumMin, 'f', 2));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceHumidityMaxDayText", QString::number(memoHumMax, 'f', 2));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceAtmoPressurMinDayText", QString::number(memoPressMin, 'f', 1));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceAtmoPressurMaxDayText", QString::number(memoPressMax, 'f', 1));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceConsoDayText", QString::number(memoConsoTotal, 'f', 0));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceConsoDayBeforeText", QString::number(memoConsoTotalDayBefore, 'f', 0));
    
    //    this->replot(true);
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

void CustomPlotItem::setRange(const quint64 &range)
{
    _range = range;
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
    
    //    QMetaObject::invokeMethod(this->_plotView, "addYValue",
    //                              Q_ARG(QVariant, temperature),
    //                              Q_ARG(QVariant, humidity),
    //                              Q_ARG(QVariant, pressure),
    //                              Q_ARG(QVariant, 6)
    //                              );
    
}

void CustomPlotItem::updatePlot()
{
    // add data on th plot
    this-> _graph0->setData(_arrayPlotContainerPointerGraph0);
    
    
    // make key axis range scroll with the data:
    //this->_customPlot->xAxis->setRange(_CPT, this->_nbPixels, Qt::AlignRight);
    
    this->_customPlot->yAxis->rescale();
    
    // Update the plot widget
    //ui->widget_AI->replot();
}

void CustomPlotItem::addYValue(qreal valueGraph0, qreal valueGraph1, qreal valueGraph2,
                               qreal valueGraph3, qreal valueGraph4, qreal valueGraph5,
                               qreal settingTriggerValue,
                               bool tickAsDate, quint8 tickNumber, bool isTheFirstData)
{
    //    qDebug() << this->_dateTime;
    
    //    QCPGraphDataContainer::const_iterator itBegin = _arrayPlotContainerPointerGraph0->constBegin();
    static quint8 CPT = 0;
    //    QDateTime dateTimeNow = QDateTime::currentDateTime();
    static quint64 memoRange = 0;

    if(tickAsDate)
    {
        //        _CPT = QDateTime::currentDateTime().toTime_t()/60000;
        _CPT = QDateTime::currentDateTime().toMSecsSinceEpoch()/(1000);
    }
    else
    {
        //        CPT = CPT > 30 ? 0 : CPT+1;
        //        _CPT = CPT;
        _CPT = tickNumber;
        
        if(isTheFirstData)
        {
            for (int i = 1; i<=this->_nbOfTrace; i++)
            {
                switch (i) {
                case 1:
                    _arrayPlotContainerPointerGraph0->clear();
                    break;
                case 2:
                    _arrayPlotContainerPointerGraph1->clear();
                    break;
                case 3:
                    _arrayPlotContainerPointerGraph2->clear();
                    break;
                case 4:
                    _arrayPlotContainerPointerGraph3->clear();
                    break;
                case 5:
                    _arrayPlotContainerPointerGraph4->clear();
                    break;
                case 6:
                    _arrayPlotContainerPointerGraph5->clear();
                    break;
                default:
                    break;
                }
            }
        }
    }
    //    _CPT = dateTimeNow.currentMSecsSinceEpoch()/100;
    //    qDebug() << "CPT : " << _CPT << "it: " << this->_itBegin << "itEnd: " << this->_itEnd;
    
    //    _CPT = QCPAxisTickerDateTime::dateTimeToKey(dateTimeNow);
    
    //   _CPT = QDateTime::currentDateTime().toTime_t();
    
    
    //_CPT++;
    _settingTriggerValue = settingTriggerValue;
    
    //    _line->point1->setCoords(0, _settingTriggerValue);
    //    _line->point2->setCoords(_CPTMax, _settingTriggerValue);
    
    
    for (int i = 1; i<=this->_nbOfTrace; i++)
    {
        switch (i) {
        case 1:
            _arrayPlotContainerPointerGraph0->add(QCPGraphData(_CPT, valueGraph0));
            this->_yValueMin = valueGraph0 < this->_yValueMin ? valueGraph0 : this->_yValueMin;
            this->_yValueMax = valueGraph0 > this->_yValueMax ? valueGraph0 : this->_yValueMax;
            break;
        case 2:
            _arrayPlotContainerPointerGraph1->add(QCPGraphData(_CPT, valueGraph1));
            this->_yValueMin = valueGraph1 < this->_yValueMin ? valueGraph1 : this->_yValueMin;
            this->_yValueMax = valueGraph1 > this->_yValueMax ? valueGraph1 : this->_yValueMax;
            break;
        case 3:
            _arrayPlotContainerPointerGraph2->add(QCPGraphData(_CPT, valueGraph2));
            this->_yValueMin = valueGraph2 < this->_yValueMin ? valueGraph2 : this->_yValueMin;
            this->_yValueMax = valueGraph2 > this->_yValueMax ? valueGraph2 : this->_yValueMax;
            break;
        case 4:
            _arrayPlotContainerPointerGraph3->add(QCPGraphData(_CPT, valueGraph3));
            this->_yValueMin = valueGraph3 < this->_yValueMin ? valueGraph3 : this->_yValueMin;
            this->_yValueMax = valueGraph3 > this->_yValueMax ? valueGraph3 : this->_yValueMax;
            break;
        case 5:
            _arrayPlotContainerPointerGraph4->add(QCPGraphData(_CPT, valueGraph4));
            this->_yValueMin = valueGraph4 < this->_yValueMin ? valueGraph4 : this->_yValueMin;
            this->_yValueMax = valueGraph4 > this->_yValueMax ? valueGraph4 : this->_yValueMax;
            break;
        case 6:
            _arrayPlotContainerPointerGraph5->add(QCPGraphData(_CPT, valueGraph5));
            this->_yValueMin = valueGraph5 < this->_yValueMin ? valueGraph5 : this->_yValueMin;
            this->_yValueMax = valueGraph5 > this->_yValueMax ? valueGraph5 : this->_yValueMax;
            break;
        default:
            break;
        }
    }
    
    //        _arrayPlotContainerPointerGraph0->add(QCPGraphData(_CPT, valueGraph1));
    //        _arrayPlotContainerPointerGraph1->add(QCPGraphData(_CPT, valueGraph0));
    //        _arrayPlotContainerPointerGraph2->add(QCPGraphData(_CPT, valueGraph2));
    
    
    this->_itEnd = _arrayPlotContainerPointerGraph0->constEnd();
    
    //    qDebug() << Q_FUNC_INFO << "plot container size: " << this->_arrayPlotContainerPointerGraph0->size() << " / "
    //             << this->_nbPixels;
    
    if(_arrayPlotContainerPointerGraph0->size() >= _nbPixels)
    {
        //        _CPTMin = _CPT - _nbPixels;
        //        _CPTMax = _CPT;
        //        _arrayPlotContainerPointerGraph0->remove(_CPTMin);
        //        _line->point1->setCoords(_CPTMin, _settingTriggerValue);
        //        _line->point2->setCoords(_CPTMax, _settingTriggerValue);
        for (int i = 1; i<=this->_nbOfTrace; i++)
        {
            switch (i) {
            case 1:
                _arrayPlotContainerPointerGraph0->remove(this->_itBegin->key);
                break;
            case 2:
                _arrayPlotContainerPointerGraph1->remove(this->_itBegin->key);
                break;
            case 3:
                _arrayPlotContainerPointerGraph2->remove(this->_itBegin->key);
                break;
            case 4:
                _arrayPlotContainerPointerGraph3->remove(this->_itBegin->key);
                break;
            case 5:
                _arrayPlotContainerPointerGraph4->remove(this->_itBegin->key);
                break;
            case 6:
                _arrayPlotContainerPointerGraph5->remove(this->_itBegin->key);
                break;
            default:
                break;
            }
        }
        
        this->_itBegin = _arrayPlotContainerPointerGraph0->constBegin();
        
    }
    
    //    qDebug() << _objectInstance << Q_FUNC_INFO << _arrayPlotContainerPointerGraph0->size();
    //    qDebug() << _objectInstance << Q_FUNC_INFO << _arrayPlotContainerPointerGraph1->size();
    //    qDebug() << _objectInstance << Q_FUNC_INFO << _arrayPlotContainerPointerGraph2->size();
    
    updateCustomPlotSize();

    _customPlot->xAxis->setRange(_CPT-(this->_range),  _CPT);

//    qDebug() << Q_FUNC_INFO << this->_range;

    if(memoRange != this->_range)
    {
        update();
        memoRange=this->_range;
    }

}

void CustomPlotItem::clearGraphAndValues()
{
    this->_customPlot->clearGraphs();
}

void CustomPlotItem::onCustomReplot()
{
    if(this->_plotWithYBorderGap)
    {
        _customPlot->yAxis->setRange(this->_yValueMin-10, this->_yValueMax);
    }
    else
    {
        _customPlot->yAxis->rescale();
    }
    
    update();
}

void CustomPlotItem::setGraph5Label(const QString &graph5Label)
{
    _graph5Label = graph5Label;
}

void CustomPlotItem::setGraph4Label(const QString &graph4Label)
{
    _graph4Label = graph4Label;
}

void CustomPlotItem::setGraph3Label(const QString &graph3Label)
{
    _graph3Label = graph3Label;
}

void CustomPlotItem::setGraph2Label(const QString &graph2Label)
{
    _graph2Label = graph2Label;
}

void CustomPlotItem::setGraph1Label(const QString &graph1Label)
{
    _graph1Label = graph1Label;
}

void CustomPlotItem::setGraph0Label(const QString &graph0Label)
{
    _graph0Label = graph0Label;
}

void CustomPlotItem::setupStyle(GlobalEnumerate::E_PlotStyle plotstyle, quint8 nbOfTrace)
{
    
    this->_myPlotStyle = plotstyle;
    //   this->_nbOfTrace = nbOfTrace;
    this->_nbOfTrace = this->_nbOfTrace != 0 ? this->_nbOfTrace : nbOfTrace;
    
    for (int i = 1; i <= this->_nbOfTrace; i++)
    {
        _customPlot->addGraph();
        switch (i) {
        case 1:
            this->_graph0 = _customPlot->graph(0);
            this->_graph0->setName(this->_graph0Label);
            GlobalStyle::setTraceColorTankTrace1(this->_graph0);
            _arrayPlotContainerPointerGraph0 = _customPlot->graph(0)->data();
            break;
        case 2:
            this->_graph1 = _customPlot->graph(1);
            this->_graph1->setName("");
            GlobalStyle::setTraceColorTankTrace2(this->_graph1);
            _arrayPlotContainerPointerGraph1 = _customPlot->graph(1)->data();
            break;
        case 3:
            this->_graph2 = _customPlot->graph(2);
            this->_graph2->setName("");
            GlobalStyle::setTraceColorTankTrace3(this->_graph2);
            _arrayPlotContainerPointerGraph2 = _customPlot->graph(2)->data();
            break;
        case 4:
            this->_graph3 = _customPlot->graph(3);
            this->_graph3->setName("");
            GlobalStyle::setTraceColorTankTrace4(this->_graph3);
            _arrayPlotContainerPointerGraph3 = _customPlot->graph(3)->data();
            break;
        case 5:
            this->_graph4 = _customPlot->graph(4);
            this->_graph4->setName("");
            GlobalStyle::setTraceColorTankTrace5(this->_graph4);
            _arrayPlotContainerPointerGraph4 = _customPlot->graph(4)->data();
            break;
        case 6:
            this->_graph5 = _customPlot->graph(5);
            this->_graph5->setName("");
            GlobalStyle::setTraceColorTankTrace6(this->_graph5);
            _arrayPlotContainerPointerGraph5 = _customPlot->graph(5)->data();
            break;
        default:
            break;
        }
    }
    
    
    
    switch ((GlobalEnumerate::E_PlotStyle)plotstyle)
    {
    case GlobalEnumerate::PLOT_STYLE_WEATHER_STATION:
        this->_plotWithYBorderGap = true;
        this->setupTraceWatherStation();
        GlobalStyle::setStylePlot(this->_customPlot, true);
        break;
    case GlobalEnumerate::PLOT_STYLE_ANANLOG_TRACE:
        this->_plotWithYBorderGap = true;
        this->setupTraceAnalogTrace(nbOfTrace);
        GlobalStyle::setStylePlot(this->_customPlot, true);
        break;
    case GlobalEnumerate::PLOT_STYLE_STATISTIC_TRACE:
        this->_plotWithYBorderGap = false;
        this->setupTraceStatisticTrace(GlobalEnumerate::PLOT_STYLE_STATISTIC_TRACE);
        GlobalStyle::setStyleStatisticPlot(this->_customPlot, false);
        break;
    case GlobalEnumerate::PLOT_STYLE_TEMPERATURE_TRACE:
        this->_plotWithYBorderGap = false;
        this->setupTraceStatisticTrace(GlobalEnumerate::PLOT_STYLE_TEMPERATURE_TRACE);
        GlobalStyle::setStyleStatisticPlot(this->_customPlot, false);
        break;
    case GlobalEnumerate::PLOT_STYLE_HUMIDITY_TRACE:
        this->_plotWithYBorderGap = false;
        this->setupTraceStatisticTrace(GlobalEnumerate::PLOT_STYLE_HUMIDITY_TRACE);
        GlobalStyle::setStyleStatisticPlot(this->_customPlot, false);
        break;
    case GlobalEnumerate::PLOT_STYLE_PRESSURE_TRACE:
        this->_plotWithYBorderGap = false;
        this->setupTraceStatisticTrace(GlobalEnumerate::PLOT_STYLE_PRESSURE_TRACE);
        GlobalStyle::setStyleStatisticPlot(this->_customPlot, false);
        break;
    case GlobalEnumerate::PLOT_STYLE_CONSO_TRACE:
        this->_plotWithYBorderGap = false;
        this->setupTraceStatisticTrace(GlobalEnumerate::PLOT_STYLE_CONSO_TRACE);
        GlobalStyle::setStyleStatisticPlot(this->_customPlot, false);
        break;
    default:
        break;
    }
}

void CustomPlotItem::setupGraphLabel(quint8 traceNumber, QString titleText)
{
    //    qDebug() << "coucou";
    
    bool traceExiste = false;
    
    traceExiste = traceNumber > this->_nbOfTrace ? false : true;
    
    if(traceExiste)
    {
        switch (traceNumber-1) {
        case 0:
            this->_graph0->setName(titleText);
            break;
        case 1:
            this->_graph1->setName(titleText);
            break;
        case 2:
            this->_graph2->setName(titleText);
            break;
        case 3:
            this->_graph3->setName(titleText);
            break;
        case 4:
            this->_graph4->setName(titleText);
            break;
        case 5:
            this->_graph5->setName(titleText);
            break;
        default:
            break;
        }
    }
}

void CustomPlotItem::setupTraceIsSelected(quint8 traceNumber, bool isVisible)
{
    bool traceExiste = false;
    
    traceExiste = traceNumber > this->_nbOfTrace ? false : true;
    if(isVisible)
    {
        this->_customPlot->addGraph();
        _nbOfTrace++;
        
        switch (_nbOfTrace)
        {
        case 1:
            this->_graph0 = _customPlot->graph(0);
            this->_graph0->setName(this->_graph0Label);
            GlobalStyle::setTraceColorTankTrace1(this->_graph0);
            _arrayPlotContainerPointerGraph0 = _customPlot->graph(0)->data();
            break;
        case 2:
            this->_graph1 = _customPlot->graph(1);
            this->_graph1->setName("");
            GlobalStyle::setTraceColorTankTrace2(this->_graph1);
            _arrayPlotContainerPointerGraph1 = _customPlot->graph(1)->data();
            break;
        case 3:
            this->_graph2 = _customPlot->graph(2);
            this->_graph2->setName("");
            GlobalStyle::setTraceColorTankTrace3(this->_graph2);
            _arrayPlotContainerPointerGraph2 = _customPlot->graph(2)->data();
            break;
        case 4:
            this->_graph3 = _customPlot->graph(3);
            this->_graph3->setName("");
            GlobalStyle::setTraceColorTankTrace4(this->_graph3);
            _arrayPlotContainerPointerGraph3 = _customPlot->graph(3)->data();
            break;
        case 5:
            this->_graph4 = _customPlot->graph(4);
            this->_graph4->setName("");
            GlobalStyle::setTraceColorTankTrace5(this->_graph4);
            _arrayPlotContainerPointerGraph4 = _customPlot->graph(4)->data();
            break;
        case 6:
            this->_graph5 = _customPlot->graph(5);
            this->_graph5->setName("");
            GlobalStyle::setTraceColorTankTrace6(this->_graph5);
            _arrayPlotContainerPointerGraph5 = _customPlot->graph(5)->data();
            break;
        default:
            break;
        }
    }
    else
    {
        if(traceExiste)
        {
            switch (traceNumber-1) {
            case 0:
                this->_customPlot->removeGraph(0);
                break;
            case 1:
                this->_customPlot->removeGraph(1);
                break;
            case 2:
                this->_customPlot->removeGraph(2);
                break;
            case 3:
                this->_customPlot->removeGraph(3);
                break;
            case 4:
                this->_customPlot->removeGraph(4);
                break;
            case 5:
                this->_customPlot->removeGraph(5);
                break;
            default:
                break;
            }
            this->_nbOfTrace--;
        }
    }
}

void CustomPlotItem::setupTraceWatherStation()
{
    
    //    _customPlot->addGraph();
    //    _customPlot->addGraph();
    //    _customPlot->addGraph();
    
    //    _graph0 = _customPlot->graph(0);    //humidity
    //    _graph1 = _customPlot->graph(1);    //temperature
    //    _graph2 = _customPlot->graph(2);    //pressure
    
    _graph0->setName("Humidity");
    _graph1->setName("Temperature");
    _graph2->setName("Pressure x 10");
    
    _line = new QCPItemStraightLine(_customPlot);
    
    GlobalStyle::setTraceColorTemperaturePlot(this->_graph1);
    GlobalStyle::setTraceColorHumidityPlot(this->_graph0);
    GlobalStyle::setTraceColorPressurePlot(this->_graph2);
    
    
    this->_itBegin = _arrayPlotContainerPointerGraph0->constBegin();
    this->_itEnd = _arrayPlotContainerPointerGraph0->constEnd();
}

void CustomPlotItem::setupTraceAnalogTrace(quint8 nbOfTrace)
{
    
    
    _line = new QCPItemStraightLine(_customPlot);
    
    this->_itBegin = _arrayPlotContainerPointerGraph0->constBegin();
    this->_itEnd = _arrayPlotContainerPointerGraph0->constEnd();
}

void CustomPlotItem::setupTraceStatisticTrace(GlobalEnumerate::E_PlotStyle plotstyle)
{
    
    switch ((GlobalEnumerate::E_PlotStyle)plotstyle)
    {
    case GlobalEnumerate::PLOT_STYLE_STATISTIC_TRACE:
        _graph0->setName("Humidity");
        _graph1->setName("Temperature");
        _graph2->setName("Pressure x 10");
        
        _line = new QCPItemStraightLine(_customPlot);
        
        GlobalStyle::setTraceColorTemperatureMinPlot(this->_graph0, this->_graph1);
        GlobalStyle::setTraceColorTemperaturePlot(this->_graph1);
        GlobalStyle::setTraceColorHumidityMinPlot(this->_graph2, this->_graph3);
        GlobalStyle::setTraceColorHumidityMaxPlot(this->_graph3);
        GlobalStyle::setTraceColorPressureMinPlot(this->_graph4, this->_graph5);
        GlobalStyle::setTraceColorPressurePlot(this->_graph5);
        break;
    case GlobalEnumerate::PLOT_STYLE_TEMPERATURE_TRACE:
        GlobalStyle::setTraceColorTemperatureMinPlot(this->_graph0, this->_graph1);
        GlobalStyle::setTraceColorTemperaturePlot(this->_graph1);
        break;
    case GlobalEnumerate::PLOT_STYLE_HUMIDITY_TRACE:
        GlobalStyle::setTraceColorHumidityMinPlot(this->_graph0, this->_graph1);
        GlobalStyle::setTraceColorHumidityMaxPlot(this->_graph1);
        break;
    case GlobalEnumerate::PLOT_STYLE_PRESSURE_TRACE:
        GlobalStyle::setTraceColorPressureMinPlot(this->_graph0, this->_graph1);
        GlobalStyle::setTraceColorPressurePlot(this->_graph1);
        break;
    case GlobalEnumerate::PLOT_STYLE_CONSO_TRACE:
        GlobalStyle::setTraceColorConsoMinPlot(this->_graph0, this->_graph1);
        GlobalStyle::setTraceColorConsoPlot(this->_graph1);
        break;    default:
        break;
    }
    
    
    this->_itBegin = _arrayPlotContainerPointerGraph0->constBegin();
    this->_itEnd = _arrayPlotContainerPointerGraph0->constEnd();
}
