#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "entityTable.hpp"
#include "entity.hpp"
#include "cameraentity.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <QModelIndex>

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

    mapper.addMapping(ui->posXLineEdit, 1);
    mapper.addMapping(ui->posYLineEdit, 2);
    mapper.addMapping(ui->posZLineEdit, 3);

        mapper.addMapping(ui->rotXSlider, 4);
        mapper.addMapping(ui->rotYSlider, 5);
        mapper.addMapping(ui->rotZSlider, 6);

    connect(ui->entityTableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
             this, SLOT(onObjectRowChanged(QModelIndex, QModelIndex)));


    connect(&mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(mapperIndexChanged(int)));
}


void MainWindow::mapperIndexChanged(int idx)
{
    qDebug(QString("Mapper index changed slot" + QString::number(idx)).toStdString().c_str());
}

void MainWindow::onObjectRowChanged(QModelIndex idx, QModelIndex prev)
{
    QDataWidgetMapper &mapper = entityTable_->dataMapper();

    qDebug("Prev and curr:");
    qDebug(QString::number(prev.row()).toStdString().c_str());
    qDebug(QString::number(idx.row()).toStdString().c_str());
  //  if (prev.row() >= 0 && prev.column() >= 0)
    //    mapper.submit();
    mapper.setCurrentIndex(idx.row());
    //mapper.revert();

  /*  for (int i = 0; i < entityTable_->columnCount(); ++i)
    {
        if ( QLineEdit *ptr = dynamic_cast<QLineEdit *>(mapper.mappedWidgetAt(i)))
        {
                    ptr->setText(entityTable_->data(idx.sibling(idx.row(), i)).toString());
    }      else  if ( QSlider *ptr = dynamic_cast<QSlider *>(mapper.mappedWidgetAt(i)))
        {
                    ptr->setValue(entityTable_->data(idx.sibling(idx.row(), i)).toInt());
    }
    }*/
   // mapper.setCurrentIndex(idx.row());
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


    Entity *e = new Entity(w, "The Hulk ");
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
    ui->entityTableView->update();
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
