#ifndef MAKE_NEW_H
#define MAKE_NEW_H

#include "diary.h"
#include <QWidget>

namespace Ui {
class make_new;
class Diary;
}

class make_new : public QWidget
{
    Q_OBJECT

public:
    explicit make_new(QWidget *parent = nullptr);
    ~make_new();

private slots:
    void on_pushButton_clicked();

private:
    Ui::make_new *ui;
    Ui::Diary *d;
};

#endif // MAKE_NEW_H
