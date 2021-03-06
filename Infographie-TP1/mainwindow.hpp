#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QModelIndex>
#include <QItemSelection>

#include <irrlicht/irrlicht.h>

class EntityTable;
class QIrrlichtWidget;
namespace Ui
{
    class MainWindow;
}

class Entity;

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

    void addObjectAndSelect(Entity *e);

public:

        bool eventFilter(QObject *target, QEvent *event);
    /**
      This is used by the QIrrlichtWidget to set the selected entity when doing raycasting.
     * @brief setSelectedEntity
     */
    void setSelectedEntity(Entity *e);
    /**
      This is used by the QIrrlichtWidget to set the selected entity when doing raycasting.
     * @brief setSelectedEntity
     */
    void setSelectedNode(irr::scene::ISceneNode *n);
private slots:
    void initIrrlicht();
    /**
     * @brief When irrlicht is initiallized;
     */
    void onIrrlichtInit(QIrrlichtWidget *);
    void on_actionImporter_un_objet_triggered();

    void onObjectRowChanged(QModelIndex idx, QModelIndex prev);
    void on_rotXSlider_valueChanged(int value);
    void on_rotYSlider_valueChanged(int value);
    void on_rotZSlider_valueChanged(int value);

    void on_actionSphere_triggered();
    void on_actionCube_triggered();
    void on_loadTextureButton_clicked();
    void on_posXSpinBox_valueChanged(double arg1);
    void on_posYSpinBox_valueChanged(double arg1);
    void on_posZSpinBox_valueChanged(double arg1);
    void on_actionTake_triggered();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_HPP
