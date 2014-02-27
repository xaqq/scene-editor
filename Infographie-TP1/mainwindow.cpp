#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "entityTable.hpp"
#include "entity.hpp"
#include "cameraentity.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <QModelIndex>
#include <QInputDialog>
#include "animatedentity.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    entityTable_(new EntityTable(this))
{
    ui->setupUi(this);
    QTimer::singleShot(1, this, SLOT(initIrrlicht()));

    connect(ui->irrlichtWidget, SIGNAL(onInit(QIrrlichtWidget*)), SLOT(onIrrlichtInit(QIrrlichtWidget*)));
    ui->entityTableView->setModel(entityTable_);
            setupFormDataMapper();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupFormDataMapper()
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();

    mapper.addMapping(ui->objectNameLineEdit, 0);

    mapper.addMapping(ui->posXSpinBox, 1);
    mapper.addMapping(ui->posYSpinBox, 2);
    mapper.addMapping(ui->posZSpinBox, 3);

        mapper.addMapping(ui->rotXSlider, 4);
        mapper.addMapping(ui->rotYSlider, 5);
        mapper.addMapping(ui->rotZSlider, 6);

        mapper.addMapping(ui->scaleXLineEdit, 7);
        mapper.addMapping(ui->scaleYLineEdit, 8);
        mapper.addMapping(ui->scaleZLineEdit, 9);
    connect(ui->entityTableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
             this, SLOT(onObjectRowChanged(QModelIndex, QModelIndex)));


    connect(&mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(mapperIndexChanged(int)));
}


void MainWindow::mapperIndexChanged(int idx)
{
  //  qDebug(QString("Mapper index changed slot" + QString::number(idx)).toStdString().c_str());
}

void MainWindow::onObjectRowChanged(QModelIndex idx, QModelIndex prev)
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();
    mapper.setCurrentIndex(idx.row());
}

void MainWindow::initIrrlicht()
{
    ui->irrlichtWidget->init();
}

void MainWindow::onIrrlichtInit(QIrrlichtWidget *w)
{

    Entity *camera = new CameraEntity(w, "Camera");

    camera->buildNode();
    entityTable_->insert(camera);


    Entity *e = new AnimatedEntity(w, "The Hulk ");
    e->loadMesh("/home/xaqq/Documents/Infographie/Infographie-TP1/resources/Hulk/Hulk.obj");

    e->buildNode();
    e->loadTexture("/home/xaqq/Documents/Infographie/Infographie-TP1/resources/Hulk/Hulk_body_diff.tga");
    entityTable_->insert(e);

}

void MainWindow::on_actionImporter_un_objet_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Create from model"),
                                                     "");
    qDebug(fileName.toStdString().c_str());

    Entity *e = new Entity(ui->irrlichtWidget, "Newly created entity");
    if (!e->loadMesh(fileName))
    {
        delete e;
        QMessageBox::critical(this, "Error loading mesh", "An error occured creating object from your file.");
    return;
    }
        if (!e->buildNode())
     {
            delete e;
            QMessageBox::critical(this, "Error loading mesh", "An error occured creating building your node.");
    return ;
        }
    entityTable_->insert(e);

}

void MainWindow::on_rotXSlider_valueChanged(int value)
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();
    mapper.submit();
}

void MainWindow::on_rotYSlider_valueChanged(int value)
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();
    mapper.submit();
}

void MainWindow::on_rotZSlider_valueChanged(int value)
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();
    mapper.submit();
}

void MainWindow::on_actionSphere_triggered()
{
    Entity *e = new Entity(ui->irrlichtWidget, "Newly created sphere");

    bool ok;
    double radius = QInputDialog::getDouble(this, "Rayon de la sphere", "valeur (ne peut pas etre change plus tard) ", 3, -21474883647, 2147483647, 1, &ok);

    if (!ok)
        return;
    IMesh *mesh = ui->irrlichtWidget->getSceneManager()->getGeometryCreator()->createSphereMesh(radius);

    if (!mesh)
    {
        delete e;
       QMessageBox::critical(this, "Error creating mesh", "An error occured while creating a sphere mesh, sorry :(");
       return ;
    }

    e->setMesh(mesh);
    e->buildNode();

    entityTable_->insert(e);
    ui->entityTableView->selectRow(entityTable_->rowCount() - 1);
}

void MainWindow::on_actionCube_triggered()
{

    Entity *e = new Entity(ui->irrlichtWidget, "Newly created cube");

    bool ok;
    double x = QInputDialog::getDouble(this, "Creation de cube (1/3)", "x (ne peut pas etre change)", 3, -21474883647, 2147483647, 1, &ok);
    if (!ok)
        return;
    double y = QInputDialog::getDouble(this, "Creation de cube (2/3)", "y (ne peut pas etre change)", 3, -21474883647, 2147483647, 1, &ok);
    if (!ok)
        return;
    double z = QInputDialog::getDouble(this, "Creation de cube (3/3)", "z (ne peut pas etre change)", 3, -21474883647, 2147483647, 1, &ok);
    if (!ok)
        return;

    IMesh *mesh = ui->irrlichtWidget->getSceneManager()->getGeometryCreator()->createCubeMesh(irr::core::vector3df(x, y, z));

    if (!mesh)
    {
        delete e;
       QMessageBox::critical(this, "Error creating mesh", "An error occured while creating a cube mesh, sorry :(");
       return ;
    }

    e->setMesh(mesh);
    e->buildNode();

    entityTable_->insert(e);
    ui->entityTableView->selectRow(entityTable_->rowCount() - 1);
}

void MainWindow::on_loadTextureButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Texture"),
                                                     "");
    qDebug(fileName.toStdString().c_str());

    Entity *e = entityTable_->getEntityAt(entityTable_->dataMapper().currentIndex());
        if (!e->loadTexture(fileName))
     {
            QMessageBox::critical(this, "Error loading texture", "An error occured applying texture.");
    return ;
        }
}

void MainWindow::on_posXSpinBox_valueChanged(double arg1)
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();
    mapper.submit();
}

void MainWindow::on_posYSpinBox_valueChanged(double arg1)
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();
    mapper.submit();
}

void MainWindow::on_posZSpinBox_valueChanged(double arg1)
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();
    mapper.submit();
}
