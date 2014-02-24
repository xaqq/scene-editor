#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class EntityTable;
class QIrrlichtWidget;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EntityTable *entityTable_;

private slots:
    void initIrrlicht();
    /**
     * @brief When irrlicht is initiallized;
     */
    void onIrrlichtInit(QIrrlichtWidget *);
};

#endif // MAINWINDOW_HPP
