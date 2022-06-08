#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "chart.hpp"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // instead of: delete device;
    this->device = new QSerialPort(this);

    //scene setup
    this->scene = new QGraphicsScene(this);
    ui->graphicsViewPlane->setScene(scene);
    this->scene->setSceneRect(-100, -100, 400, 400);

    // adding vehicle to the scene
    this->vehicle = new Vehicle();
    this->scene->addItem(this->vehicle);

    // setting up animation stuff
    this->timer = new QTimeLine(100);
    this->animation  = new QGraphicsItemAnimation;
    this->animation->setItem(this->vehicle);
    this->animation->setTimeLine(timer);
    this->view = new QGraphicsView(this->scene);

    // connecting signals and slots
    connect(this, &MainWindow::analyzedDataAvailable, this, &MainWindow::print_values);
    connect(this, &MainWindow::analyzedDataAvailable, this, &MainWindow::updateVehicleStatus);

    // setting default values
    gyro_counter = 0;
    angleY = angleZ = valueV = 0;
    prev_time = curr_time = 0;
    gyroYcalli = gyroZcalli = 0;
    prev_GyrY_value = curr_GyrY_value = prev_GyrZ_value = curr_GyrZ_value = 0;
    rot = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    ui->comboBoxDevices->clear();
    this->addToLogs("Szukam urządzeń...");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    if(devices.count() > 0)
    {
        for(int i=0; i<devices.count(); i++)
        {
            this->addToLogs(devices.at(i).portName() + " " + devices.at(i).description());
            ui->comboBoxDevices->addItem(devices.at(i).portName());
        }
    }
}

void MainWindow::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxDevices->count() == 0)
    {
        this->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }
    if(this->device->isOpen())
    {
        this->addToLogs("Port jest już otwarty!");
        return;
    }

    QString portName = "/dev/" + ui->comboBoxDevices->currentText();
    this->device->setPortName(portName);
    //qDebug() << portName;

    if(device->open(QSerialPort::ReadWrite))
    {
        this->device->setBaudRate(QSerialPort::Baud115200);
        this->device->setParity(QSerialPort::NoParity);
        this->device->setDataBits(QSerialPort::Data8);
        this->device->setStopBits(QSerialPort::OneStop);
        this->device->setFlowControl(QSerialPort::NoFlowControl);

        this->addToLogs("Połączono z urządzeniem " + portName);
        qDebug() << "połączył";
        connect(this->device, SIGNAL(readyRead()), this, SLOT(callibrateGyroscope()));
        this->callibrateGyroscope();
    }
    else
    {
        this->addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        this->addToLogs(device->errorString());
        qDebug() << this->device->error();
    }
}


void MainWindow::on_pushButtonDisconnect_clicked()
{
    if(this->device->isOpen())
    {
      this->device->close();
      this->addToLogs("Zamknięto połączenie.");
    }
    else
    {
      this->addToLogs("Port nie jest otwarty!");
    }
}

void MainWindow::on_pushButtonReset_clicked()
{
    this->animateVehicle(10, 10, 30);
}

void MainWindow::on_pushButtonCharts_clicked()
{
    ChartWindow GyrXWin(&this->Gy_raw, &this->Gz_raw, nullptr);
    GyrXWin.setModal(false);

    GyrXWin.beginPlot();

    GyrXWin.exec();
    this->show();
}

void MainWindow::print_values()
{
    ui->textEditValueX->clear();
    ui->textEditValueX->append(QString::number(angleY));
    ui->textEditValueY->clear();
    ui->textEditValueY->append(QString::number(angleZ));
    ui->textEditValueV->clear();
    ui->textEditValueV->append(QString::number(valueV));
}

//**************************************************************************************************

void MainWindow::addToLogs(QString message)
{
    QString currDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(currDateTime + "\t" + message);
}

void MainWindow::callibrateGyroscope()
{
    if(gyro_counter == 0)
        this->addToLogs("Callibrating gyroscope, please wait.");

    while(this->device->canReadLine())
    {
        int init, work;
        qreal Gy, Gz;
        bool is_data_ok = false;

        QString line = this->device->readLine();
        // reading control values on fixed positions
        init = line.at(0).digitValue();
        work = line.at(2).digitValue();
        //butt = line.at(4).digitValue();

        if(init && work)
            is_data_ok = true;

        // getting sensor values
        if(is_data_ok)
        {
            // setting number of chars to read
            //always x.xx = 4 + 1 for sign
            //(if value is positive it reads " " and cuts it during conversion to float)
            int char_num = 5;
            // getting 5 chars from 5th index
            Gy = line.mid(5, char_num).toFloat();
            // getting index of next " " after 6th pos
            int gy_pos = line.indexOf(" ", 6) + 1;
            // getting 5 chars from next " " char
            Gz = line.mid(gy_pos, 5).toFloat();

            // callibrating gyroscope
            if(gyro_counter < 500)
            {
                qDebug() << gyro_counter << Gy << Gz;
                this->gyroYcalli += Gy;
                this->gyroZcalli += Gz;
            }
            else
            {
                this->gyroYcalli /= 500;
                this->gyroZcalli /= 500;
                this->addToLogs("Gyroscope is now callibrated, enjoy Your simulation.");
                disconnect(this->device, SIGNAL(readyRead()), this, SLOT(callibrateGyroscope()));
                connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromDevice()));
            }

            gyro_counter++;
        }
    }
}

void MainWindow::readFromDevice()
{
    while(this->device->canReadLine())
    {
        int init, work, butt;
        qreal Gy, Gz;
        bool is_data_ok = false;

        QString line = this->device->readLine();
        // reading control values on fixed positions
        init = line.at(0).digitValue();
        work = line.at(2).digitValue();
        butt = line.at(4).digitValue();

        if(init && work && butt)
            is_data_ok = true;

        // getting sensor values
        if(is_data_ok)
        {
            // setting number of chars to read
            //always x.xx = 4 + 1 for sign
            //(if value is positive it reads " " and cuts it during conversion to float)
            int char_num = 5;
            // getting 5 chars from 5th index
            Gy = line.mid(5, char_num).toFloat();
            // getting index of next " " after 6th pos
            int gy_pos = line.indexOf(" ", 6) + 1;
            // getting 5 chars from next " " char
            Gz = line.mid(gy_pos, 5).toFloat();

            this->Gy_raw = Gy;
            this->Gz_raw = Gz;

            this->curr_GyrY_value = Gy;
            this->curr_GyrZ_value = Gz;
            //this->curr_time += 0.1;
            this->analyzeData();
        }
        else
        {
            this->addToLogs("Please press button or check connection lines!");
        }
    }
}

void MainWindow::analyzeData()
{
    // calculating angular displacement
    this->angleY = 0.5*(0.1)*
            (this->curr_GyrY_value+this->prev_GyrY_value-2*this->gyroYcalli);
    this->angleZ = 0.5*(0.1)*
            (this->curr_GyrZ_value+this->prev_GyrZ_value-2*this->gyroZcalli);

    this->prev_GyrY_value = this->curr_GyrY_value;
    this->prev_GyrZ_value = this->curr_GyrZ_value;
    //this->prev_time = curr_time;

    emit this->analyzedDataAvailable();

    // normalizing angles
    this->normalizeAngle();
    qDebug() << curr_GyrY_value << prev_GyrY_value << angleY << gyroYcalli;
    //qDebug() << curr_GyrZ_value << prev_GyrZ_value << angleZ << gyroZcalli;
}

void MainWindow::normalizeAngle()
{
    qDebug() << "updatingxd xd";
    //if(angleY > )
}

void MainWindow::angleToVelocity()
{
    qDebug() << "updatingxd xd";
}

void MainWindow::updateVehicleStatus()
{
    qDebug() << "updatingxd xd";
}

void MainWindow::animateVehicle(qreal x, qreal y, qreal angle)
{
    // variables for single step
    qreal step_x, step_y, step_a;
    step_x = step_y = step_a = 0;

    for (int i = 0; i < 100; i++)
    {
        step_x += x/100.0;
        step_y += y/100.0;
        step_a += angle/100.0;
        animation->setPosAt(i/100.0, QPointF(step_x,step_y) + this->vehicle->pos());
        animation->setRotationAt(i/100.0, step_a + this->rot);
    }

    // setting number of frames
    timer->setFrameRange(0, 100);
    this->scene->update();
    timer->start();

    this->rot += angle;
    if(this->rot > 360.0)
        this->rot -= 360.0;
}

//void MainWindow::moveVehicle(qreal x, qreal y)
//{
//    qreal step_x, step_y;
//    step_x = step_y = 0;

//    //this->vehicle->moveBy(x, y);

//    for (int i = 0; i < 10; i++)
//        animation->setPosAt(i / 200.0, QPointF(i,i) + this->vehicle->pos());

//    this->scene->update();
//    timer->start();
//}

//void MainWindow::rotateVehicle(qreal angle)
//{
//////    QTransform trans(1, 1, 1, 1, 1, 11, 1, 1, 1);
//////    this->vehicle->setTransform(trans);
////    qDebug() << this->vehicle->rotation();
////    this->vehicle->setTransformOriginPoint(QPoint(5,5));
////    //this->vehicle->setPos(50,50);
////    this->vehicle->setRotation(this->vehicle->rotation() + 45);
////    qDebug() << this->vehicle->rotation() << "\n";
////    this->vehicle->update();

//    QGraphicsView *view = new QGraphicsView(scene);
//    view->show();
//    this->scene->update();

//    timer->start();
//    qDebug() << this->vehicle->boundingRect();
//}








