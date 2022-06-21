#include "chart.hpp"

Chart::Chart(qreal *data, Qt::GlobalColor color,
             QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_x(0),
    m_y(0),
    x_range(100),
    y_range(600),
    data(data)
{
    // sender, signal, receiver, slot
    // when timer times out, addData slot is activated
    QObject::connect(&add_timer, &QTimer::timeout, this, &Chart::addData);
    // when timer times out, scrollArea slot is activated
    QObject::connect(&scroll_timer, &QTimer::timeout, this, &Chart::scrollArea);

    // setting time between time interrupts (ms)
    scroll_timer.setInterval(1000);
    add_timer.setInterval(100);

    // creates new spline series
    m_series = new QLineSeries(this);

    // setting up line properties
    QPen pen(color);
    pen.setWidth(2);
    m_series->setPen(pen);

    // adds the data point with the coordinates x and y to the series
    // in practice starts drawing line from (m_x, m_y)
    m_series->append(m_x, m_y);

    // ???
    addSeries(m_series);

    // adding x and y axes
    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    // drawing 11 vertical lines in the plot area
    m_axisX->setTickCount(11);
    m_axisY->setTickCount(13);

    // setting axes labels
    m_axisX->setTitleText(tr("czas [s]"));
    m_axisY->setTitleText(tr("prędkość kątowa [st/s]"));

    // sets ranges for both axes
    m_axisX->setRange(0, x_range);
    m_axisY->setRange(y_range*(-1), y_range);

    // starts timers count
    add_timer.start();
    scroll_timer.start();
}

Chart::~Chart()
{

}

void Chart::scrollArea()
{
//    //
//    qreal x = plotArea().width() / 10;
//    //
//    qreal y = 1;//(m_axisX->max() - m_axisX->min()) / (m_axisX->tickCount() - 1);

//    // set next x value on the axis to draw on
//    //m_x += y;

//    // adding new value to the plot
//    //m_series->append(m_x, *data);

//    //
//    if(m_x >= 0.9*x_range) scroll(x, 0);
    qreal x = plotArea().width() / 100;
    if(m_x >= 0.95*x_range) scroll(x, 0);
}

void Chart::addData()
{
    m_x += 0.1;
    m_series->append(m_x, *data);
    *data = 0;

    //qreal x = plotArea().width() / 1000;
    //if(m_x >= 0.9*x_range) scroll(x, 0);


}
