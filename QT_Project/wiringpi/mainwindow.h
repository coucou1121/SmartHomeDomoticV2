#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QTimer>
#include <QThread>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>

#include <mcp3004.h>
#include <bme280cpp.h>
#include <bme280.h>

#define BASE 200
#define SPI_CHAN 0

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void readDataSP();

    void readDataI2C();

    BME280 *bme280_1;
    //actif wait delay
        /**
          * \fn void _waitDelay(int delayInSeconde)
          * \brief Active wait delay
          * \param[in] Delay to wait in seconds.
          * \return void : nothing
          */
        void _waitDelay(int delayInSeconde);
};

#endif // MAINWINDOW_H


