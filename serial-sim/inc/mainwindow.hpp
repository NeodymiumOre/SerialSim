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

    /*!
     * \brief Wartość Gy odczytana prosto z urządzenia
     *
     * Przechowuje surową wartość Gy do odczytu dla metody \link Chart::handle::timeout \endlink
     */
    qreal Gy_raw;

    /*!
     * \brief Wartość Gz odczytana prosto z urządzenia
     *
     * Przechowuje surową wartość Gz do odczytu dla metody \link Chart::handleTimeout \endlink
     */
    qreal Gz_raw;

    /*!
     * \brief Licznik cykli kalibracji żyroskopu
     *
     * Przechowuje liczbę cykli pomiarowych wykonanych przez metodę
     * \link MainWindow::callibrateGyroscope \endlink
     */
    int gyro_counter;

    /*!
     * \brief Skumulowane odchylenie kątowe dla obu osi
     *
     * Przechowują wartości skumulowanego odchylenia kątowego dla obu osi żyroskopu.
     */
    qreal angleY, angleZ;

    /*!
     * \brief Prędkość pojazdu w symulacji [mm/s]
     *
     * Przechowują wartości prędkości pojazdu poruszającego się w symulacji.
     * Jadnostką są [mm/s] żeby pojazd co chwilę nie wyskakiwał z okienka symulacji.
     */
    qreal valueV;

    /*!
     * \brief Dryf żyroskopu w obu osiach
     *
     * Przechowują wartości dryfu żyroskopu w obu osiach. Używane są w metodach
     * \link MainWindow::callibrateGyroscope \endlink
     */
    qreal gyroYcalli, gyroZcalli;

    /*!
     * \brief Zmiana czasu do liczenia zmiany przemieszczenia kątowego
     *
     * Zmiana czasu do liczenia zmiany przemieszczenia kątowego w metodzie
     * \link MainWindow::analyzeData \endlink
     */
    qreal prev_time, curr_time;

    /*!
     * \brief Różnica wartości odczytów z osi Y żyroskopu
     *
     * Różnica wartości odczytów z osi Y żyroskopu do liczenia zmiany przemieszczenia
     * kątowego w metodzie \link MainWindow::analyzeData \endlink
     */
    qreal prev_GyrY_value, curr_GyrY_value;

    /*!
     * \brief Różnica wartości odczytów z osi Z żyroskopu
     *
     * Różnica wartości odczytów z osi Z żyroskopu do liczenia zmiany przemieszczenia
     * kątowego w metodzie \link MainWindow::analyzeData \endlink
     */
    qreal prev_GyrZ_value, curr_GyrZ_value;

signals:

    /*!
     * \brief Sygnalizuje
     *
     * Przechowują wartości dryfu żyroskopu w obu osiach. Używane są w metodach
     * \link MainWindow::callibrateGyroscope \endlink
     */
    void analyzedDataAvailable(qreal angleY, qreal angleZ, qreal valueV);

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

    /*!
     * \brief Pojazd rysowany na scenie
     *
     * Wskaźnik na obiekt przechowujący dane o pojeździe wyświetlanym na scenie. Przechowuje
     * wszystkie dane związane z jego wymiarami, położeniem oraz orientacją.
     */
    Vehicle *vehicle;

private slots:

    //************************* UI SECTION *************************

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
     * \brief Metoda resetująca położenie pojazdu w oknie symulacji.
     *
     * Przywraca domyślne położenie oraz orientację pojazdu w oknie symulacji. Oznacza to praktycznie
     * przywrócenie wszystkich zmiennych i obiektów należących do klasy \link Vehicle \endlink do stanu początkowego.
     */
    void on_pushButtonReset_clicked();

    /*!
     * \brief Metoda otwierająca okno zawierające wykresy odczytywanych wartości.
     *
     * Metoda otwiera nowe okno z wykresami wartości odczytywanych z portu szeregowego.
     * Wyświetlane wartości są juz przetworzone
     */
    void on_pushButtonCharts_clicked();

    void print_values(qreal angleY, qreal angleZ, qreal valueV);

    //************************ LOGIC SECTION ************************

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
     * \brief Metoda kalibrująca żyroskop.
     *
     * Odbiera otrzymane z urządzenia dane, sprawdza czy dane są poprawne, a następnie dodaje
     * pomiar do zmiennych, które przechowują dryf w obu osiach. Po 500 odczytach, które trwają
     * ok. 50s metoda przełącza sygnał "readyRead()" do metody \link MainWindow::readFromDevice
     * \endlink
     */
    void callibrateGyroscope();

    /*!
     * \brief Metoda odczytująca dane z portu szeregowego.
     *
     * Odbiera otrzymane z urządzenia dane, sprawdza czy dane są poprawne, a następnie
     *  wyłuskuje potrzebne wartości i przekazuje je do wyświetlenia oraz dalszej analizy.
     */
    void readFromDevice();

    /*!
     * \brief Metoda przeliczająca dane pomiarowe na prędkość oraz położenie pojazdu.
     *
     * Dokonuje przekształcenia odczytanych danych z żyroskopu na wartości prędkości katowych.
     * \link v \endlink, oraz położenie (\link x \endlink, \link y \endlink).
     */
    void analyzeData();

};
#endif // MAINWINDOW_HPP
