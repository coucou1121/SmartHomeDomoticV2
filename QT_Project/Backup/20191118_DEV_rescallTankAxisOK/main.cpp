#include <main.h>

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    QFile outFile(GlobaleStaticValue::logFile);

    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("[%1] ").arg(dt);

    switch (type)
    {
    case QtDebugMsg:
        txt += QString("{Debug} \t\t %1").arg(msg);
        break;
    case QtWarningMsg:
        txt += QString("{Warning} \t %1").arg(msg);
        break;
    case QtCriticalMsg:
        txt += QString("{Critical} \t %1").arg(msg);
        break;
    case QtFatalMsg:
        txt += QString("{Fatal} \t\t %1").arg(msg);
        abort();
        break;
    }

    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream textStream(&outFile);
    textStream << txt << endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    //qInstallMessageHandler(customMessageHandler);

    QApplication  app(argc, argv);

    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Home domotic");

    QQuickStyle::setStyle("Material");

    //Initialising of the global qRegisterMetaType and qmlRegisterType
    GlobalEnumerate::initCppToQmlClass();
    qmlRegisterType<Setting>("io.qt.Setting", 1, 0, "Setting");
    qmlRegisterType<CustomPlotItem>("io.qt.CustomPlotItem", 1, 0, "CustomPlotItem");

    //Creation of CPP windows Object for linked after to QML Windows in UI
    QObject *qobjectHomeViewer = nullptr;
    QObject *qobjectWarningSideBar = nullptr;
    QObject *qobjectSettingViewer = nullptr;
    QObject *qobjectStatisticViewer = nullptr;
    QObject *qobjectTankViewer = nullptr;
    QObject *qobjectBME280Display = nullptr;
    QObject *qobjectStastisticValueViewer = nullptr;

    //Creation of CPP plots Object for linked after to QML Plots in UI
    //tanks
    QObject *qobjectTank1 = nullptr;
    QObject *qobjectTank2 = nullptr;
    QObject *qobjectTank3 = nullptr;
    QObject *qobjectTank4 = nullptr;
    QObject *qobjectTank5 = nullptr;
    QObject *qobjectTank6 = nullptr;

    //plots
    QObject *qcustomPlotRoomData = nullptr;
    QObject *qcustomPlotTankData = nullptr;
    QObject *qcustomPlotStatisticsTemperature = nullptr;
    QObject *qcustomPlotStatisticsHumidity = nullptr;
    QObject *qcustomPlotStatisticsPressure = nullptr;
    QObject *qcustomPlotStatisticsConsomation = nullptr;

    //Link QML object to CPP Object
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //wait delay to be sure all qml are loaded
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }

    if (!engine.rootObjects().isEmpty())
    {
        //Linked CPP object windows to QML windows
        qobjectHomeViewer = engine.rootObjects().first()->findChild<QObject*>("homeViewer");
        qobjectWarningSideBar = engine.rootObjects().first()->findChild<QObject*>("warningDisplaySideBar");
        qobjectSettingViewer = engine.rootObjects().first()->findChild<QObject*>("settingViewer");
        qobjectStatisticViewer = engine.rootObjects().first()->findChild<QObject*>("statisticViewer");
        qobjectTankViewer = engine.rootObjects().first()->findChild<QObject*>("tankViewer");
        qobjectBME280Display = engine.rootObjects().first()->findChild<QObject*>("bME280");
        qobjectStastisticValueViewer = engine.rootObjects().first()->findChild<QObject*>("stastisticValueViewer");

        //Linked CPP object plot to QML plot
        qcustomPlotRoomData = engine.rootObjects().first()->findChild<QObject*>("qcustomPlotRoomData");
        qcustomPlotTankData = engine.rootObjects().first()->findChild<QObject*>("qcustomPlotTanksData");
        qcustomPlotStatisticsTemperature = engine.rootObjects().first()->findChild<QObject*>("qcustomPlotStatisticsTemperature");
        qcustomPlotStatisticsHumidity = engine.rootObjects().first()->findChild<QObject*>("qcustomPlotStatisticsHumidity");
        qcustomPlotStatisticsPressure = engine.rootObjects().first()->findChild<QObject*>("qcustomPlotStatisticsPressure");
        qcustomPlotStatisticsConsomation = engine.rootObjects().first()->findChild<QObject*>("qcustomPlotStatisticsConsomation");

        //set Style of the plots
        QMetaObject::invokeMethod(qcustomPlotRoomData, "setupStyleLiveWeatherStation");
        QMetaObject::invokeMethod(qcustomPlotTankData, "setupStyleLiveTanksData");
        QMetaObject::invokeMethod(qcustomPlotStatisticsTemperature, "setupStyleTemperatureTrace");
        QMetaObject::invokeMethod(qcustomPlotStatisticsHumidity, "setupStyleHumidityTrace");
        QMetaObject::invokeMethod(qcustomPlotStatisticsPressure, "setupStylePressureTrace");
        QMetaObject::invokeMethod(qcustomPlotStatisticsConsomation, "setupStyleConsomationTrace");



        //set QML tank object name
        QQmlProperty objectNameTank1(qobjectTankViewer, "tank1TankObjectName");
        QQmlProperty objectNameTank2(qobjectTankViewer, "tank2TankObjectName");
        QQmlProperty objectNameTank3(qobjectTankViewer, "tank3TankObjectName");
        QQmlProperty objectNameTank4(qobjectTankViewer, "tank4TankObjectName");
        QQmlProperty objectNameTank5(qobjectTankViewer, "tank5TankObjectName");
        QQmlProperty objectNameTank6(qobjectTankViewer, "tank6TankObjectName");
        objectNameTank1.write(GlobaleStaticValue::ObjectNameTank1);
        objectNameTank2.write(GlobaleStaticValue::ObjectNameTank2);
        objectNameTank3.write(GlobaleStaticValue::ObjectNameTank3);
        objectNameTank4.write(GlobaleStaticValue::ObjectNameTank4);
        objectNameTank5.write(GlobaleStaticValue::ObjectNameTank5);
        objectNameTank6.write(GlobaleStaticValue::ObjectNameTank6);

        //Linked CPP object tanks to QML tanks
        qobjectTank1 = engine.rootObjects().first()->findChild<QObject*>(GlobaleStaticValue::ObjectNameTank1);
        qobjectTank2 = engine.rootObjects().first()->findChild<QObject*>(GlobaleStaticValue::ObjectNameTank2);
        qobjectTank3 = engine.rootObjects().first()->findChild<QObject*>(GlobaleStaticValue::ObjectNameTank3);
        qobjectTank4 = engine.rootObjects().first()->findChild<QObject*>(GlobaleStaticValue::ObjectNameTank4);
        qobjectTank5 = engine.rootObjects().first()->findChild<QObject*>(GlobaleStaticValue::ObjectNameTank5);
        qobjectTank6 = engine.rootObjects().first()->findChild<QObject*>(GlobaleStaticValue::ObjectNameTank6);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << engine.rootObjects().isEmpty();
    }


    //Create thread *Object used for application living
    DataAnalyser *dataAnalyserObject = new DataAnalyser(qobjectStastisticValueViewer,
                                                        qobjectStatisticViewer,
                                                        qobjectSettingViewer,
                                                        qobjectHomeViewer,
                                                        qobjectBME280Display,
                                                        qcustomPlotRoomData,
                                                        qcustomPlotTankData);

    DataManager *dataManager = new DataManager("datamanager",
                                               //                                               1000,
                                               qobjectStatisticViewer,
                                               qobjectBME280Display,
                                               //                                               qobjectStastisticValueViewer,
                                               dataAnalyserObject); //3600

    ErrorManager *errorManager = new ErrorManager(nullptr, qobjectWarningSideBar);

    //Create *Object for the Hardware sensor and device
    BME280Item *bme280 = new BME280Item(BME280_I2C_ADDR_PRIM,
                                        qobjectBME280Display,
                                        qcustomPlotRoomData,
                                        qobjectHomeViewer);

    ADS1115Item *ads1115_1 = new ADS1115Item(GlobaleStaticValue::ADS1115_1Title,
                                             ADS1115_DEFAULT_ADDRESS,
//                                             nullptr,
                                             qcustomPlotTankData,
                                             nullptr,
                                             //                                             _thread_ADS115_1_manager,
                                             qobjectHomeViewer);

    ADS1115Item *ads1115_2 = new ADS1115Item(GlobaleStaticValue::ADS1115_2Title,
                                             ADS1115_VDD_ADDRESS,
//                                             nullptr,
                                             qcustomPlotTankData,
                                             nullptr,
                                             //                                             _thread_ADS115_2_manager,
                                             qobjectHomeViewer);

    //Create setting *Object  for application setting management
    Setting *setting = new Setting(nullptr,
                                   qobjectHomeViewer,
                                   qobjectTankViewer,
                                   qobjectSettingViewer,
                                   qobjectStatisticViewer,
                                   dataAnalyserObject,
                                   bme280,
                                   ads1115_1,
                                   ads1115_2,
                                   dataManager);


    dataManager->setADS1115_1(ads1115_1);

    dataManager->setBME280(bme280);

    //From tanks to the error manager
    QObject::connect(qobjectTank1, SIGNAL(sendWarningLowLevel(QString,QString,int,bool)),
                     errorManager, SLOT(_reveived_Error(QString,QString,int,bool)));
    QObject::connect(qobjectTank2, SIGNAL(sendWarningLowLevel(QString,QString,int,bool)),
                     errorManager, SLOT(_reveived_Error(QString,QString,int,bool)));
    QObject::connect(qobjectTank3, SIGNAL(sendWarningLowLevel(QString,QString,int,bool)),
                     errorManager, SLOT(_reveived_Error(QString,QString,int,bool)));
    QObject::connect(qobjectTank4, SIGNAL(sendWarningLowLevel(QString,QString,int,bool)),
                     errorManager, SLOT(_reveived_Error(QString,QString,int,bool)));
    QObject::connect(qobjectTank5, SIGNAL(sendWarningLowLevel(QString,QString,int,bool)),
                     errorManager, SLOT(_reveived_Error(QString,QString,int,bool)));
    QObject::connect(qobjectTank6, SIGNAL(sendWarningLowLevel(QString,QString,int,bool)),
                     errorManager, SLOT(_reveived_Error(QString,QString,int,bool)));

    //From tanks to setting
    //volume max
    QObject::connect(qobjectTank1, SIGNAL(sendTankVolumeMaxChanged(QString, int)),
                     setting, SLOT(receivedTankVolumeMaxChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank2, SIGNAL(sendTankVolumeMaxChanged(QString, int)),
                     setting, SLOT(receivedTankVolumeMaxChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank3, SIGNAL(sendTankVolumeMaxChanged(QString, int)),
                     setting, SLOT(receivedTankVolumeMaxChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank4, SIGNAL(sendTankVolumeMaxChanged(QString, int)),
                     setting, SLOT(receivedTankVolumeMaxChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank5, SIGNAL(sendTankVolumeMaxChanged(QString, int)),
                     setting, SLOT(receivedTankVolumeMaxChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank6, SIGNAL(sendTankVolumeMaxChanged(QString, int)),
                     setting, SLOT(receivedTankVolumeMaxChanged(QString, int)), Qt::UniqueConnection);
    //warning low level value
    QObject::connect(qobjectTank1, SIGNAL(sendTankWarningLowLevelChanged(QString, int)),
                     setting, SLOT(receivedTankWarningLowLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank2, SIGNAL(sendTankWarningLowLevelChanged(QString, int)),
                     setting, SLOT(receivedTankWarningLowLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank3, SIGNAL(sendTankWarningLowLevelChanged(QString, int)),
                     setting, SLOT(receivedTankWarningLowLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank4, SIGNAL(sendTankWarningLowLevelChanged(QString, int)),
                     setting, SLOT(receivedTankWarningLowLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank5, SIGNAL(sendTankWarningLowLevelChanged(QString, int)),
                     setting, SLOT(receivedTankWarningLowLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank6, SIGNAL(sendTankWarningLowLevelChanged(QString, int)),
                     setting, SLOT(receivedTankWarningLowLevelChanged(QString, int)), Qt::UniqueConnection);

    //liquide fillup
    QObject::connect(qobjectTank1, SIGNAL(sendTankLiquideFillupChanged(QString, int)),
                     setting, SLOT(receivedTankLiquideFillupChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank2, SIGNAL(sendTankLiquideFillupChanged(QString, int)),
                     setting, SLOT(receivedTankLiquideFillupChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank3, SIGNAL(sendTankLiquideFillupChanged(QString, int)),
                     setting, SLOT(receivedTankLiquideFillupChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank4, SIGNAL(sendTankLiquideFillupChanged(QString, int)),
                     setting, SLOT(receivedTankLiquideFillupChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank5, SIGNAL(sendTankLiquideFillupChanged(QString, int)),
                     setting, SLOT(receivedTankLiquideFillupChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank6, SIGNAL(sendTankLiquideFillupChanged(QString, int)),
                     setting, SLOT(receivedTankLiquideFillupChanged(QString, int)), Qt::UniqueConnection);

    //height volume max value in milimeter
    QObject::connect(qobjectTank1, SIGNAL(sendTankHeightMaxLevelChanged(QString, int)),
                     setting, SLOT(receivedTankHeightMaxLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank2, SIGNAL(sendTankHeightMaxLevelChanged(QString, int)),
                     setting, SLOT(receivedTankHeightMaxLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank3, SIGNAL(sendTankHeightMaxLevelChanged(QString, int)),
                     setting, SLOT(receivedTankHeightMaxLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank4, SIGNAL(sendTankHeightMaxLevelChanged(QString, int)),
                     setting, SLOT(receivedTankHeightMaxLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank5, SIGNAL(sendTankHeightMaxLevelChanged(QString, int)),
                     setting, SLOT(receivedTankHeightMaxLevelChanged(QString, int)), Qt::UniqueConnection);
    QObject::connect(qobjectTank6, SIGNAL(sendTankHeightMaxLevelChanged(QString, int)),
                     setting, SLOT(receivedTankHeightMaxLevelChanged(QString, int)), Qt::UniqueConnection);

    //tank in warning
    QObject::connect(qobjectTank1, SIGNAL(sendWarningLowLevelToSetting(QString, bool)),
                     setting, SLOT(receivedWarningLowLevelFromTank(QString, bool)), Qt::UniqueConnection);
    QObject::connect(qobjectTank2, SIGNAL(sendWarningLowLevelToSetting(QString, bool)),
                     setting, SLOT(receivedWarningLowLevelFromTank(QString, bool)), Qt::UniqueConnection);
    QObject::connect(qobjectTank3, SIGNAL(sendWarningLowLevelToSetting(QString, bool)),
                     setting, SLOT(receivedWarningLowLevelFromTank(QString, bool)), Qt::UniqueConnection);
    QObject::connect(qobjectTank4, SIGNAL(sendWarningLowLevelToSetting(QString, bool)),
                     setting, SLOT(receivedWarningLowLevelFromTank(QString, bool)), Qt::UniqueConnection);
    QObject::connect(qobjectTank5, SIGNAL(sendWarningLowLevelToSetting(QString, bool)),
                     setting, SLOT(receivedWarningLowLevelFromTank(QString, bool)), Qt::UniqueConnection);
    QObject::connect(qobjectTank6, SIGNAL(sendWarningLowLevelToSetting(QString, bool)),
                     setting, SLOT(receivedWarningLowLevelFromTank(QString, bool)), Qt::UniqueConnection);

    //From setting viewer to close this application
    QObject::connect(qobjectSettingViewer, SIGNAL(sendCloseApplication()), qApp, SLOT(quit()));

    //From setting viewer to setting
    QObject::connect(qobjectSettingViewer, SIGNAL(sendTankIsVisible(int, bool)),
                     setting, SLOT(receivedTankIsVisible(int, bool)));

    QObject::connect(qobjectSettingViewer, SIGNAL(sendTankTitleChanged(int, QString)),
                     setting, SLOT(receivedTankTitleChanged(int, QString)), Qt::UniqueConnection);

    QObject::connect(qobjectSettingViewer, SIGNAL(sendGraphReccordTimesChanged(int)),
                     setting, SLOT(receivedGraphReccordTimesChanged(int)), Qt::UniqueConnection);

    QObject::connect(qobjectSettingViewer, SIGNAL(sendOnCalibrationMode(bool)),
                     setting, SLOT(receivedOnCalibrationMode(bool)), Qt::UniqueConnection);

    QObject::connect(qobjectSettingViewer, SIGNAL(sendTankOffsetPressureChanged(int,int)),
                     setting, SLOT(receivedTankOffsetPressureChanged(int,int)), Qt::UniqueConnection);

    QObject::connect(qobjectSettingViewer, SIGNAL(sendVolumeATMChanged()),
                     setting, SLOT(receivedVolumeATMChanged()), Qt::UniqueConnection);

    //From ADS115 to setting
    //Volume PID coef for tank volume calculation
    QObject::connect(qobjectSettingViewer, SIGNAL(sendVolumePIDChanged(int)),
                     setting, SLOT(receivedVolumePIDChanged(int)));


    //actual tank volume
    QObject::connect(dataAnalyserObject, SIGNAL(sendTankActualVolumeChanged(int, int)),
                     setting, SLOT(receivedTankActualVolumeChanged(int, int)));


    //From StatisticView to Datamanager for replot a saved data in statistic tab
    QObject::connect(qobjectStatisticViewer, SIGNAL(sendReplotWithSavedData(int, int, int)),
                     dataAnalyserObject, SLOT(ReceivedreplotWithSavedData(int, int, int)), Qt::UniqueConnection);

    qDebug() << "all signals connected";

    //Connection CPP Signal to QML Slot
    //    QObject::connect(&warningReceiver, SIGNAL(sendErrorMsgToDisplay(QString)),
    //                     qobjectWarningDisplay, SLOT(warningReceivedToDisplay(string)), Qt::UniqueConnection);

    //    QObject::connect(bme280, SIGNAL(sendTextToDisplay(QString)),
    //                     qobjectHomeViewer, SLOT(addTextToDisplay(string)), Qt::UniqueConnection);

    //    QVariant returnedValue;
    //   QVariant msg = "Hello from C++";
    //    QMetaObject::invokeMethod(qobjectWarningDisplay, "myQmlFunction",
    //            Q_RETURN_ARG(QVariant, returnedValue),
    //            Q_ARG(QVariant, msg));

    //   qDebug() << "QML function returned:" << returnedValue.toString();
    //read property in base qml file

    //    QQmlEngine engineItem;
    //    QQmlComponent component(&engineItem, "qrc:/TankViewer.qml");
    //    QObject *object = component.create();
    //    QQmlProperty p(object, "tank1TankObjectName");
    //    qDebug() << "Property value:" << QQmlProperty::read(object,"tank1TankObjectName").toString();
    //    qDebug() << "Property value:" << p.read();
    //    p.write("Tank1bis");
    //    qDebug() << "Property value:" << p.read();

    //       QQmlProperty::write(object,"tank1", ).toString();

    //plot device
    //viewer.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    //    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    //    viewer.setColor(QColor("#404040"));
    //qobjectPlotView->rootContext()->setContextProperty("dataSource", &dataSource);
    //   viewer.rootContext()->setContextProperty("dataSource", &dataSource);

    //Start Thread for application living
    dataManager->start();
    ads1115_1->start();
    bme280->start();

    do
    {
        //wait delay until all threads are running
        QTime dieTime = QTime::currentTime().addMSecs(200);
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
        qDebug() << "Wait all threads are running";

    }
    while(!dataManager->isRunning() && !ads1115_1->isRunning() && !bme280->isRunning());

    qDebug() << "all threads are running!!!";

    return app.exec();
}


