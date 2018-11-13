#include "menu.h"
#include "ui_menu.h"
#include <QDir>
#include <qstandardpaths.h>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <alternative_save_load.h>

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
        Save_load File;

        File.checkDiaries(&Diaries);

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
        Diary *di = new Diary(this);
        di->show();
        this->close();
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
    int id = ui->comboBox->currentIndex();
    QStringList Diaries;
    Save_load File;
    File.checkDiaries(&Diaries);
    //QString NameDiary = ui->comboBox->currentIndex();
    File.make_config(Diaries[id]);
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << Diaries[id];

        Diary *di = new Diary(this);
        di->show();

        this->close();

}

void Menu::on_importButton_clicked()
{
    QString Standart_path,path;
    Save_load File;

    File.standart_path(&Standart_path);
    Standart_path.replace("//","/");
    path = "file://" + Standart_path;
    QDesktopServices::openUrl(QUrl(path));
}

void Menu::on_createButton_clicked()
{
    make_new *make = new make_new(this);
    make->show();
    close();
}
