#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QModelIndex>
#include <QItemSelection>

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
    void setupFormDataMapper();

private slots:
    void initIrrlicht();
    /**
     * @brief When irrlicht is initiallized;
     */
    void onIrrlichtInit(QIrrlichtWidget *);
    void on_actionImporter_un_objet_triggered();

    void onObjectRowChanged(QModelIndex idx);
};

#endif // MAINWINDOW_HPP
