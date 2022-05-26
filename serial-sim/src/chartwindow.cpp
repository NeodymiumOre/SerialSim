#include "chartwindow.hpp"
#include "ui_chartwindow.h"

ChartWindow::ChartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);
}

ChartWindow::~ChartWindow()
{
    delete ui;
}

void ChartWindow::beginPlot()
{
    Chart *chart = new Chart(Qt::blue);
    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    ui->graphicsViewAx->setChart(chart);

    Chart *chart2 = new Chart;
    chart2->setTitle("Dynamic spline chart");
    chart2->legend()->hide();
    chart2->setAnimationOptions(QChart::AllAnimations);
    ui->graphicsViewAy->setChart(chart2);

    Chart *chart3 = new Chart;
    chart3->setTitle("Dynamic spline chart");
    chart3->legend()->hide();
    chart3->setAnimationOptions(QChart::AllAnimations);
    ui->graphicsViewGx->setChart(chart3);

    Chart *chart4 = new Chart;
    chart4->setTitle("Dynamic spline chart");
    chart4->legend()->hide();
    chart4->setAnimationOptions(QChart::AllAnimations);
    ui->graphicsViewGy->setChart(chart4);
}
