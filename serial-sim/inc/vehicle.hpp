#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>

class Vehicle : public QGraphicsItem
{
public:
    Vehicle();
    virtual ~Vehicle() {};

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
   // void advance(int step) override;

private:
    QRectF _Body, _LUWheel, _LBWheel, _RUWheel, _RBWheel;
};

#endif // VEHICLE_HPP
