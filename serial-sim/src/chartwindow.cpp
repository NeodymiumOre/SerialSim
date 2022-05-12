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
    Chart *chart = new Chart;
    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    ui->graphicsView->setChart(chart);
}
