#ifndef CHART_H
#define CHART_H

/*!
 * \file
 * \brief Definicja klasy Chart
 *
 * Plik zawiera definicję klasy Chart, która jest odpowiedzialna
 * za implementację wykresów.
 */

#include <QChart>
#include <QTimer>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_END_NAMESPACE

QT_USE_NAMESPACE

/*!
 * \brief Definicja klasy Chart
 *
 * Klasa Chart jest odpowiedzialna za implementację wykresów.
 * Zawiera metody do obsługi ich zachowań takich jak
 * przesuwanie w czasie. Odpowiada także za wygląd wykresów.
 */
class Chart: public QChart
{
    Q_OBJECT

public:

    /*!
     * \brief Konstruktor obiektu klasy Chart
     *
     * Tworzy obiekt klasy Chart
     *
     * \param[in] color - kolor lini na wykresie, domyślny kolor: zielony
     * \param[in] parent - wskaźnik na obiekt klsy rodzica; domyślnie nullptr
     * \param[in] wFlags - lista flag typu WindowFlags
     */
    Chart(Qt::GlobalColor color = Qt::green, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});

    /*!
     * \brief Destruktor obiektu klasy Chart
     *
     * Usuwa obiekt klasy Chart
     */
    virtual ~Chart();

public slots:
    /*!
     * \brief Metoda aktualizująca dane prezentowane na wykresie.
     *
     * Odpowiada za dopisywanie nowych danych do wykresu oraz za przesunięcia osi czasu.
     */
    void handleTimeout();

private:
    /*!
     * \brief Obiekt timera
     *
     * Odpowiada za podstawę czasu do przesuwania wykresów.
     */
    QTimer m_timer;

    /*!
     * \brief Wykres reprezentujący dane
     *
     * Zawiera dane rysowane na wykresie w postaci zaokrąglanej linii.
     */
    QSplineSeries *m_series;

    /*!
     * \brief Oś x wykresu
     *
     * Reprezentuje oś x wykresu.
     */
    QValueAxis *m_axisX;

    /*!
     * \brief Oś y wykresu
     *
     * Reprezentuje oś y wykresu.
     */
    QValueAxis *m_axisY;

    /*!
     * \brief Współrzędna x kolejnego rysowanego punktu
     *
     * Określa położenie na osi x kolejnego punktu rysowanego na wykresie.
     */
    qreal m_x;

    /*!
     * \brief Współrzędna y kolejnego rysowanego punktu
     *
     * Określa położenie na osi y kolejnego punktu rysowanego na wykresie.
     */
    qreal m_y;

    /*!
     * \brief Górny zakres osi x na początkowym wykresie.
     *
     * Określa największą współrzędną x rysowaną na osi x w chwili t=0
     */
    qreal x_range;

    /*!
     * \brief Górny zakres osi y na początkowym wykresie.
     *
     * Określa największą współrzędną y rysowaną na osi x w chwili t=0
     */
    qreal y_range;
};

#endif /* CHART_H */
