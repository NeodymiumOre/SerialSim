#ifndef CHARTWINDOW_HPP
#define CHARTWINDOW_HPP

/*!
 * \file
 * \brief Definicja klasy ChartWindow
 *
 * Plik zawiera definicję klasy ChartWindow, która jest odpowiedzialna
 * za wyświetlanie okna zawierającego wykresy.
 */

#include <QDialog>
#include <QtCharts>
#include <QDebug>
#include "chart.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ChartWindow; }
QT_END_NAMESPACE

/*!
 * \brief Definicja klasy ChartWindow
 *
 * Klasa ChartWindow odpowiada za wyświetlanie okna z wykresami.
 * Zawiera metodę do inicjalizacji wykresów. Przechowuje także same
 * widgety wykresów jako obiekty prywatne.
 */
class ChartWindow : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief Konstruktor obiektu klasy ChartWindow
     *
     * Tworzy obiekt klasy ChartWindow
     *
     * \param[in] parent - wskaźnik na obiekt klsy rodzica; domyślnie nullptr
     */
    explicit ChartWindow(qreal *Gy_raw, qreal *Gz_raw, QWidget *parent = nullptr);

    /*!
     * \brief Destruktor obiektu klasy ChartWindow
     *
     * Usuwa obiekt klasy ChartWindow
     */
    ~ChartWindow();

private:

    /*!
     * \brief Interfejs graficzny okna z wykresami
     *
     * Interfejs zawiera wszystkie wykresy rysowane w oknie.
     */
    Ui::ChartWindow *ui;

    /*!
     * \brief Wykresy poszczególnych wartości
     *
     * Obiekty reprezentują wykresy danych przychodzących z urządzenia
     * zewnętrznego. Obiektów jest tyle ile różnych danych.
     */
    Chart *GyrY, *GyrZ;

    qreal *Gy_raw, *Gz_raw;

public slots:

    /*!
     * \brief Metoda inicjalizująca wykresy.
     *
     * Metoda odpowiada za wywołanie konstruktorów klasy \link Chart \endlink oraz za
     * ustawienie tytułów wykresów, koloru lini oraz innych parametrów wyświetlania.
     */
    void beginPlot();

};

#endif // CHARTWINDOW_HPP

