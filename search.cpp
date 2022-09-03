#include "search.h"
#include "ui_search.h"
#include "taggy.h"
#include <QMessageBox>
#include<algorithm>
#include <QVector>
#include <string>
#include <vector>
using namespace std;
::
search::search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
}

search::~search()
{
    delete ui;
}

void search::on_pushButton_clicked()
{
    QString tag=ui->lineEdit->text();
//    QMessageBox::information(this,"..",tag);
    string sand=" and ";
    string sor=" or ";
    string s1=tag.toStdString();
    ui->listWidget->clear();
    if (s1.find(sand) != std::string::npos) {
        addItemsAnd(s1);
    }

    else if(s1.find(sor)!=std::string::npos){
        addItemsOr(s1);
    }
    else
        addItemsToList(tag);
}

void search::addItemsToList(QString tag){
    Taggy t;
    std::vector<std::string> vec = t.searching(tag.toStdString());
    QVector<QString> qt;
    std::transform(vec.begin(), vec.end(), std::back_inserter(qt), [](const std::string &v){ return QString::fromStdString(v); });
    for(int i=0;i<qt.size();i++){
        ui->listWidget->addItem(qt[i]);
    }
}

void search::addItemsAnd(string tags){
    Taggy t;
    string tag1="";
    string tag2="";
    for(auto x:tags){
        if(x==' ' ){
            break;
        }
        else{
            tag1=tag1+x;
        }
    }

    for (int i = tags.size() - 1; i >= 0; i--) {
        if(tags[i]==' '){
            break;
        }
        else{
            tag2=tags[i]+tag2;
        }
    }

    vector<string> tag1vec=t.searching(tag1);
    vector<string> tag2vec=t.searching(tag2);
    vector<string> vec;

    for(int i=0;i<tag2vec.size();i++){
        if(std::find(tag1vec.begin(), tag1vec.end(), tag2vec[i]) != tag1vec.end()) {
            cout<<tag2vec[i]<<endl;
            vec.push_back(tag2vec[i]);
        }
    }
    QVector<QString> qt;
    std::transform(vec.begin(), vec.end(), std::back_inserter(qt), [](const std::string &v){ return QString::fromStdString(v); });
    for(int i=0;i<qt.size();i++){
        ui->listWidget->addItem(qt[i]);
    }
}


void search::addItemsOr(string tags){
    Taggy t;
    string tag1="";
    string tag2="";
    for(auto x:tags){
        if(x==' ' ){
            break;
        }
        else{
            tag1=tag1+x;
        }
    }

    for (int i = tags.size() - 1; i >= 0; i--) {
        if(tags[i]==' '){
            break;
        }
        else{
            tag2=tags[i]+tag2;
        }
    }
    vector<string> tag1vec=t.searching(tag1);
    vector<string> tag2vec=t.searching(tag2);

    unordered_set <string> resultSet ;
    for(int i=0;i<tag1vec.size();i++){
        resultSet.insert(tag1vec[i]);
    }

    for(int i=0;i<tag2vec.size();i++){
        resultSet.insert(tag2vec[i]);
    }

    QVector<QString> qt;
    std::transform(resultSet.begin(), resultSet.end(), std::back_inserter(qt), [](const std::string &v){ return QString::fromStdString(v); });
    for(int i=0;i<qt.size();i++){
        ui->listWidget->addItem(qt[i]);
    }
}
