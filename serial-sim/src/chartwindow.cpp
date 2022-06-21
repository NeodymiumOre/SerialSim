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
    chart->setTitle(tr("Surowe odczyt żyroskopu osi Y"));
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(300);
    ui->graphicsViewGy->setChart(chart);

    Chart *chart2 = new Chart(this->Gz_raw, Qt::green);
    chart2->setTitle(tr("Surowe odczyt żyroskopu osi Z"));
    chart2->legend()->hide();
    chart2->setAnimationOptions(QChart::SeriesAnimations);
    chart2->setAnimationDuration(300);
    ui->graphicsViewGz->setChart(chart2);
}
