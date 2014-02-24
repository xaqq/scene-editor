#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(1, this, SLOT(initIrrlicht()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initIrrlicht()
{ui->irrlichtWidget->init();
}
