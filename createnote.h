#ifndef CREATENOTE_H
#define CREATENOTE_H

#include "diary.h"
#include <QMainWindow>
#include "note.h"

class Diary;

namespace Ui {
class CreateNote;
}

class CreateNote : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateNote(Diary *d, QWidget *parent = 0);
    ~CreateNote();

private slots:
    void on_backButton_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

    void on_timeEdit_timeChanged(const QTime &time);

    void on_saveNoteButton_clicked();

private:
    Ui::CreateNote *ui;
    Diary *d;
};

#endif // CREATENOTE_H
