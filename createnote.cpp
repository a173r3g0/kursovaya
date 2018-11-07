#include "createnote.h"
#include "ui_createnote.h"

CreateNote::CreateNote(Diary *d, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateNote)
{
    ui->setupUi(this);
    this->d = d;

    if(d->editFlag != -1) {
        ui->titleEdit->setText(QString::fromStdString(d->notes[d->editFlag].name));
        ui->textEdit->setPlainText(QString::fromStdString(d->notes[d->editFlag].note));
        ui->timeEdit->setTime(d->notes[d->editFlag].time);
        ui->dateEdit->setDate(d->notes[d->editFlag].date);
    }
    else {
        ui->dateEdit->setDate(QDate::currentDate());
        ui->timeEdit->setTime(QTime :: currentTime());
    }
}

CreateNote::~CreateNote()
{
    delete ui;
}

void CreateNote::on_backButton_clicked()
{
    d->show();
    if(d->editFlag != -1) d->calendar_color(d->notes[d->editFlag].date);

    d->hide = true;
    if(d->todayTasksFlag == true && d->hideCompletedFlag == true) {
        d->writeTodayUnchecked();
    } else if(d->todayTasksFlag == true) {
        d->writeToday();
    } else if(d->hideCompletedFlag == true) {
        d->writeUnchecked();
    } else {
        d->write();
    }
    d->hide = false;
    d->editFlag = -1;
    this->close();
}




void CreateNote::on_dateEdit_dateChanged(const QDate &date) // запрет на создание событий в прошлом
{
    if (date < QDate :: currentDate() || (date == QDate::currentDate() && this->ui->timeEdit->time() <= QTime::currentTime())) this->ui->saveNoteButton->setDisabled(true);
        else this->ui->saveNoteButton->setDisabled(false);
}

void CreateNote::on_timeEdit_timeChanged(const QTime &time) // запрет на игры со временем
{
    if (this->ui->dateEdit->date() == QDate::currentDate()) {
        if (time <= QTime::currentTime()) this->ui->saveNoteButton->setDisabled(true);
            else this->ui->saveNoteButton->setDisabled(false);
    } else ui->saveNoteButton->setDisabled(false);

}

void CreateNote::on_saveNoteButton_clicked()
{
    if(d->editFlag != -1 && ui->textEdit->toPlainText() != "" && ui->titleEdit->text() != "") { // Редактирование существующей заметки
        d->notes[d->editFlag].setName(ui->titleEdit->text().toStdString());
        d->notes[d->editFlag].setNote(ui->textEdit->toPlainText().toStdString());
        d->notes[d->editFlag].setTime(ui->timeEdit->time());
        d->notes[d->editFlag].setDate(ui->dateEdit->date());

        std::sort(d->notes.begin(),d->notes.end(),d->ptr);
        on_backButton_clicked();
    }

    else if(ui->textEdit->toPlainText() != "" && ui->titleEdit->text() != "") {
        Note note;
        note.id = d->notes.size();
        note.setName(ui->titleEdit->text().toStdString());
        note.setNote(ui->textEdit->toPlainText().toStdString());
        note.setTime(ui->timeEdit->time());
        note.setDate(ui->dateEdit->date());
        d->notes.push_back(note);

        d->calendar_color(d->notes[d->notes.size()-1].date);
        std::sort(d->notes.begin(),d->notes.end(),d->ptr);
        on_backButton_clicked();


        // сохранение в notes - нужно придумать, как передадим заметку в diary
        // нужно придумать как передать дату в календарь (считывать дату последней созданной заметки?)
    }
}
