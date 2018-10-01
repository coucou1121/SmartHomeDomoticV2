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
#define ERROR_LINE_COLOR_IN_TROUBLE 255, 0, 0                     //RGB, R=255,   G=0,  B=0   aplha = 255

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
#define TEMPERATURE_PLOT_TRACE              237, 41, 57    //Imperial red
#define HUMIDITY_PLOT_TRACE                  0, 153, 255   //Blue
#define HUMIDITY_UNDER_PLOT_TRACE            0, 153, 255, 50   //Blue with alpha
#define PRESSURE_PLOT_TRACE                 250, 218, 94   //Royal yellow
#define DIGITAL_PLOT_TRACE_ON  155, 220, 155             //soft green
#define DIGITAL_RED_PLOT_TRACE_ON 200, 155, 155
//#define TEMPERATURE_PLOT_TRACE              51, 204, 51    //green

class GlobalStyle
{
public:
    GlobalStyle();

    //BACKGROUND
    static void setBackGroundColor(QCustomPlot *customPlot);
//    static void setBackGroundColor(QLabel *label);
//    static void setBackGroundColor(QPushButton *pushButton);
//    static void setbackGroundColorLabel(QLabel *label);
//    static void setbackGroundColorLabel(QPushButton *pushButton);
//    static void setbackGroundColorLabelUnselected(QLabel *label);
//    static void setbackGroundColorLabelUnselected(QPushButton *pushButton);
//    static void setbackGroundColorLabelPlot(QLabel *label);
//    static void setbackGroundColorLabelPlotSmall(QLabel *label);
//    static void setbackGroundColorFrame(QFrame *frame);
//    static void setbackGroundColorFrame(QWidget *widget);
//    static void setBackGroundColorPlot(QCPAxisRect *qcpAxisRect);
//    static void setBackGroundColorDILabel(QLabel *label);
//    static void setBackGroundColorRedDILabel(QLabel *label);
//    static void setBackGroundColorAISelected(QPushButton *pushButton);
//    static void setBackGroundColorDISelected(QPushButton *pushButton);

//    //ERROR
//    static void setErrorColor(QLabel *label);
//    static void setErrorColor(QFrame *frame);

    //PLOT
    static void setStylePlot(QCustomPlot *customPlot);

    //pen
    //temperature trace
    static void setTraceColorTemperaturePlot(QCPGraph *graph);

    //humidity trace
    static void setTraceColorHumidityPlot(QCPGraph *graph);

    //humidity trace
    static void setTraceColorPressurePlot(QCPGraph *graph);

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

    //humidity trace
    static QColor _traceColorHumidityPlot;

    //pressure trace
    static QColor _traceColorPressurePlot;
//    static QColor _backGroundLabelDIPlotON;
//    static QColor _backGroundLabelRedDIPlotON;
};

#endif // GLOBALSTYLE_H
