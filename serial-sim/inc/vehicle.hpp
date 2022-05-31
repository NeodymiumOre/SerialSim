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

    /*!
     * \brief Konstruktor obiektu klasy Vehicle
     *
     * Tworzy obiekt klasy Vehicle
     */
    Vehicle();

    /*!
     * \brief Destruktor obiektu klasy Vehicle
     *
     * Usuwa obiekt klasy Vehicle
     */
    virtual ~Vehicle();

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    /*!
     * \brief Metoda odpowiadająca za rysowanie pojazdu.
     *
     * Wyrysowuje obiekt pojazdu jako całości na ekranie symulacji.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void calculatePositionSpeed(qreal angleY, qreal angleZ, qreal valueV);

protected:
   // void advance(int step) override;

private:

    /*!
     * \brief Elementy składowe graficznej reprezentacji pojazdu
     *
     * Obiekty reprezentują poszczególne elementy graficzne pojazdu.
     * Obiekt _Body reprezentuje korpus pojazdu, natomiast pozostałe obiekty reprezentują
     * koła (L - left, R - right, U - up, B - bottom).
     */
    QRectF _Body, _LUWheel, _LBWheel, _RUWheel, _RBWheel;

    qreal x, y, v;
};

#endif // VEHICLE_HPP
