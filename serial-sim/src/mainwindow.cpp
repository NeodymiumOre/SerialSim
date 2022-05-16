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
        QString line = this->device->readLine();
        //this->addToLogs(line);
        qDebug() << line;

        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        qDebug() << line.left(pos);

        this->addToLogs(line.left(pos));
    }
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
    qDebug() << "xd";
    //this->vehicleSetup();
}

void MainWindow::on_pushButtonCharts_clicked()
{
    ChartWindow GyrXWin(nullptr);
    GyrXWin.setModal(true);

    GyrXWin.beginPlot();

    GyrXWin.exec();
    this->show();
}











