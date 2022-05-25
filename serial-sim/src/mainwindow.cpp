#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "chart.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // instead of: delete device;
    this->device = new QSerialPort(this);

    //scene setup
    this->scene = new QGraphicsScene(this);
    ui->graphicsViewPlane->setScene(scene);

    // adding vehicle to the scene
    this->vehicle = new Vehicle();
    this->scene->addItem(this->vehicle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToLogs(QString message)
{
    QString currDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(currDateTime + "\t" + message);
}

void MainWindow::readFromDevice()
{
        while(this->device->canReadLine())
        {
            int init, work, butt;
            float Ax, Ay, Gx, Gy;
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
                Ax = line.mid(5, char_num).toFloat();
                // getting index of next " " after 6th pos
                int ay_pos = line.indexOf(" ", 6) + 1;
                // getting 5 chars from next " " char
                Ay = line.mid(ay_pos, 5).toFloat();
                // getting index of next " " after ay_pos
                int gx_pos = line.indexOf(" ", ay_pos) + 1;
                // getting 5 chars from next " " char
                Gx = line.mid(gx_pos, 5).toFloat();
                // getting index of next " " after gx_pos
                int gy_pos = line.indexOf(" ", gx_pos) + 1;
                // getting 5 chars from next " " char
                Gy = line.mid(gy_pos, 5).toFloat();

                qDebug() << Ax << Ay << Gx << Gy;
            }
            else
            {
                qDebug() << "Broken";
            }

        }
}

void MainWindow::sceneSetup()
{
    qDebug() << "xd";
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
        connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromDevice()));
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

void MainWindow::on_pushButtonStart_clicked()
{
    this->sceneSetup();
}

void MainWindow::on_pushButtonCharts_clicked()
{
    ChartWindow GyrXWin(nullptr);
    GyrXWin.setModal(true);

    GyrXWin.beginPlot();

    GyrXWin.exec();
    this->show();
}











