#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QSerialPort>
#include <QGraphicsView>
#include <QDebug>

#include "chartwindow.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QSerialPort *device;
    QGraphicsScene *scene;

private slots:
    void addToLogs(QString message);
    //void readFromPort();

    void on_pushButtonSearch_clicked();
    void on_pushButtonConnect_clicked();
    void on_pushButtonDisconnect_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonCharts_clicked();

};
#endif // MAINWINDOW_HPP
