#include "chart.hpp"

Chart::Chart(Qt::GlobalColor color, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_x(1),
    m_y(5),
    x_range(10),
    y_range(10)
{
    // sender, signal, receiver, slot
    // when timer times out, handleTimeout slot is activated
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);

    // setting time between data points drawing (ms)
    m_timer.setInterval(1000);

    // creates new spline series
    m_series = new QSplineSeries(this);

    // setting up line properties
    QPen pen(color);
    pen.setWidth(3);
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

    // sets ranges for both axes
    m_axisX->setRange(0, x_range);
    m_axisY->setRange(0, y_range);

    // starts timer count
    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    // calculating x axis shift in pixels
    qreal x = plotArea().width() / (m_axisX->tickCount()-1);
    // calculating x xis shift in seconds
    qreal y = (m_axisX->max() - m_axisX->min()) / (m_axisX->tickCount() - 1);

    // set next x value on the axis to draw on
    m_x += y;

    // choosing new random value
    m_y = QRandomGenerator::global()->bounded(5);
    // adding new value to the plot
    m_series->append(m_x, m_y);

    // shifts the x axis if it is bigger then initial range
    if(m_x > x_range) scroll(x, 0);
}
