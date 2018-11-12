#include "make_new.h"
#include "ui_make_new.h"
#include <QString>
#include "diary.h"
#include "alternative_save_load.h"

make_new::make_new(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::make_new)
{
    ui->setupUi(this);
    setWindowTitle("Create new");
}

make_new::~make_new()
{
    delete ui;
}

void make_new::on_pushButton_clicked()
{
    QString NameDiary = ui->lineEdit->text();
    Save_load file;
    file.make_config(NameDiary);
    file.make_dir(NameDiary);

    Diary *diary = new Diary();
    diary->show();
    close();
}
