#include <main.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication  app(argc, argv);

    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Home domotic");
    /**
      * \fn init();
      * \brief initialise the global enumate and extern class
      */
    GlobalEnumerate::initClass();
    QMap<int, QString> tankObjectNameArray(GlobaleStaticValue::initTankObjectName());
    // qRegisterMetaType<GlobalEnumatedAndExtern::eTankLiquidInside>("GlobalEnumatedAndExtern::eTankLiquidInside");
    //  qmlRegisterType<GlobalEnumatedAndExtern>("io.qt.GlobalEnumatedAndExtern", 1, 0, "GlobalEnumatedAndExtern");

    //Warning manager
    //WarningReceiver warningReceiver(qobjectWarningDisplay);

    qmlRegisterType<Setting>("io.qt.Setting", 1, 0, "Setting");
    qmlRegisterType<CustomPlotItem>("io.qt.CustomPlotItem", 1, 0, "CustomPlotItem");
    //   qmlRegisterType<GlobalStyle>("io.qt.GlobalStyle", 1, 0, "GlobalStyle");


    QQmlApplicationEngine engine;

    QQuickStyle::setStyle("Material");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



    //thread to start the initiasitation, check the device register and get new value if good
    timerthread *_thread_ADS115_1_manager = new timerthread(false, "thread_ADS115_1_manager",1000);
    timerthread *_thread_ADS115_2_manager = new timerthread(false, "thread_ADS115_2_manager",1000);


    //CPP object windows creation from existing QML Object in UI
    QObject *qobjectHomeViewer = engine.rootObjects().first()->findChild<QObject*>("homeViewer");
    QObject *qobjectWarningSideBar = engine.rootObjects().first()->findChild<QObject*>("warningDisplaySideBar");
    QObject *qobjectSettingViewer = engine.rootObjects().first()->findChild<QObject*>("settingViewer");
    QObject *qobjectStatisticViewer = engine.rootObjects().first()->findChild<QObject*>("statisticViewer");
    QObject *qobjectTankViewer = engine.rootObjects().first()->findChild<QObject*>("tankViewer");
    QObject *qobjectBME280Display = engine.rootObjects().first()->findChild<QObject*>("bME280");
    QObject *qobjectStastisticValueViewer = engine.rootObjects().first()->findChild<QObject*>("stastisticValueViewer");

    //data manager thread
    DataAnalyser *dataAnalyserObject = new DataAnalyser(60,
                                                        qobjectStastisticValueViewer,
                                                        qobjectStatisticViewer);

    DataManager *dataManager = new DataManager(qobjectStatisticViewer,
                                               qobjectBME280Display,
                                               "datamanager",
                                               60,
                                               1000,
                                               qobjectStastisticValueViewer,
                                               dataAnalyserObject); //3600

    //plot
    QObject *qobjectcustomPlotRoomData = engine.rootObjects().first()->findChild<QObject*>("customPlotRoomData");
    QObject *qobjectcustomPlotTankData = engine.rootObjects().first()->findChild<QObject*>("customPlotTanksData");
    //    QObject *qobjectCustomPlotHumidity = engine.rootObjects().first()->findChild<QObject*>("customPlotHumidity");
    //    QObject *qobjectCustomPlotPressure = engine.rootObjects().first()->findChild<QObject*>("customPlotPressure");
    //startup display text

    //    QMetaObject::invokeMethod(qobjectHomeViewer, "addTextToDisplay",
    //                              Q_ARG(QVariant, GlobaleStaticValue::welcomeText));

    //CPP object creation from existing QML Object in UI
    ErrorManager *errorManager = new ErrorManager(nullptr, qobjectWarningSideBar);
    //    CustomPlotItem *plotWeatherStation = new CustomPlotItem(nullptr, qobjectcustomPlotRoomData);
    //    CustomPlotItem *customPlotTanks = qobjectcustomPlotTankData;
    //    CustomPlotItem *customPlotTanks = engine.rootObjects().first()->findChild<CustomPlotItem*>("customPlotTanksData");
    //    CustomPlotItem *plotPressure = new CustomPlotItem(nullptr, qobjectCustomPlotPressure);
    BME280Item *bme280 = new BME280Item(BME280_I2C_ADDR_PRIM,
                                        qobjectBME280Display,
                                        qobjectcustomPlotRoomData,
                                        qobjectHomeViewer);

    ADS1115Item *ads1115_1 = new ADS1115Item(GlobaleStaticValue::ADS1115_1Title,
                                             ADS1115_DEFAULT_ADDRESS,
                                             nullptr,
                                             qobjectcustomPlotTankData,
                                             _thread_ADS115_1_manager,
                                             qobjectHomeViewer);

    ADS1115Item *ads1115_2 = new ADS1115Item(GlobaleStaticValue::ADS1115_2Title,
                                             ADS1115_VDD_ADDRESS,
                                             nullptr,
                                             qobjectcustomPlotTankData,
                                             _thread_ADS115_2_manager,
                                             qobjectHomeViewer);

    Setting *setting = new Setting(nullptr,
                                   qobjectHomeViewer,
                                   qobjectTankViewer,
                                   qobjectSettingViewer,
                                   qobjectStatisticViewer,
                                   bme280,
                                   ads1115_1,
                                   ads1115_2,
                                   dataManager);

    //    ads1115_1->moveToThread(_thread_ADS115_1_manager);
    //    ads1115_2->moveToThread(_thread_ADS115_2_manager);
    //    bme280->moveToThread(_thread_BME280_manager);

    //_thread_ADS115_1_manager->start();

    //    _thread_ADS115_2_manager->start();
    ads1115_1->start();
    bme280->start();
    //    _thread_BME280_manager->start();

    dataManager->setADS1115_1(ads1115_1);
    dataManager->setBME280(bme280);
    dataManager->start();

    //thread signal manager use to initialise the device.
    //    QObject::connect(_thread_ADS115_1_manager, SIGNAL(delayFinished()),
    //                     ads1115_1, SLOT(receivedAddNewDataFromThread()));
    //    QObject::connect(_thread_ADS115_1_manager, SIGNAL(delayFinished()),
    //                     ads1115_1, SLOT(addValueInRoomDataPlot()));
    //    QObject::connect(_thread_ADS115_1_manager, SIGNAL(delayFinished()),
    //                     ads1115_1, SLOT(addValueInRoomDataPlot()));

    //plots refresh
    //        QObject::connect(qobjectTimerPlotRefreching, SIGNAL(sendRefreshDataTemperaturePlot()),
    //                         plotWeatherStation, SLOT(_recievedRefreshDataTemperaturePlot()));
    //    QObject::connect(qobjectTimerPlotRefreching, SIGNAL(sendRefreshDataTemperaturePlot()),
    //                     bme280, SLOT(addValueInroomDataPlot()));

    //    QObject::connect(_TankDataUpdate, SIGNAL(delayFinished()),
    //                     ads1115_1, SLOT(receivedAddValueInTankDataPlot()));
    //    QObject::connect(qobjectTimerTemperature, SIGNAL(sendRefreshDataHumidity()),
    //                     plotHumidity, SLOT(_recievedRefreshDataTemperaturePlot()));
    //    QObject::connect(qobjectTimerTemperature, SIGNAL(sendRefreshDataPressure()),
    //                     plotPressure, SLOT(_recievedRefreshDataTemperaturePlot()));


    //create tank CPP object from qml design
    QObject *qobjectTank1 = engine.rootObjects().first()->findChild<QObject*>(tankObjectNameArray[GlobalEnumerate::TANK1]);
    QObject *qobjectTank2 = engine.rootObjects().first()->findChild<QObject*>(tankObjectNameArray[GlobalEnumerate::TANK2]);
    QObject *qobjectTank3 = engine.rootObjects().first()->findChild<QObject*>(tankObjectNameArray[GlobalEnumerate::TANK3]);
    QObject *qobjectTank4 = engine.rootObjects().first()->findChild<QObject*>(tankObjectNameArray[GlobalEnumerate::TANK4]);
    QObject *qobjectTank5 = engine.rootObjects().first()->findChild<QObject*>(tankObjectNameArray[GlobalEnumerate::TANK5]);
    QObject *qobjectTank6 = engine.rootObjects().first()->findChild<QObject*>(tankObjectNameArray[GlobalEnumerate::TANK6]);

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

    //From ADS115 to setting
    //actual tank volume
    QObject::connect(ads1115_1, SIGNAL(sendTankActualVolumeChanged(int, int)),
                     setting, SLOT(receivedTankActualVolumeChanged(int, int)));


    //From StatisticView to Datamanager for replot a saved data in statistic tab
    QObject::connect(qobjectStatisticViewer, SIGNAL(sendReplotWithSavedData(int, int, int)),
                     dataAnalyserObject, SLOT(ReceivedreplotWithSavedData(int, int, int)), Qt::UniqueConnection);

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
    //    QQmlComponent component(&engineItem, "qrc:/Tank.qml");
    //    QObject *object = component.create();
    //   qDebug() << "Property value:" << QQmlProperty::read(object,"tankVolumeAcutal").toInt();

    //plot device
    //viewer.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    //    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    //    viewer.setColor(QColor("#404040"));
    //qobjectPlotView->rootContext()->setContextProperty("dataSource", &dataSource);
    //   viewer.rootContext()->setContextProperty("dataSource", &dataSource);


    return app.exec();
}


