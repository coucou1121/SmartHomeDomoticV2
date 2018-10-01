#include <main.h>

int main(int argc, char *argv[])
{
#if true
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
    qmlRegisterType<QlLinePlotItem>("io.qt.QlLinePlotItem", 1, 0, "QlLinePlotItem");
    //   qmlRegisterType<GlobalStyle>("io.qt.GlobalStyle", 1, 0, "GlobalStyle");


    QQmlApplicationEngine engine;

    QQuickStyle::setStyle("Material");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    //Receiving Signals from QML to CPP
    //    To find QML child item using QObject::findChild(), it should have a name. So it should be like :
    //    Item {
    //        id: button
    //        objectName: "name"
    //        ...
    //    }
    //    Now you can access it by :
    //    QObject *childObj = obj->findChild<QObject *>("name");
    //
    //    connect(childObj, SIGNAL(qmlMsg(QString)), this, SLOT(printData(QString)));
    //
    //https://stackoverflow.com/questions/25132844/how-to-connect-a-qml-child-component-signal-to-a-c-slot


    //link Object from QML to CPP signal
    //Search by objectName

    //CPP object windows creation from existing QML Object in UI
    QObject *qobjectWarningSideBar = engine.rootObjects().first()->findChild<QObject*>("warningDisplaySideBar");
    QObject *qobjectSettingViewer = engine.rootObjects().first()->findChild<QObject*>("settingViewer");
    QObject *qobjectTankViewer = engine.rootObjects().first()->findChild<QObject*>("tankViewer");
    QObject *qobjectBME280 = engine.rootObjects().first()->findChild<QObject*>("bME280");
    //timer
    QObject *qobjectTimerTemperature = engine.rootObjects().first()->findChild<QObject*>("timerTemperature");
    qobjectTimerTemperature->setProperty("refreshTimer", 5000);
    QObject *qobjectRoomDataTimer = engine.rootObjects().first()->findChild<QObject*>("roomDataTimer");
    qobjectRoomDataTimer->setProperty("refreshTimer", 100);
    //plot
    QObject *qobjectcustomPlotRoomData = engine.rootObjects().first()->findChild<QObject*>("customPlotRoomData");
//    QObject *qobjectCustomPlotHumidity = engine.rootObjects().first()->findChild<QObject*>("customPlotHumidity");
//    QObject *qobjectCustomPlotPressure = engine.rootObjects().first()->findChild<QObject*>("customPlotPressure");

    //CPP object creation from existing QML Object in UI
    ErrorManager *errorManager = new ErrorManager(nullptr, qobjectWarningSideBar);
    Setting *setting = new Setting(nullptr, qobjectTankViewer, qobjectSettingViewer);
    CustomPlotItem *plotTemperature = new CustomPlotItem(nullptr, qobjectcustomPlotRoomData);
//    CustomPlotItem *plotHumidity = new CustomPlotItem(nullptr, qobjectCustomPlotHumidity);
//    CustomPlotItem *plotPressure = new CustomPlotItem(nullptr, qobjectCustomPlotPressure);
    BME280 *bme280 = new BME280(nullptr,qobjectBME280, qobjectcustomPlotRoomData);


    //plots refresh
    QObject::connect(qobjectTimerTemperature, SIGNAL(sendRefreshDataTemperaturePlot()),
                     plotTemperature, SLOT(_recievedRefreshDataTemperaturePlot()));
//    QObject::connect(qobjectTimerTemperature, SIGNAL(sendRefreshDataTemperaturePlot()),
//                     bme280, SLOT(addValueInroomDataPlot()));
    QObject::connect(qobjectRoomDataTimer, SIGNAL(sendRefreshRoomData()),
                     bme280, SLOT(addValueInroomDataPlot()));
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


    QObject::connect(qobjectSettingViewer, SIGNAL(sendTankIsVisible(int, bool)),
                     setting, SLOT(receivedTankIsVisible(int, bool)));

    //From setting viewer to tank
    QObject::connect(qobjectSettingViewer, SIGNAL(sendTankTitleChanged(int, QString)),
                     setting, SLOT(receivedTankTitleChanged(int, QString)), Qt::UniqueConnection);

    //Connection CPP Signal to QML Slot
    //    QObject::connect(&warningReceiver, SIGNAL(sendErrorMsgToDisplay(QString)),
    //                     qobjectWarningDisplay, SLOT(warningReceivedToDisplay(string)), Qt::UniqueConnection);


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

#endif
#if false
    QApplication a(argc, argv);

    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");

    QQuickView view(QUrl("qrc:/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.resize(500, 500);
    view.show();

    return a.exec();
#endif
}
