#include "chartwindow.hpp"
#include "ui_chartwindow.h"

ChartWindow::ChartWindow(qreal *Gy_raw, qreal *Gz_raw, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartWindow),
    Gy_raw(Gy_raw),
    Gz_raw(Gz_raw)
{
    ui->setupUi(this);
}

ChartWindow::~ChartWindow()
{
    delete ui;
}

void ChartWindow::beginPlot()
{
    Chart *chart = new Chart(this->Gy_raw, Qt::blue);
    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    ui->graphicsViewGy->setChart(chart);

    Chart *chart2 = new Chart(this->Gz_raw, Qt::green);
    chart2->setTitle("Dynamic spline chart");
    chart2->legend()->hide();
    chart2->setAnimationOptions(QChart::AllAnimations);
    ui->graphicsViewGz->setChart(chart2);
}
