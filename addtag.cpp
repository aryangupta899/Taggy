#include "addtag.h"
#include "ui_addtag.h"
#include "taggy.h"
#include <QFileDialog>
#include <QMessageBox>

QString file_name;

addTag::addTag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTag)
{
    ui->setupUi(this);
}

addTag::~addTag()
{
    delete ui;
}

void addTag::on_pushButton_clicked()
{
    file_name = QFileDialog::getOpenFileName(this,"browse file","C://");
    ui->lineEdit_2->setText(file_name);
    if(file_name.isEmpty()){
        QMessageBox::information(this,"..","Please choose directory carefully!");
    }
}


void addTag::on_pushButton_2_clicked()
{
    QString tag=ui->lineEdit->text();
//    QMessageBox::information(this,"..",file_name+" "+tag);
    Taggy t;
    if(file_name.isEmpty() || tag.isEmpty()){
        QMessageBox::information(this,"..","Please choose directory carefully!");
    }else{
        t.addTag2(file_name.toStdString(),tag.toStdString());
        close();
    }
}


