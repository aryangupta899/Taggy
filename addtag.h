#ifndef ADDTAG_H
#define ADDTAG_H

#include <QDialog>

namespace Ui {
class addTag;
}

class addTag : public QDialog
{
    Q_OBJECT

public:
    explicit addTag(QWidget *parent = nullptr);
    ~addTag();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addTag *ui;
};

#endif // ADDTAG_H
