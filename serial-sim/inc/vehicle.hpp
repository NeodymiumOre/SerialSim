#ifndef VEHICLE_HPP
#define VEHICLE_HPP

/*!
 * \file
 * \brief Definicja klasy Vehicle
 *
 * Plik zawiera definicję klasy Vehicle, która reprezentuje pojazd oraz zawiera
 * wszystkie metody potrzebne do symulowania jego ruchu w oknie symulacji.
 */

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>


/*!
 * \brief Definicja klasy Vehicle
 *
 * Klasa Vehicle reprezentuje symulowany pojazd.
 * Zawiera metody do obsługi transformacji obiektu podczas ruchu.
 */
class Vehicle : public QGraphicsItem
{
public:
    Vehicle();

    virtual ~Vehicle();

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
   // void advance(int step) override;

private:
    QRectF _Body, _LUWheel, _LBWheel, _RUWheel, _RBWheel;
};

#endif // VEHICLE_HPP
