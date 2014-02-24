#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "entityTable.hpp"
#include "entity.hpp"

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
{ui->irrlichtWidget->init();
}

void MainWindow::onIrrlichtInit(QIrrlichtWidget *w)
{

    entityTable_->insert(new Entity("Test"));

}
