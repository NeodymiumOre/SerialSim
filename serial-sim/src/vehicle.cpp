#include "vehicle.hpp"

static const double Pi = 3.1415;
static double TwoPi = 2.0 * Pi;

Vehicle::Vehicle()
{
    //setFlag(ItemIsMovable);

    _Body.setRect(-50, -20, 100, 60);
    _LUWheel.setRect(-40, 40, 20, 10);
    _LBWheel.setRect(-40, -30, 20, 10);
    _RUWheel.setRect(20, 40, 20, 10);
    _RBWheel.setRect(20, -30, 20, 10);
}

Vehicle::~Vehicle() {}

QRectF Vehicle::boundingRect() const {}

QPainterPath Vehicle::shape() const {}

void Vehicle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(_Body);
    painter->drawRect(_LUWheel);
    painter->drawRect(_LBWheel);
    painter->drawRect(_RUWheel);
    painter->drawRect(_RBWheel);
}



//static qreal normalizeAngle(qreal angle)
//{
//    while (angle < 0)
//        angle += TwoPi;
//    while (angle > TwoPi)
//        angle -= TwoPi;
//    return angle;
//}

//void Vehicle::advance(int step)
//{
//    if (!step)
//        return;
//    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
//    if (lineToCenter.length() > 150) {
//        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
//        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

//        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
//            // Rotate left
//            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
//        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
//            // Rotate right
//            angle += (angle < Pi / 2) ? 0.25 : -0.25;
//        }
//    } else if (::sin(angle) < 0) {
//        angle += 0.25;
//    } else if (::sin(angle) > 0) {
//        angle -= 0.25;
//    }

//    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
//                           << mapToScene(0, 0)
//                           << mapToScene(-30, -50)
//                           << mapToScene(30, -50));

//    for (const QGraphicsItem *item : dangerMice) {
//        if (item == this)
//            continue;

//        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
//        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
//        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

//        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
//            // Rotate right
//            angle += 0.5;
//        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
//            // Rotate left
//            angle -= 0.5;
//        }
//    }

//    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
//        if (QRandomGenerator::global()->bounded(1))
//            angle += QRandomGenerator::global()->bounded(1 / 500.0);
//        else
//            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
//    }

//    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

//    qreal dx = ::sin(angle) * 10;
//    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

//    setRotation(rotation() + dx);
//    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
//}

