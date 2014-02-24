#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "entityTable.hpp"
#include "entity.hpp"
#include "cameraentity.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    entityTable_(new EntityTable(this))
{
    ui->setupUi(this);
    QTimer::singleShot(1, this, SLOT(initIrrlicht()));

    connect(ui->irrlichtWidget, SIGNAL(onInit(QIrrlichtWidget*)), SLOT(onIrrlichtInit(QIrrlichtWidget*)));

    ui->entityTableView->setModel(entityTable_);
}

MainWindow::~MainWindow()
{
    delete ui;
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
