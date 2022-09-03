#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtag.h"
#include "search.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    addTag addtag;
    addtag.setModal(true);
    addtag.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    search sear;
    sear.setModal(true);
    sear.exec();
}

