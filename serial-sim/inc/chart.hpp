#ifndef CHART_H
#define CHART_H

#include <QChart>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class Chart: public QChart
{
    Q_OBJECT

public:
    Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    virtual ~Chart();

public slots:
    void handleTimeout();

private:
    QTimer m_timer;
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal m_step;
    qreal m_x;
    qreal m_y;
};

#endif /* CHART_H */
