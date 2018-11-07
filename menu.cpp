#include "menu.h"
#include "ui_menu.h"
#include <QDir>
#include <qstandardpaths.h>
#include <standart_path.h>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>

Menu::Menu(Diary *d, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->d = d;

}

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

        QStringList Diaries;
        int size;

        check_Diaries(&Diaries);

        size = Diaries.size();

        for(int Counter = 0; size > Counter; Counter++)
        {

            ui->comboBox->addItem(Diaries[Counter]);

        }

}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_lastButton_clicked()
{   
    if(!d) {
        Diary *di = new Diary;
        di->show();

        this->close();
    }
    else {
        d->show();

        this->close();
    }
}

void Menu::on_exitButton_clicked() {
    QMessageBox exit(QMessageBox::Question,
                tr("Выход"),
                tr("Вы действительно хотите выйти?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
        exit.setButtonText(QMessageBox::Yes, tr("Действительно хочу!"));
        exit.setButtonText(QMessageBox::No, tr("НЕТ!"));

    if (exit.exec() == QMessageBox::Yes){
        QApplication::exit();
    }
}

void Menu::on_opencurrent_button_clicked()
{
    QString NameDiary = ui->comboBox->currentText();
    make_cfg(NameDiary);
    if(!d) {
        Diary *di = new Diary;
        di->show();

        this->close();
    }
    else {
        d->show();

        this->close();
    }
}

void Menu::on_importButton_clicked()
{
    QString Standart_path,path;
    standart_paths(&Standart_path);
    Standart_path.replace("//","/");
    path = "file://" + Standart_path;
    QDesktopServices::openUrl(QUrl(path));
}

void Menu::on_createButton_clicked()
{

}
