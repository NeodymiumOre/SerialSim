#ifndef CHARTWINDOW_HPP
#define CHARTWINDOW_HPP

#include <QDialog>
#include <QtCharts>
#include <QDebug>
#include "chart.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ChartWindow; }
QT_END_NAMESPACE

class ChartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = nullptr);
    ~ChartWindow();

private:
    Ui::ChartWindow *ui;
    Chart *GyrX, *GyrY, *AccX, *AccY;

public slots:
    void beginPlot();

};

#endif // CHARTWINDOW_HPP

