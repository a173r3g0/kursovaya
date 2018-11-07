#ifndef DIARY_H
#define DIARY_H

#include "note.h"
#include "menu.h"
#include "createnote.h"
#include <QMainWindow>
#include <vector>
#include <QListWidget>
#include <QMessageBox>
#include <string>
#include <QDebug>
#include "createnote.h"
#include <algorithm>

namespace Ui {
class Diary;
}

class Diary : public QMainWindow
{
    Q_OBJECT

public:
    explicit Diary(QWidget *parent = 0);
    static bool sorting (Note one, Note two);
    bool (*ptr) (Note one, Note two) = &sorting;
    ~Diary();

friend class CreateNote;

private slots:
    void setData(int i);

    void getData(int i);

    void write();

    void writeUnchecked();

    void writeTodayUnchecked();

    void writeToday();

    int getIndex(std::string);

    void calendar_color (QDate date);

    bool day_is_empty(QDate &date);

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

    void on_editButton_clicked();

    void on_taskList_itemDoubleClicked();

    void on_hideCompleted_stateChanged(int arg1);

    void on_taskList_itemChanged(QListWidgetItem *item);

    //void on_calendar_clicked(const QDate &date);

    void on_todayTasks_stateChanged(int arg1);

    void on_instruction_triggered();

    void on_exit_triggered();

    //void on_timeEdit_timeChanged(const QTime &time);

    void on_menuButton_clicked();

    void on_newNoteButton_clicked();

    void on_taskList_itemClicked(QListWidgetItem *item);

    void on_clearTextButton_clicked();

    void on_clearTasksButton_clicked();

private:
    Ui::Diary *ui;
    std::vector <Note> notes;           // Все заметки
    int editFlag = -1;                  // Флаг редактирования, содержит номер редактируемой заметки или значение = -1
    bool hide = false;                  // Успокаивает обработчик событий на листе
    bool hideCompletedFlag = false;     // Флаг поднят, при галочке на "Скрыть выполненные"
    bool todayTasksFlag = false;        // Флаг поднят, при галочке на "Показать сегодняшние"
    QString name;
    QString note;
    QString date;
    QString time;
    QString id;
};


#endif // DIARY_H
