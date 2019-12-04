#ifndef GLOBALSTYLE_H
#define GLOBALSTYLE_H

#include <QColor>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QMetaType>
#include <QQmlEngine>
#include <qcustomplot.h>

//main windows
//size
#define MINIMUM_WIDTH_SIZE 1280
#define MINIMUM_HEIGHT_SIZE 720

//color RGB  R, G, B  alpha = 255
#define BACKGROUD_COLOR 70,70,70                                   //deep drak Grey
#define BACKGROUD_COLOR_PUSHBUTTON_LIGHT 220,220,220               //light Gray
#define BACKGROUD_COLOR_PUSHBUTTON_DARK 90,90,90                   //drak Grey
#define BACKGROUD_COLOR_LABEL 125,125,125                          //Gray
#define BACKGROUD_COLOR_FRAME 119,119,119                          //Gray
#define BACKGROUD_COLOR_ERROR_FRAME 255,160,160                    //soft Red

//ERROR
#define DEVICE_COLOR_IN_TROUBLE 255, 64, 64                     //RGB, R=255,   G=0,  B=0   aplha = 255
#define DEVICE_COLOR_IN_TROUBLE_HEX "#FF4040"                     //RGB, R=255,   G=0,  B=0   aplha = 255

//Ready
#define DEVICE_COLOR_READY 140, 255, 140                     //RGB, R=255,   G=0,  B=0   aplha = 255
#define DEVICE_COLOR_READY_HEX "#60FF60"

//On analysis
#define DEVICE_COLOR_WORKING 0, 140, 255                     //RGB, R=255,   G=0,  B=0   aplha = 255
#define DEVICE_COLOR_WORKING_HEX "#0060FF"

//PLOT
//analog plot size
#define ANALOG_PLOT_MINIMUM_WIDTH_SIZE 960
#define ANALOG_PLOT_MINIMUM_HEIGHT_SIZE 22

//digital plot size
#define DIGITAL_PLOT_MINIMUM_WIDTH_SIZE 960
#define DIGITAL_PLOT_MINIMUM_HEIGHT_SIZE 22

//color
#define BACKGROUD_COLOR_PLOT         25,25,25                //Dark Gray close to black

#define GRID_COLOR_PLOT             255, 255, 0, 100        //RGB, R=140,   G=140,  B=140   aplha = 100
#define AXIS_COLOR_PLOT             250, 250, 250           //RGB, R=140,   G=140,  B=140   aplha = 255
#define AXE_GRID_COLOR_PLOT         255, 255, 0             //RGB, R=140,   G=140,  B=140   aplha = 255

//pen
#define TEMPERATURE_PLOT_TRACE          237, 41, 57         //Imperial red
#define TEMPERATURE_UNDER_PLOT_TRACE      237, 41, 57, 30     //Imperial red with alpha
#define HUMIDITY_PLOT_TRACE             0, 153, 255         //Blue
#define HUMIDITY_UNDER_PLOT_TRACE       0, 153, 255, 30     //Blue with alpha
#define PRESSURE_PLOT_TRACE             250, 218, 94        //Royal yellow
#define PRESSURE_UNDER_PLOT_TRACE       250, 218, 94, 30    //Royal yellow with alpha
#define CONSO_PLOT_TRACE                220, 220, 220       //Gray
#define CONSO_UNDER_PLOT_TRACE          220, 220, 220, 30   //Gray with alpha
#define DIGITAL_PLOT_TRACE_ON           155, 220, 155       //soft green
#define DIGITAL_RED_PLOT_TRACE_ON       200, 155, 155
#define TANK1_PLOT_TRACE                116, 80, 60         //braun
#define TANK2_PLOT_TRACE                128, 128, 128       //Gray
#define TANK3_PLOT_TRACE                255, 96, 208        //Pink
#define TANK4_PLOT_TRACE                160, 32, 255        //Purple
#define TANK5_PLOT_TRACE                80, 208, 255        //Light Blue
#define TANK6_PLOT_TRACE                255, 208, 160       //Light Pink

//#define TEMPERATURE_PLOT_TRACE              51, 204, 51    //green

class GlobalStyle
{
public:
    GlobalStyle();

    //BACKGROUND
    static void setBackGroundColor(QCustomPlot *customPlot);

//    //ERROR
//    static void setErrorColor(QLabel *label);
//    static void setErrorColor(QFrame *frame);

    //PLOT
    //style
    static void setStylePlot(QCustomPlot *customPlot, bool tickAsTime);
    static void setStyleStatisticPlot(QCustomPlot *customPlot, bool tickAsTime);

    //pen
    //temperature trace
    static void setTraceColorTemperaturePlot(QCPGraph *graph);
    static void setTraceColorTemperatureMinPlot(QCPGraph *graph, QCPGraph *graphAbove);

    //humidity trace
    static void setTraceColorHumidityPlot(QCPGraph *graph);
    static void setTraceColorHumidityMaxPlot(QCPGraph *graph);
    static void setTraceColorHumidityMinPlot(QCPGraph *graph, QCPGraph *graphAbove);

    //humidity trace
    static void setTraceColorPressurePlot(QCPGraph *graph);
    static void setTraceColorPressureMinPlot(QCPGraph *graph, QCPGraph *graphAbove);

    //conso trace
    static void setTraceColorConsoPlot(QCPGraph *graph);
    static void setTraceColorConsoMinPlot(QCPGraph *graph, QCPGraph *graphAbove);

    //tanks trace
    static void setTraceColorTankTrace1(QCPGraph *graph);
    static void setTraceColorTankTrace2(QCPGraph *graph);
    static void setTraceColorTankTrace3(QCPGraph *graph);
    static void setTraceColorTankTrace4(QCPGraph *graph);
    static void setTraceColorTankTrace5(QCPGraph *graph);
    static void setTraceColorTankTrace6(QCPGraph *graph);

//    //digital trace
//    static void setTraceColorTriggerPlot(QCPGraph *graph);
//    static void setTraceColorTriggerPlot(QCPItemStraightLine *line);

//    //pushbutton unselect Shape
//    static void setPushButtonUnselected(QPushButton *pushButton);
//    static void setPushButtonBlocked(QPushButton *pushButton);

//    //doublspinbox Shape
//    static void setSpinBoxShape(QSpinBox *spinBox);
//    static void setDoublespinBoxShape(QDoubleSpinBox *doubleSpinBox);

//    //main button start
//    static void setStartButtonToGreen(QPushButton *pushButton);
//    static void setStartButtonToRed(QPushButton *pushButton);

//    //button on status barre
//    static void setButtonStatusBarSelect(QPushButton *pushButton);
//    static void setButtonStatusBarUnselect(QPushButton *pushButton);


//    //main backrgound color
    static QColor _backGroundColor;

//private:
//    static QColor _backGroundColorLabel;
//    static QColor _backGroundColorFrame;
//    static QColor _backGroundColorPlot;
//    static QColor _backGroundColorPushButtonLight;
//    static QColor _backGroundColorPushButtonDark;

//    //ERROR
//    static QColor _backGroundColorErrorFrame;
//    static QColor _errorLineInTrouble;

//    //PLOT
//    //Grid
    static QColor _gridColorPlot;

    //Axis
    static QColor _axisColorPlot;
    static QColor _axisTickPlot;

    //pen
    //Temperature trace
    static QColor _traceColorTemperaturePlot;
    static QColor _traceColorTemperatureMinPlot;

    //humidity trace
    static QColor _traceColorHumidityPlot;
    static QColor _traceColorHumidityMinPlot;

    //pressure trace
    static QColor _traceColorPressurePlot;

    //conso trace
    static QColor _traceColorConsoPlot;

    //tanks trace
    static QColor _traceColortank1;
    static QColor _traceColortank2;
    static QColor _traceColortank3;
    static QColor _traceColortank4;
    static QColor _traceColortank5;
    static QColor _traceColortank6;
//    static QColor _backGroundLabelDIPlotON;
//    static QColor _backGroundLabelRedDIPlotON;
    static QColor traceColorTemperatureMaxPlot();
    static void setTraceColorTemperatureMaxPlot(const QColor &traceColorTemperatureMaxPlot);
};

#endif // GLOBALSTYLE_H
