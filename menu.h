#ifndef MENU_H
#define MENU_H

#include "diary.h"
#include <QMainWindow>
#include "make_new.h"


class Diary;
namespace Ui {
class Menu;
class make_new;
}

class Menu : public QMainWindow
{
    Q_OBJECT
friend class Diary;
public:
    explicit Menu(Diary *d, QWidget *parent = 0);
    Menu (QWidget *parent = 0);
    ~Menu();

private slots:

    void on_lastButton_clicked();

    void on_exitButton_clicked();

    void on_opencurrent_button_clicked();

    void on_importButton_clicked();

    void on_createButton_clicked();

private:
    Ui::Menu *ui;
    Diary *d;
    Ui::make_new *make;
};

#endif // MENU_H
