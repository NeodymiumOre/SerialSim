#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

/*!
 * \file
 * \brief Definicja klasy MainWindow
 *
 * Plik zawiera definicję klasy MainWindow, która
 * jest odpowiedzialna za obsugę głównego okna programu
 * SerialSim.
 */

#include <QMainWindow>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QSerialPort>
#include <QGraphicsView>
#include <QDebug>

#include "chartwindow.hpp"
#include "vehicle.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Definicja klasy MainWindow
 *
 * Klasa MainWindow odpowiada za główne okno programu SerialSim.
 * Zawiera metody do obsługi jego poszczególnych elementów graficznych
 *  (przyciski, pola tekstowe, etc) oraz metody pomocnicze do obsługi
 *  logiki programu.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief Konstruktor obiektu klasy MainWindow
     *
     * Tworzy obiekt klasy MainWindow
     *
     * \param[in] parent - wskaźnik na obiekt klsy rodzica; domyślnie nullptr
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief Destruktor obiektu klasy MainWindow
     *
     * Usuwa obiekt klasy MainWindow
     */
    ~MainWindow();

private:
    /*!
     * \brief Interfejs graficzny okna głównego programu
     *
     * Interfejs zawiera wszystkie obiekty graficzne wyświetlane w oknie głównym.
     */
    Ui::MainWindow *ui;

    /*!
     * \brief Urządzenie, z którym komunikuje się aplikacja
     *
     * Wskaźnik na obiekt przechowujący dane o urządzeniu współpracyjącym z
     *  aplikacją. Inicjalizowany w konstruktorze \link MainWindow::MainWindow() \endlink
     */
    QSerialPort *device;
    /*!
     * \brief Scena graficzna do wyświetlania symulowanego pojazdu.
     *
     * Wskaźnik na obiekt przechowujący dane o scenie graficznej, która odpowiada za wyświetlanie
     * pojazdu w oknie symulacji.
     */
    QGraphicsScene *scene;
    QGraphicsItem *vehicle;

private slots:
    /*!
     * \brief Metoda wyświetlająca dane w obiekcie ui->textEditLogs
     *
     * Wyświetla przekazany tekst w polu tekstowym, które przechowuje wszystkie wyświetlane komunikaty aplikacji.
     * Służy do wyświetlania tychże komunikatów dla użytkownika.
     *
     * \param[in] message - treść komunikatu do wyświetlenia
     */
    void addToLogs(QString message);

    /*!
     * \brief Metoda odczytująca dane z portu szeregowego.
     *
     * Odbiera otrzymane z urządzenia dane, sprawdza czy dane są poprawne, a następnie
     *  wyłuskuje potrzebne wartości i przekazuje je do wyświetlenia oraz dalszej analizy.
     */
    void readFromDevice();

    void sceneSetup();

    /*!
     * \brief Metoda wyszukująca podłączone urządzenia w portch szeregowych.
     *
     * Wyszukuje porty szeregowe, które można otworzyć oraz wyświetla je w ui->comboBoxDevices.
     */
    void on_pushButtonSearch_clicked();

    /*!
     * \brief Metoda otwierająca wybrany port szeregowy.
     *
     * Metod próbuje otworzyć port szeregowy wybrany w ui->comboBoxDevices. Sprawdza, czy
     * zostały znalezione jakieś porty szeregowe, czy wybrany port nie został już otwarty, a
     * następnie dokonuje próby otwarcia. Jeśli próba się powiedzie ustawione zostają parametry
     * połączenia oraz wypisany zostanie stosowny komunikat. Jeśli port nie zostanie otwarty zostanie
     * tylko wypisany komunikat.
     */
    void on_pushButtonConnect_clicked();

    /*!
     * \brief Metoda zamykająca wybrany port szeregowy.
     *
     * Sprawdza, czy port był otwarty, jeśli tak to go zamyka. W każdym przypadku wypisuje odpowiedni kounikat.
     */
    void on_pushButtonDisconnect_clicked();

    /*!
     * \brief Na razie nic nie robi xd
     *
     * xdxd
     */
    void on_pushButtonStart_clicked();

    /*!
     * \brief Metoda otwierająca okno zawierające wykresy odczytywanych wartości.
     *
     * Metoda otwiera nowe okno z wykresami wartości odczytywanych z portu szeregowego.
     * Wyświetlane wartości są juz przetworzone
     */
    void on_pushButtonCharts_clicked();

};
#endif // MAINWINDOW_HPP
