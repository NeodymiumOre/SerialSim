#include "vehicle.hpp"

static const double Pi = 3.1415;
static double TwoPi = 2.0 * Pi;

Vehicle::Vehicle()
{
    setFlag(ItemIsMovable);

    _Body.setRect(-50, -30, 100, 60);
    _LUWheel.setRect(-40, 30, 20, 10);
    _LBWheel.setRect(-40, -40, 20, 10);
    _RUWheel.setRect(20, 30, 20, 10);
    _RBWheel.setRect(20, -40, 20, 10);
}

Vehicle::~Vehicle() {}

QRectF Vehicle::boundingRect() const
{
    return QRectF(-100, -100, 200, 200);
}

QPainterPath Vehicle::shape() const {}

void Vehicle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(_Body);
    painter->drawRect(_LUWheel);
    painter->drawRect(_LBWheel);
    painter->drawRect(_RUWheel);
    painter->drawRect(_RBWheel);
}

void Vehicle::advance(int step)
{
    update();
}

