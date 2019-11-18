#include <ADS1115/ads1115item.h>


ADS1115Item::ADS1115Item(QString deviceName,
                         quint8 deviceI2CAdress,
//                         QObject *ADS1115Display,
                         QObject *tanksDataPlot,
                         timerthread *I2CThread,
                         QObject *homeViewer):
    _tanksDataPlot(tanksDataPlot),
    _homeViewer(homeViewer),
    _I2CThread(I2CThread),
    _deviceName(deviceName),
    _deviceI2CAdress(deviceI2CAdress),
    _fd(0),
    _ads1115(new ADS1115(_deviceI2CAdress)),
    _sleepingDelay(400),
    _timeInMilisecond(0),
    _memotimeInMilisecond(0),
//    _PIDVolumeCoef(1),
    _dataFrame(new DataFrame()),
    _ads_rate(RATE_64), //RATE_64
    _deviceIsReady(false),
    _onReadingData(true),
    _startToReadOnData(false),
    _onCalibration(false),
    _filterList0_IsFull(false),
    _filterList1_IsFull(false),
    _filterList2_IsFull(true),
    _filterList3_IsFull(true),
    _chan0_used(false),
    _chan1_used(false),
    _chan2_used(false),
    _chan3_used(false),
//    _offsetChan0InPuls(0),
//    _offsetChan1InPuls(0),
//    _chan0HighMaxValueInPuls(26000),
//    _chan1HighMaxValueInPuls(26000),
//    _tankIDchan0(0),
//    _tankIDchan1(0),
//    _tankIDchan2(0),
//    _tankIDchan3(0),
//    _tankChan0VolumeMax(0),
//    _tankChan1VolumeMax(0),
//    _tankChan2VolumeMax(0),
//    _tankChan3VolumeMax(0),
//    _tankChan0VolumeMaxHeightInMilimeter(0),
//    _tankChan1VolumeMaxHeightInMilimeter(0),
//    _tankChan2VolumeMaxHeightInMilimeter(0),
//    _tankChan3VolumeMaxHeightInMilimeter(0),
//    _tankChan0LiquideInside(GlobalEnumerate::WATER),
//    _tankChan1LiquideInside(GlobalEnumerate::WATER),
//    _tankChan2LiquideInside(GlobalEnumerate::WATER),
//    _tankChan3LiquideInside(GlobalEnumerate::WATER),
    _chan0(0),
    _chan1(0),
    _chan2(0),
    _chan3(0),
    _offsetPressurChan0(0),
    _offsetPressurChan1(0),
    _offsetPressurChan2(0),
    _offsetPressurChan3(0),
    _stateMachine(GlobalEnumerate::STATE_NOT_FOUNDED)
{
    moveToThread(this);
}

//adsRate_t ADS1115Item::ads_rate() const
//{
//    return _ads_rate;
//}

//void ADS1115Item::setAds_rate(const adsRate_t &ads_rate)
//{
//    _ads_rate = ads_rate;
//}

bool ADS1115Item::deviceIsReady() const
{
    return _deviceIsReady;
}

//void ADS1115Item::setTankChan0VolumeMax(const quint16 &tankChan0VolumeMax)
//{
//    _tankChan0VolumeMax = tankChan0VolumeMax;
//}

//void ADS1115Item::setTankChan1VolumeMax(const quint16 &tankChan1VolumeMax)
//{
//    _tankChan1VolumeMax = tankChan1VolumeMax;
//}

//void ADS1115Item::setTankChan2VolumeMax(const quint16 &tankChan2VolumeMax)
//{
//    _tankChan2VolumeMax = tankChan2VolumeMax;
//}

//void ADS1115Item::setTankChan3VolumeMax(const quint16 &tankChan3VolumeMax)
//{
//    _tankChan3VolumeMax = tankChan3VolumeMax;
//}

//void ADS1115Item::setTankChan0LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan0LiquideInside)
//{
//    _tankChan0LiquideInside = tankChan0LiquideInside;
//}

//void ADS1115Item::setTankChan1LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan1LiquideInside)
//{
//    _tankChan1LiquideInside = tankChan1LiquideInside;
//}

//void ADS1115Item::setTankChan2LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan2LiquideInside)
//{
//    _tankChan2LiquideInside = tankChan2LiquideInside;
//}

//void ADS1115Item::setTankChan3LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan3LiquideInside)
//{
//    _tankChan3LiquideInside = tankChan3LiquideInside;
//}

//void ADS1115Item::setTankIDchan0(const quint8 &tankIDchan0)
//{
//    _tankIDchan0 = tankIDchan0;
//}

//void ADS1115Item::setTankIDchan1(const quint8 &tankIDchan1)
//{
//    _tankIDchan1 = tankIDchan1;
//}

//void ADS1115Item::setTankIDchan2(const quint8 &tankIDchan2)
//{
//    _tankIDchan2 = tankIDchan2;
//}

//void ADS1115Item::setTankIDchan3(const quint8 &tankIDchan3)
//{
//    _tankIDchan3 = tankIDchan3;
//}

//void ADS1115Item::setTankChan0VolumeMaxHeightInMilimeter(const quint16 &tankChan0VolumeMaxHeightInMilimeter)
//{
//    _tankChan0VolumeMaxHeightInMilimeter = tankChan0VolumeMaxHeightInMilimeter;
//}

//void ADS1115Item::setTankChan1VolumeMaxHeightInMilimeter(const quint16 &tankChan1VolumeMaxHeightInMilimeter)
//{
//    _tankChan1VolumeMaxHeightInMilimeter = tankChan1VolumeMaxHeightInMilimeter;
//}

//void ADS1115Item::setTankChan2VolumeMaxHeightInMilimeter(const quint16 &tankChan2VolumeMaxHeightInMilimeter)
//{
//    _tankChan2VolumeMaxHeightInMilimeter = tankChan2VolumeMaxHeightInMilimeter;
//}

//void ADS1115Item::setTankChan3VolumeMaxHeightInMilimeter(const quint16 &tankChan3VolumeMaxHeightInMilimeter)
//{
//    _tankChan3VolumeMaxHeightInMilimeter = tankChan3VolumeMaxHeightInMilimeter;
//}

bool ADS1115Item::onReadingData() const
{
    return _onReadingData;
}

void ADS1115Item::run()
{

    qint64 sleepingDelay = 0;

    while(true)
    {
        this->_memotimeInMilisecond = QDateTime::currentMSecsSinceEpoch();

        //        qDebug() << Q_FUNC_INFO;
//        while(!this->_deviceIsReady)
//        {

//            this->_initDevice();
//            this->_waitDelayMili(1000);
//        }

//        _goToNextState();
        this->_checkStateOfDevice();

        //        if(this->_startToReadOnData && this->_deviceIsReady)
        //        {
        //            this->_startToReadOnData = false;
        //insert data in plot

//        if(this->_filterList0_IsFull && this->_filterList1_IsFull &&
//                this->_filterList2_IsFull && this->_filterList3_IsFull)
//        {
//            //                QMetaObject::invokeMethod(this->_tanksDataPlot, "addYValue",
//            //                                          Q_ARG(QVariant, this->_dataFrame->ADS115_1_chan0()),
//            //                                          Q_ARG(QVariant, this->_dataFrame->ADS115_1_chan1()),
//            //                                          Q_ARG(QVariant, this->_dataFrame->ADS115_1_chan2()),
//            //                                          Q_ARG(QVariant, this->_dataFrame->ADS115_1_chan3())
//            //                                          );
//        }

//        sendTankActualVolumeChanged(this->_tankIDchan0, this->_dataFrame->ADS115_1_chan0());
//        sendTankActualVolumeChanged(this->_tankIDchan1, this->_dataFrame->ADS115_1_chan1());

        //        }
        this->_timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
        sleepingDelay = (this->_timeInMilisecond - this->_memotimeInMilisecond) > this->_sleepingDelay ?
                    0 : this->_sleepingDelay - (this->_timeInMilisecond - this->_memotimeInMilisecond);

//        qDebug() << Q_FUNC_INFO << this->objectName() << "Time to read data : "
//                 << this->_timeInMilisecond - this->_memotimeInMilisecond << "[ms]";

        this->_waitDelayMili(sleepingDelay);
//        this->_timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
//        qDebug() << Q_FUNC_INFO << this->objectName() << "Time to read data : "
//                 << this->_timeInMilisecond - this->_memotimeInMilisecond << "[ms]";

    }
}

//qint16 ADS1115Item::PIDVolumeCoef() const
//{
//    return _PIDVolumeCoef;
//}

//void ADS1115Item::setPIDVolumeCoef(const qint16 &PIDVolumeCoef)
//{
//    _PIDVolumeCoef = PIDVolumeCoef;
//}

void ADS1115Item::setDataFrame(DataFrame *dataFrame)
{
    _dataFrame = dataFrame;
}

//qint8 ADS1115Item::offsetPressurChan3() const
//{
//    return _offsetPressurChan3;
//}

//qint8 ADS1115Item::offsetPressurChan2() const
//{
//    return _offsetPressurChan2;
//}

//qint8 ADS1115Item::offsetPressurChan1() const
//{
//    return _offsetPressurChan1;
//}

//qint8 ADS1115Item::offsetPressurChan0() const
//{
//    return _offsetPressurChan0;
//}

//void ADS1115Item::setOffsetPressurChan3(qint8 offsetPressurChan3)
//{
//    _offsetPressurChan3 = offsetPressurChan3;
//}

//void ADS1115Item::setOffsetPressurChan2(qint8 offsetPressurChan2)
//{
//    _offsetPressurChan2 = offsetPressurChan2;
//}

//void ADS1115Item::setOffsetPressurChan1(qint8 offsetPressurChan1)
//{
//    _offsetPressurChan1 = offsetPressurChan1;
//}

//void ADS1115Item::setOffsetPressurChan0(qint8 offsetPressurChan0)
//{
//    _offsetPressurChan0 = offsetPressurChan0;
//}

bool ADS1115Item::chan0_used() const
{
    return _chan0_used;
}

void ADS1115Item::setChan0_used(bool chan0_used)
{
    _chan0_used = chan0_used;
}

bool ADS1115Item::chan3_used() const
{
    return _chan3_used;
}

void ADS1115Item::setChan3_used(bool chan3_used)
{
    _chan3_used = chan3_used;
}

bool ADS1115Item::chan2_used() const
{
    return _chan2_used;
}

void ADS1115Item::setChan2_used(bool chan2_used)
{
    _chan2_used = chan2_used;
}

bool ADS1115Item::chan1_used() const
{
    return _chan1_used;
}

void ADS1115Item::setChan1_used(bool chan1_used)
{
    _chan1_used = chan1_used;
}

//void ADS1115Item::setChan1HighMaxValueInPuls(const quint64 &chan1HighMaxValueInPuls)
//{
//    _chan1HighMaxValueInPuls = chan1HighMaxValueInPuls;
//}

//void ADS1115Item::setChan0HighMaxValueInPuls(const quint64 &chan0HighMaxValueInPuls)
//{
//    _chan0HighMaxValueInPuls = chan0HighMaxValueInPuls;
//}

//void ADS1115Item::setOffsetChan1InPuls(const quint64 &offsetChan1InPuls)
//{
//    _offsetChan1InPuls = offsetChan1InPuls;
//}

//void ADS1115Item::setOffsetChan0InPuls(const quint64 &offsetChan0InPuls)
//{
//    _offsetChan0InPuls = offsetChan0InPuls;
//}

void ADS1115Item::setOnCalibration(bool onCalibration)
{
    _onCalibration = onCalibration;
}

bool ADS1115Item::startToReadOnData() const
{
    return _startToReadOnData;
}

void ADS1115Item::setStartToReadOnData(bool startToReadOnData)
{
    _startToReadOnData = startToReadOnData;
}

DataFrame *ADS1115Item::dataFrame() const
{
    return _dataFrame;
}

void ADS1115Item::_initDevice()
{
    do
    {
        this->_checkStateOfDevice();
        this->_waitDelay(1);
    }
    while(!this->_deviceIsReady);
}

void ADS1115Item::_initConfigDevice()
{
    this->_ads1115->setAds_osmode(OSMODE_SINGLE);
    this->_ads1115->setAds_gain(GAIN_TWOTHIRDS);
    this->_ads1115->setAds_mode(MODE_SINGLE);
    this->_ads1115->setAds_rate(_ads_rate);
    this->_ads1115->setAds_compmode(COMPMODE_TRAD);
    this->_ads1115->setAds_comppol(COMPPOL_LOW);
    this->_ads1115->setAds_complat(COMPLAT_NONLAT);
    this->_ads1115->setAds_MUX(MUX_SINGLE_0);
    this->_ads1115->setAds_compque(COMPQUE_NONE);

    this->_ads1115->setRegister(true);

}
bool ADS1115Item::_checkRegisterConfiguration()
{
    quint16 registerValue = this->_ads1115->readConfigRegister();
    quint16 configRegisterValue = 0x0000;

    configRegisterValue |= 0xF000;
    registerValue |= 0xF000;

    configRegisterValue |= this->_ads1115->ads_compque();
    configRegisterValue |= this->_ads1115->ads_complat();
    configRegisterValue |= this->_ads1115->ads_comppol();
    configRegisterValue |= this->_ads1115->ads_compmode();
    configRegisterValue |= this->_ads1115->ads_rate();
    configRegisterValue |= this->_ads1115->ads_mode();
    configRegisterValue |= this->_ads1115->ads_gain();

    //    qDebug() << Q_FUNC_INFO << "config register ADS1115: \t" << QString::number(configRegisterValue,2);
    //    qDebug() << Q_FUNC_INFO << "read register ADS1115: \t" << QString::number(registerValue,2);

    //    return (registerValue == 0b1111000100000011 ? true : false);    // RATE_8
    //              return (registerValue == 0b1111000100100011 ? true : false);    // RATE_16
    //        return (registerValue == 0b1111000101000011 ? true : false);    // RATE_32
    //        return (registerValue == 0b1111000101100011 ? true : false);    // RATE_64
    //        return (registerValue == 0b1111000110000011 ? true : false);    // RATE_128
    //        return (registerValue == 0b1111000111100011 ? true : false);    // RATE_860

    //        return (registerValue == 0b1100000101100011 ? true : false);    // MUX_SINGLE_0
    //    return (registerValue == 0b1111000101100011 ? true : false);    // MUX_SINGLE_3

    //        Bits [14:12] MUX[2:0]: Input multiplexer configuration (ADS1115 only)
    //                              100 : AINP = AIN0 and AINN = GND    registerValue == 0b1100000101100011
    //                              101 : AINP = AIN1 and AINN = GND    registerValue == 0b1101000101100011
    //                              110 : AINP = AIN2 and AINN = GND    registerValue == 0b1110000101100011
    //                              111 : AINP = AIN3 and AINN = GND    registerValue == 0b1111000101100011
    return (registerValue == configRegisterValue ? true : false);

}
void ADS1115Item::_checkStateOfDevice()
{
    switch (this->_stateMachine)
    {
    case GlobalEnumerate::STATE_NOT_FOUNDED:
    {
        //send text "not founded" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " " + GlobaleStaticValue::stateNotFounded);

        //check if the object was created
        if(&this->_ads1115 != nullptr)
        {
            this->_fd = this->_ads1115->ads_fd();
        }
        //check if the object was founded
        if(this->_ads1115->ads_fd())
        {
            this->_fd = this->_ads1115->ads_fd();
            _goToNextState();
            //jumpToNextState();
        }
        break;
    }

    case GlobalEnumerate::STATE_FOUNDED:
    {
        //send text "founded" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " " + GlobaleStaticValue::stateFounded);
        //change the color to red, not read to use
        QMetaObject::invokeMethod(this->_homeViewer, "changeColorAD1115_1",
                                  Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX));
        //display FD of the device
        this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " FD : " + QString::number(_ads1115->ads_fd(),10));

        _goToNextState();
        break;
    }

    case GlobalEnumerate::STATE_INIT:
    {
        //send text "init" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " " + GlobaleStaticValue::stateInit);

        //programme the device register
        this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " " + GlobaleStaticValue::stateOnProgramming);
        this->_initConfigDevice();
        this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " " + GlobaleStaticValue::stateCheckProgramming);

        //check the good programming of the device register
        if(this->_checkRegisterConfiguration())
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " " + GlobaleStaticValue::stateProgrammingSuccessful);

            _goToNextState();
        }
        break;
    }

    case GlobalEnumerate::STATE_ON_READING:
    {
        //qDebug() << Q_FUNC_INFO << "STATE_ON_READING";

        //send text "on reading" to display
        if(!this->_deviceIsReady)
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " " + GlobaleStaticValue::stateOnReading);
        }

        if(!this->_checkRegisterConfiguration())
        {
            this->_stateMachine = GlobalEnumerate::STATE_INIT;
            this->_checkStateOfDevice();
        }
        else
        {

            this->_onReadingData = true;
            //change the color to blue, on analysis
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorAD1115_1",
                                      Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));

            //check smooth data is full
            while(!this->_filterList0_IsFull && !this->_filterList1_IsFull && !this->_filterList1_IsFull && !this->_filterList1_IsFull)
            {
                this->_readDataI2C();
//                this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + "on reading smooth data : " +
//                                            QString::number(this->_filterListeChan0.size()));
            }

            this->_readDataI2C();
            _goToNextState();
        }

        break;
    }

    case GlobalEnumerate::STATE_READY:
    {
        //qDebug() << Q_FUNC_INFO << "STATE_READY";

        if(!this->_deviceIsReady)
        {
            this->_deviceIsReady = true;
            this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " " + GlobaleStaticValue::stateReady);

        }
        //change the color to green, ready to use
        QMetaObject::invokeMethod(this->_homeViewer, "changeColorAD1115_1",
                                  Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));

        this->_onReadingData = false;
        _goToNextState();
        break;
    }
    default:
        break;
    }

}
void ADS1115Item::_insertTextAtHomePage(QString textToInsert)
{
    QMetaObject::invokeMethod(this->_homeViewer, "addTextToDisplay",
                              Q_ARG(QVariant, textToInsert));
}
//void ADS1115Item::_readDataI2C()
//{
//    //    quint16 mask = 0xFFF8;
//    //        quint16 mask = 0xFFFC;
//    quint16 mask = 0xFFFF;
//    qint8 shiftToRight = 0;
//    qint16 dataframeState = this->_dataFrame->dataFrameState();

//    double chan0 = 0;
//    double chan1 = 0;

//    double BME280_pressure = this->_dataFrame->BME280_pressure();
//    double offsetPressure = 0;

//    static double minChan0 = 32700;
//    static double maxChan0 = 0;
//    static double minChan1 = 32700;
//    static double maxChan1 = 0;

//    static double memoChan0 = 0;
//    static double memoChan1 = 0;
//    double atmAtStart = ATM_DEFAULT_PRESSURE;

//    static bool firstTimeRequest = true;


//    if(this->_onCalibration)
//    {
//        //change sample frequency accisition
//        this->_sleepingDelay = 300;
//        //read register value
//        this->_chan0 = ((this->_ads1115->Mesure_Differential_0_1() - this->_offsetChan0InPuls) & mask) >> shiftToRight;
//        this->_chan1 = ((this->_ads1115->Mesure_Differential_2_3() - this->_offsetChan1InPuls) & mask) >> shiftToRight;
//        minChan0 = this->_chan0 < minChan0 ? this->_chan0 : minChan0;
//        minChan1 = this->_chan1 < minChan1 ? this->_chan1 : minChan1;
//        maxChan0 = this->_chan0 > maxChan0 ? this->_chan0 : maxChan0;
//        maxChan1 = this->_chan1 > maxChan1 ? this->_chan1 : maxChan1;

//        //        this->_chan0 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(0);
//        //        this->_chan1 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(1);
//        //        this->_chan2 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(2);
//        //        this->_chan3 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(3);
//    }
//    else
//    {
//        this->_sleepingDelay = 1000;
//        minChan0 = 32700;
//        minChan1 = 32700;
//        maxChan0 = 0;
//        maxChan1 = 0;

//        //        //read register value with mask
//        //        this->_chan0 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(0) & mask;
//        //        this->_chan1 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(1) & mask;
//        //        this->_chan2 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(2) & mask;
//        //        this->_chan3 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(3) & mask;

//        //calcul the mean of the list
//        //        while(_filterListeChan0.size()<10)
//        //        {
//        //            //read register value
//        //            //            _filterListeChan0.append(_ads1115->Measure_SingleEnded_OnlyPositiveValue(0) & mask);
//        //            //            _filterListeChan1.append(_ads1115->Measure_SingleEnded_OnlyPositiveValue(1) & mask);
//        //            //            _filterListeChan2.append(_ads1115->Measure_SingleEnded_OnlyPositiveValue(2) & mask);
//        //            //            _filterListeChan3.append(_ads1115->Measure_SingleEnded_OnlyPositiveValue(3) & mask);
//        //            if(this->chan0_used())
//        //            {
//        //                _filterListeChan0.append(_ads1115->Mesure_Differential_0_1() - this->_offsetChan0InPuls);
//        //            }

//        //            if(this->chan1_used())
//        //            {
//        //                _filterListeChan1.append(_ads1115->Mesure_Differential_2_3() - this->_offsetChan1InPuls);
//        //            }
//        //            //            _filterListeChan1.append(_ads1115->Measure_SingleEnded_OnlyPositiveValue(1));
//        //            //            _filterListeChan2.append(_ads1115->Measure_SingleEnded_OnlyPositiveValue(2));
//        //            //            _filterListeChan3.append(_ads1115->Measure_SingleEnded_OnlyPositiveValue(3));
//        //            //            this->_waitDelayMili(15);
//        //        }
//        if(this->chan0_used())
//        {
//            this->_chan0 = ((this->_ads1115->Mesure_Differential_0_1() - this->_offsetChan0InPuls) & mask) >> shiftToRight;

//            if(!firstTimeRequest)
//            {
//                chan0 = (this->_chan0 > (memoChan0 + HYSTERESIS) ||
//                         this->_chan0 < (memoChan0 - HYSTERESIS))
//                        ? memoChan0 : this->_chan0;
//            }
//            else
//            {
//                chan0 = this->_chan0;
//            }

//            chan0 = this->_meanList(_filterListeChan0, chan0);
//            this->_filterList0_IsFull = _filterListeChan0.size() >= NB_OF_VALUE_FOR_SMOOTH_PLOT ? true : false;

//            memoChan0 = chan0;

//            if(this->_filterList0_IsFull)
//            {
//                this->_chan0 != 0 ? dataframeState |= (1 << 3) :
//                        dataframeState &= (0 << 3);
//            }

//        }
//        else
//        {
//            dataframeState |= (1 << 3);
//            this->_filterList0_IsFull = true;
//        }


//        if(this->chan1_used())
//        {
//            this->_chan1 = ((this->_ads1115->Mesure_Differential_2_3() - this->_offsetChan1InPuls) & mask) >> shiftToRight;

//            if(!firstTimeRequest)
//            {
//                chan1 = (this->_chan1 > (memoChan1 + HYSTERESIS) ||
//                         this->_chan1 < (memoChan1 - HYSTERESIS))
//                        ? memoChan1 : this->_chan1;
//            }
//            else
//            {
//                chan1 = this->_chan1;
//            }

//            chan1 = this->_meanList(_filterListeChan1, chan1);
//            this->_filterList1_IsFull = _filterListeChan1.size() >= NB_OF_VALUE_FOR_SMOOTH_PLOT ? true : false;

//            memoChan1 = chan1;
//            if(this->_filterList1_IsFull)
//            {

//                this->_chan1 != 0 ? dataframeState |= (1 << 4) :
//                        dataframeState &= (0 << 4);
//            }
//        }
//        else
//        {
//            dataframeState |= (1 << 4);
//            this->_filterList0_IsFull = true;
//        }
//    }

//    //        this->_insertTextAtHomePage(
//    //                    GlobaleStaticValue::ADS1115_1Title
//    //                    + " : Chan0: " + QString::number(chan0) + ", \tmemoChan0: " + QString::number(memoChan0)
//    //                    + "\tChan1: " + QString::number(chan1) + ", \tmemoChan1: " + QString::number(memoChan1)
//    //                    + "\tBME280_pressure: " + QString::number(BME280_pressure)
//    //                    );

//#if VALUE_IN_VOLTS
//    //convert to volt
//    this->_chan0 = _ads1115->convertValueToVolt(this->_chan0);
//    this->_chan1 = _ads1115->convertValueToVolt(this->_chan1);
//    this->_chan2 = _ads1115->convertValueToVolt(this->_chan2);
//    this->_chan3 = _ads1115->convertValueToVolt(this->_chan3);

//    //display value
//    //        qDebug() << " | " << QString::number(this->_chan0, 'f', 3)
//    //                 << " | " << QString::number(this->_chan1, 'f', 3)
//    //                 << " | " << QString::number(this->_chan2, 'f', 3)
//    //                 << " | " << QString::number(this->_chan3, 'f', 3)
//    //                 << " | ";
//    this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " :   " +
//                                GlobaleStaticValue::ADS1115_Chan0 + " : " + QString::number(this->_chan0,'f',3) + " " + GlobaleStaticValue::ADS1115_Volt + ",\t" +
//                                GlobaleStaticValue::ADS1115_Chan1 + " : " + QString::number(this->_chan1,'f',3) + " " + GlobaleStaticValue::ADS1115_Volt + ",\t" +
//                                GlobaleStaticValue::ADS1115_Chan2 + " : " + QString::number(this->_chan2,'f',3) + " " + GlobaleStaticValue::ADS1115_Volt + ",\t" +
//                                GlobaleStaticValue::ADS1115_Chan3 + " : " + QString::number(this->_chan2,'f',3) + " " + GlobaleStaticValue::ADS1115_Volt
//                                );
//#else
//    if(!this->_onCalibration)
//    {
//        chan0 = chan0 < 0 ? 0 : chan0;
//        chan1 = chan1 < 0 ? 0 : chan1;


//        //pressure adaptation
//        switch (this->_tankChan0LiquideInside)
//        {
//        case GlobalEnumerate::WATER :
//            offsetPressure = ((atmAtStart-BME280_pressure)*100*
//                              (GlobaleStaticValue::pressureCoefWater+((double)this->_PIDVolumeCoef/100)));
//            break;
//        case GlobalEnumerate::OIL :
//            offsetPressure = ((atmAtStart-BME280_pressure)*100*
//                              (GlobaleStaticValue::pressureCoefOil+((double)this->_PIDVolumeCoef/100)));
//            break;
//        case GlobalEnumerate::ECO_OIL :
//            offsetPressure = ((atmAtStart-BME280_pressure)*100*
//                              (GlobaleStaticValue::pressureCoefOil+((double)this->_PIDVolumeCoef/100)));
//            break;
//        }


//        chan0 = chan0 + offsetPressure;

//        switch (this->_tankChan1LiquideInside)
//        {
//        case GlobalEnumerate::WATER :
//            offsetPressure = ((atmAtStart-BME280_pressure)*100*
//                              (GlobaleStaticValue::pressureCoefWater+((double)this->_PIDVolumeCoef/100)));
//            break;
//        case GlobalEnumerate::OIL :
//            offsetPressure = ((atmAtStart-BME280_pressure)*100*
//                              (GlobaleStaticValue::pressureCoefOil+((double)this->_PIDVolumeCoef/100)));
//            break;
//        case GlobalEnumerate::ECO_OIL :
//            offsetPressure =  ((atmAtStart-BME280_pressure)*100*
//                               (GlobaleStaticValue::pressureCoefOil+((double)this->_PIDVolumeCoef/100)));
//            break;
//        }

//        chan1 = chan1 + offsetPressure;

//        //        qDebug() << Q_FUNC_INFO << this->_deviceName << " atmAtStart : " << atmAtStart
//        //                 << " BME280_pressure : " << BME280_pressure << ", delt[Pa]: " << (atmAtStart-BME280_pressure)*100
//        //                 << "coef water : " << GlobaleStaticValue::pressureCoefWater+((double)this->_PIDVolumeCoef/100)
//        //                 << "chan0 : " << chan0 << " ,chan1 : " << chan1;

//        //if all datas are recording correctly
//        if(dataframeState == 31)
//        {
//            chan0 += _offsetPressurChan0;
//            chan1 += _offsetPressurChan1;

//            //convert puls to litre
//            chan0 = this->_convertToVolumeInLiter(0,
//                                                  chan0,
//                                                  this->_tankChan0VolumeMax,
//                                                  this->_tankChan0VolumeMaxHeightInMilimeter,
//                                                  this->_tankChan0LiquideInside);
//            chan1 = this->_convertToVolumeInLiter(1,
//                                                  chan1,
//                                                  this->_tankChan1VolumeMax,
//                                                  this->_tankChan1VolumeMaxHeightInMilimeter,
//                                                  this->_tankChan1LiquideInside);
//            chan0 = chan0 < 0 ? 0 : chan0;
//            chan1 = chan1 < 0 ? 0 : chan1;
//            chan0 = chan0 > 7000 ? 0 : chan0;
//            chan1 = chan1 > 7000 ? 0 : chan1;


//            if(firstTimeRequest)
//            {
//                firstTimeRequest = false;
//                sendTankActualVolumeChanged(this->_tankIDchan0, qRound(chan0));
//                sendTankActualVolumeChanged(this->_tankIDchan1, qRound(chan1));
//                this->_readDataI2C();
//            }

//            this->_dataFrame->setADS115_1_chan0(chan0);
//            this->_dataFrame->setADS115_1_chan1(chan1);

//            //            qDebug() << Q_FUNC_INFO << this->_deviceName << " atmAtStart : " << atmAtStart
//            //                     << " BME280_pressure : " << BME280_pressure << ", delt[Pa]: " << (atmAtStart-BME280_pressure)*100
//            //                     << "coef water : " << GlobaleStaticValue::pressureCoefWater+((double)this->_PIDVolumeCoef/100)
//            //                     << "chan0 : " << chan0 << " ,chan1 : " << chan1;

//            this->_insertTextAtHomePage(
//                        GlobaleStaticValue::ADS1115_1Title
//                        + ", atmAtStart : "  + QString::number(atmAtStart)
//                        + ",   BME280_pressure : " + QString::number(BME280_pressure, 'g', 3)
//                        + ",   delt[Pa]: " + QString::number((atmAtStart-BME280_pressure)*100,'g', 5)
//                        + ",   coef water : " + QString::number((GlobaleStaticValue::pressureCoefWater+((double)this->_PIDVolumeCoef/100)), 'g', 3)
//                        + ",   chan0 : "  + QString::number(chan0, 'g', 5)
//                        + ",   chan1 : "  + QString::number(chan1,'g', 5)
//                        + ",   filterSize : "  + QString::number(this->_filterListeChan1.size())
//                        );
//            //            this->_insertTextAtHomePage(
//            //                        GlobaleStaticValue::ADS1115_1Title
//            //                        + "\tatmAtStart : " + QString::number(atmAtStart) + "\tBME280_pressure : " + QString::number(BME280_pressure)
//            //                        + "\t\tdelta[Pa]: " + QString::number((atmAtStart-BME280_pressure)*100)
//            //                        + "\tWaterCoef: " + QString::number(GlobaleStaticValue::pressureCoefWater)
//            //                        + "\tWater[lt]: " + QString::number((atmAtStart-BME280_pressure)*100*GlobaleStaticValue::pressureCoefWater)
//            //                        );
//            //            //            qDebug() << Q_FUNC_INFO << this->_deviceName << " atmAtStart : " << atmAtStart
//            //                     << " BME280_pressure : " << BME280_pressure << ", delt[Pa]: " << (atmAtStart-BME280_pressure)*100;



//        } //this->_dataFrame->dataFrameState() == 7

//    }
//    else
//    {
//        this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " :   " +
//                                    GlobaleStaticValue::ADS1115_Chan0 + " : " + QString::number(this->_chan0) + "   \t" +
//                                    GlobaleStaticValue::ADS1115_Chan1 + " : " + QString::number(this->_chan1) + "   \t" +
//                                    " min " + GlobaleStaticValue::ADS1115_Chan0 + " : " + QString::number(minChan0) + "   \t" +
//                                    " max " + GlobaleStaticValue::ADS1115_Chan0 + " : " + QString::number(maxChan0) + "   \t" +
//                                    " min " + GlobaleStaticValue::ADS1115_Chan1 + " : " + QString::number(minChan1) + "   \t" +
//                                    " max " + GlobaleStaticValue::ADS1115_Chan1 + " : " + QString::number(maxChan1)
//                                    );

//    }

//    //    qDebug() << Q_FUNC_INFO
//    //             << "Chan0 used: " << this->_chan0_used << ", Chan1 used: " << this->_chan1_used
//    //             << "Chan2 used: " << this->_chan2_used << ", Chan3 used: " << this->_chan3_used;

//    //    qDebug() << Q_FUNC_INFO << "Chan0 : " << this->_chan0 << " ,mean : "
//    //             << chan0 <<  " ,memo : " << memoChan0 << " ,cpt : " <<cptChan0;
//    //    qDebug() << Q_FUNC_INFO << "Chan1 : " << this->_chan1 << " ,mean : "
//    //             << chan1 <<  " ,memo : " << memoChan1 << " ,cpt : " <<cptChan1;



//#endif
//    if(this->_deviceIsReady)
//    {

//        if(this->_dataFrame!=nullptr && this->_dataFrame->dataFrameState() == 7)
//        {
//            if(this->_deviceName == GlobaleStaticValue::ADS1115_1Title)
//            {
//                this->_dataFrame->setADS115_1_chan0(chan0);
//                this->_dataFrame->setADS115_1_chan1(chan1);
//                //                dataFrame->setADS115_1_chan2(chan2);
//                //                dataFrame->setADS115_1_chan3(chan3);
//            }

//            if(this->_deviceName == GlobaleStaticValue::ADS1115_2Title)
//            {
//                this->_dataFrame->setADS115_2_chan0(chan0);
//                this->_dataFrame->setADS115_2_chan1(chan1);
//            }

//            this->_dataFrame->setDataFrameState(dataframeState);
//        }

//    }
////    _goToNextState();
////    this->_checkStateOfDevice();
//}


void ADS1115Item::_readDataI2C()
{

//    this->_memotimeInMilisecond = QDateTime::currentMSecsSinceEpoch();

    qint16 chan0 = -32767;
    qint16 chan1 = -32767;

   qint16 dataframeState = this->_dataFrame->dataFrameState();


    static bool firstTimeRequest = true;


    if(this->_onCalibration)
    {
        //change sample frequency accisition
        this->_sleepingDelay = 300;
        //read register value
        this->_chan0 = this->_ads1115->Mesure_Differential_0_1();
        this->_chan1 = this->_ads1115->Mesure_Differential_2_3();
    }
    else
    {
        if(this->chan0_used())
        {
            this->_chan0 = this->_ads1115->Mesure_Differential_0_1();

                chan0 = this->_chan0;

            chan0 = this->_meanList(_filterListeChan0, chan0);
            this->_filterList0_IsFull = _filterListeChan0.size() >= NB_OF_VALUE_FOR_SMOOTH_PLOT ? true : false;

            if(this->_filterList0_IsFull)
            {
                this->_chan0 != -32767 ? dataframeState |= (1 << 3) :
                        dataframeState &= (0 << 3);
            }

        }
        else
        {
            dataframeState |= (1 << 3);
            this->_filterList0_IsFull = true;
        }


        if(this->chan1_used())
        {
            this->_chan1 = this->_ads1115->Mesure_Differential_2_3();

                chan1 = this->_chan1;

            chan1 = this->_meanList(_filterListeChan1, chan1);
            this->_filterList1_IsFull = _filterListeChan1.size() >= NB_OF_VALUE_FOR_SMOOTH_PLOT ? true : false;

            if(this->_filterList1_IsFull)
            {

                this->_chan1 != -32767 ? dataframeState |= (1 << 4) :
                        dataframeState &= (0 << 4);
            }
        }
        else
        {
            dataframeState |= (1 << 4);
            this->_filterList0_IsFull = true;
        }
    }

    //        this->_insertTextAtHomePage(
    //                    GlobaleStaticValue::ADS1115_1Title
    //                    + " : Chan0: " + QString::number(chan0) + ", \tmemoChan0: " + QString::number(memoChan0)
    //                    + "\tChan1: " + QString::number(chan1) + ", \tmemoChan1: " + QString::number(memoChan1)
    //                    + "\tBME280_pressure: " + QString::number(BME280_pressure)
    //                    );

    if(!this->_onCalibration)
    {

        //if all datas are recording correctly
        if(dataframeState == 24)
        {


            if(firstTimeRequest)
            {
                firstTimeRequest = false;
//                sendTankActualVolumeChanged(this->_tankIDchan0, chan0);
//                sendTankActualVolumeChanged(this->_tankIDchan1, chan1);
                this->_readDataI2C();
            }

            this->_dataFrame->setADS115_1_chan0(chan0);
            this->_dataFrame->setADS115_1_chan1(chan1);
            this->_dataFrame->setDataFrameState(dataframeState);

            //            qDebug() << Q_FUNC_INFO << this->_deviceName << " atmAtStart : " << atmAtStart
            //                     << " BME280_pressure : " << BME280_pressure << ", delt[Pa]: " << (atmAtStart-BME280_pressure)*100
            //                     << "coef water : " << GlobaleStaticValue::pressureCoefWater+((double)this->_PIDVolumeCoef/100)
            //                     << "chan0 : " << chan0 << " ,chan1 : " << chan1;

//            this->_insertTextAtHomePage(
//                        GlobaleStaticValue::ADS1115_1Title
//                        + ", atmAtStart : "  + QString::number(atmAtStart)
//                        + ",   BME280_pressure : " + QString::number(BME280_pressure, 'g', 3)
//                        + ",   delt[Pa]: " + QString::number((atmAtStart-BME280_pressure)*100,'g', 5)
//                        + ",   coef water : " + QString::number((GlobaleStaticValue::pressureCoefWater+((double)this->_PIDVolumeCoef/100)), 'g', 3)
//                        + ",   chan0 : "  + QString::number(chan0, 'g', 5)
//                        + ",   chan1 : "  + QString::number(chan1,'g', 5)
//                        + ",   filterSize : "  + QString::number(this->_filterListeChan1.size())
//                        );
            //            this->_insertTextAtHomePage(
            //                        GlobaleStaticValue::ADS1115_1Title
            //                        + "\tatmAtStart : " + QString::number(atmAtStart) + "\tBME280_pressure : " + QString::number(BME280_pressure)
            //                        + "\t\tdelta[Pa]: " + QString::number((atmAtStart-BME280_pressure)*100)
            //                        + "\tWaterCoef: " + QString::number(GlobaleStaticValue::pressureCoefWater)
            //                        + "\tWater[lt]: " + QString::number((atmAtStart-BME280_pressure)*100*GlobaleStaticValue::pressureCoefWater)
            //                        );
            //            //            qDebug() << Q_FUNC_INFO << this->_deviceName << " atmAtStart : " << atmAtStart
            //                     << " BME280_pressure : " << BME280_pressure << ", delt[Pa]: " << (atmAtStart-BME280_pressure)*100;



        } //this->_dataFrame->dataFrameState() == 7

    }
    else
    {
        this->_insertTextAtHomePage(GlobaleStaticValue::ADS1115_1Title + " :   " +
                                    GlobaleStaticValue::ADS1115_Chan0 + " : " + QString::number(this->_chan0) + "   \t" +
                                    GlobaleStaticValue::ADS1115_Chan1 + " : " + QString::number(this->_chan1));
    }
        //    qDebug() << Q_FUNC_INFO
    //             << "Chan0 used: " << this->_chan0_used << ", Chan1 used: " << this->_chan1_used
    //             << "Chan2 used: " << this->_chan2_used << ", Chan3 used: " << this->_chan3_used;

    //    qDebug() << Q_FUNC_INFO << "Chan0 : " << this->_chan0 << " ,mean : "
    //             << chan0 <<  " ,memo : " << memoChan0 << " ,cpt : " <<cptChan0;
    //    qDebug() << Q_FUNC_INFO << "Chan1 : " << this->_chan1 << " ,mean : "
    //             << chan1 <<  " ,memo : " << memoChan1 << " ,cpt : " <<cptChan1;



    if(this->_deviceIsReady)
    {

        if(this->_dataFrame!=nullptr && this->_dataFrame->dataFrameState() == 7)
        {
            if(this->_deviceName == GlobaleStaticValue::ADS1115_1Title)
            {
                this->_dataFrame->setADS115_1_chan0(chan0);
                this->_dataFrame->setADS115_1_chan1(chan1);
                //                dataFrame->setADS115_1_chan2(chan2);
                //                dataFrame->setADS115_1_chan3(chan3);
            }

            if(this->_deviceName == GlobaleStaticValue::ADS1115_2Title)
            {
                this->_dataFrame->setADS115_2_chan0(chan0);
                this->_dataFrame->setADS115_2_chan1(chan1);
            }

            this->_dataFrame->setDataFrameState(dataframeState);
        }

    }


//    _goToNextState();
//    this->_checkStateOfDevice();
}

//double ADS1115Item::_convertToVolumeInLiter(quint8 channelNumber,
//                                            double valueIn,
//                                            quint16 tankolumeMax,
//                                            quint16 tankVolumeMMaxHeightInMilimeter,
//                                            GlobalEnumerate::E_TankLiquidInside liquide)
//{

//    double liquideDensity = 0;
//    double heightMaxInTankInPlus = 0;

//    switch (liquide)
//    {
//    case GlobalEnumerate::WATER:
//    {
//        liquideDensity = GlobaleStaticValue::densityWater;
//        break;
//    }
//    case GlobalEnumerate::OIL:
//    {
//        liquideDensity = GlobaleStaticValue::densityOil;
//        break;
//    }
//    case GlobalEnumerate::ECO_OIL:
//    {
//        liquideDensity = GlobaleStaticValue::densityOilECO;
//        break;
//    }
//    default:
//        break;
//    }

//    //    heightMaxInTankInPlus = ((GlobaleStaticValue::pressureCapteurRangeMaxInPlus*tankVolumeMMaxHeightInMilimeter)/
//    //                             (GlobaleStaticValue::pressureCapteurHeightMaxWater/liquideDensity));

//    switch (channelNumber)
//    {
//    case 0:
//    {
//        heightMaxInTankInPlus = ((this->_chan0HighMaxValueInPuls*tankVolumeMMaxHeightInMilimeter)/
//                                 (GlobaleStaticValue::pressureCapteurHeightMaxWater/liquideDensity));
//        break;
//    }
//    case 1:
//    {
//        heightMaxInTankInPlus = ((this->_chan1HighMaxValueInPuls*tankVolumeMMaxHeightInMilimeter)/
//                                 (GlobaleStaticValue::pressureCapteurHeightMaxWater/liquideDensity));
//        break;
//    }
//    default:
//        break;
//    }

//    //    qDebug() << Q_FUNC_INFO << qRound(valueIn*tankolumeMax/heightMaxInTankInPlus);
//    //    this->_insertTextAtHomePage("_convertToVolumeInLiter chan" + QString::number(channelNumber) + " : " + QString::number(qRound(valueIn*tankolumeMax/heightMaxInTankInPlus)));
//    // this->_insertTextAtHomePage("_convertToVolumeInLiter chan" + QString::number(channelNumber) + " : " + QString::number(valueIn*(double)tankolumeMax/heightMaxInTankInPlus));

//    //    return (qRound(valueIn*tankolumeMax/heightMaxInTankInPlus));
//    return (valueIn*(double)tankolumeMax/heightMaxInTankInPlus);

//}

void ADS1115Item::_continueReadingAllValue()
{
    float chan0 = 0;
    float chan1 = 0;
    float chan2 = 0;
    float chan3 = 0;

    while(true)
    {
        //read register value
        chan0 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(0);
        chan1 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(1);
        chan2 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(2);
        chan3 =   _ads1115->Measure_SingleEnded_OnlyPositiveValue(3);

        //convert to volt
        chan0 = _ads1115->convertValueToVolt(chan0);
        chan1 = _ads1115->convertValueToVolt(chan1);
        chan2 = _ads1115->convertValueToVolt(chan2);
        chan3 = _ads1115->convertValueToVolt(chan3);

        //display value
        qDebug() << " | " << QString::number(chan0, 'f', 3)
                 << " | " << QString::number(chan1, 'f', 3)
                 << " | " << QString::number(chan2, 'f', 3)
                 << " | " << QString::number(chan3, 'f', 3)
                 << " | ";
        this->_waitDelay(1);
    }
}

void ADS1115Item::_waitDelay(quint64 delaySeconde)
{
    QThread::sleep(delaySeconde);
}

void ADS1115Item::_waitDelayMili(quint64 delayInMiliSeconde)
{
    QThread::msleep(delayInMiliSeconde);
}

void ADS1115Item::_waitDelayMicro(quint64 delayInMicroSeconde)
{
    QThread::usleep(delayInMicroSeconde);
}

void ADS1115Item::_goToNextState()
{
    switch (this->_stateMachine)
    {
    case GlobalEnumerate::STATE_NOT_FOUNDED:
    {
        this->_stateMachine = GlobalEnumerate::STATE_FOUNDED;
        break;
    }
    case GlobalEnumerate::STATE_FOUNDED:
    {
        this->_stateMachine = GlobalEnumerate::STATE_INIT;
        break;
    }
    case GlobalEnumerate::STATE_INIT:
    {
        this->_stateMachine = GlobalEnumerate::STATE_ON_READING;
        break;
    }
    case GlobalEnumerate::STATE_ON_READING:
    {
        this->_stateMachine = GlobalEnumerate::STATE_READY;
        break;
    }
    case GlobalEnumerate::STATE_READY:
    {
        this->_stateMachine = GlobalEnumerate::STATE_ON_READING;
        break;
    }
    default:
        break;
    }
}

double ADS1115Item::_meanList(QList<double> &listToMean, double value)
{
    double meanvalue = 0;

    listToMean.append(value);

    if(listToMean.size() > NB_OF_VALUE_FOR_SMOOTH_PLOT)
    {
        listToMean.removeFirst();
    }


    foreach(int n, listToMean)
    {
        meanvalue+=n;
    }

    //    qDebug() << Q_FUNC_INFO << "mean as double : " << (float)meanvalue/listToMean.size();
    //    qDebug() << Q_FUNC_INFO << "mean as double : " << qRound((float)meanvalue/listToMean.size());

    return (meanvalue/listToMean.size());
}

quint16 ADS1115Item::_maxList(QList<quint16> &listToMean)
{
    return (*std::max_element(listToMean.begin(), listToMean.end()));
}

//void ADS1115Item::receivedAddNewDataFromThread()
//{
//    //    bool readytoCheck = false;

//    //    qDebug() << Q_FUNC_INFO << "_deviceIsReady : " << _deviceIsReady;

//    bool readToCheck = false;

//    if(!this->_onReadingSavedData)
//    {
//  //          qDebug() << Q_FUNC_INFO << "_onReadingSavedData : " << _onReadingSavedData;

//        if(this->_deviceIsReady)
//        {
//            do
//            {
//                readToCheck = this->_stateMachine == GlobalEnumerate::STATE_READY ? true : false;
//                this->_waitDelayMili(1);
//            }
//            while(!readToCheck);


//            _goToNextState();
//            this->_checkStateOfDevice();
//        }
//        else
//        {
//            this->_checkStateOfDevice();
//        }
//    }
//}
