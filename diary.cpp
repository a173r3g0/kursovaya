#include "diary.h"
#include "ui_diary.h"
#include "note.h"
//#include "save_load.h"
#include <QStringList>
#include <QVector>
#include <QDebug>
#include <alternative_save_load.h>

Diary::Diary(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Diary)
{

    ui->setupUi(this);

    Save_load file;

    QString config;
    file.load_config(&config);
    setWindowTitle(config); // связать зарузку с функцией write, чтобы не ломались чекстэйты и календарь
                            //(добавить закрашивание календаря во врайте
    QString Path;
    file.standart_path(&Path);
    Path = Path + "//" + config + "//data.tfd";
    QStringList N0te,Date,Time,Name;
    QList<int>Check;
    file.load_file(Path,&Date,&N0te,&Time,&Name,&Check);

    int size = Date.size();
    qDebug() << "size" << size;

    for(int n = 0; n < size; n++)
    {
        Note n0;
        notes.push_back(n0);

        notes[n].note = N0te[n].toStdString();
        qDebug() << QString::fromStdString(notes[n].note);
        qDebug() << "NOTE" << n << "-----" << N0te[n];
        qDebug() << "NOTE-------------------------------------------------------";


        notes[n].name = Name[n].toStdString();
        qDebug() << QString::fromStdString(notes[n].name);
        qDebug() << "NAME" << n << "-----" << Name[n];
        qDebug() << "NAME-------------------------------------------------------";


        notes[n].time = QTime::fromString(Time[n], "hh:mm");
        qDebug() << notes[n].time;
        qDebug() << "TIME" << n << "-----" << Time[n];
        qDebug() << "TIME-------------------------------------------------------";


        notes[n].date = QDate::fromString(Date[n], "dd.MM.yyyy");
        qDebug() << notes[n].date;
        qDebug() << "DATE" << n << "-----" << Date[n];
        qDebug() << "DATE-------------------------------------------------------";

        notes[n].completeFlag = Check[n];
    }

    ui->hideCompleted->setCheckState(Qt::Checked);
    ui->hideCompleted->setCheckState(Qt::Unchecked);
    //write();

}

Diary::~Diary()
{
    delete ui;
}

//ФУНКЦИИ ТУТ--------------------------------------------------------------------------------------------------------------
void Diary::setData(int i) {
    name = QString::fromStdString(notes[i].name);//имя заметки
    note = QString::fromStdString(notes[i].note);//сама заметка
    date = notes[i].date.toString("dd.MM.yyyy"); //дата заметки
    time = notes[i].time.toString("hh:mm");      //время заметки
    id   = notes[i].id;                          //номер заметки
}

void Diary::getData(int i) {
    notes[i].name = name.toStdString();
    notes[i].note = note.toStdString();
    notes[i].date.fromString(date, "dd.MM.yyyy");
    notes[i].time.fromString(time, "hh:mm");
    notes[i].id = id.toInt();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
bool Diary::sorting (Note one, Note two)
 {

   if (one.date < two.date)
        return true;
    else if (one.date == two.date && one.time <= two.time)
        return true;
    else return false;
}

void Diary::write() { // Запись в лист всех задач
    for(unsigned int i = 0; i < notes.size(); i++) {
        notes[i].id = i;
        notes[i].setName(notes[i].name);
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(notes[i].printedName), ui->taskList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if(notes[i].completeFlag == true) {
            item->setCheckState(Qt::Checked);
        }
        else {
            item->setCheckState(Qt::Unchecked);
        }
        if (i == 0) calendar_color(notes[i].date);
        if ((i > 0) && (notes[i].date!= notes[i-1].date))
            calendar_color(notes[i].date);
       // тцт должны закрашиваться ячейки, проверка дат, чтобы избежать повторного закрашивания
    }
}

void Diary::writeUnchecked() { // Запись в лист невыполненных задач
    for(unsigned int i = 0; i < notes.size(); i++) {
        notes[i].id = i;
        notes[i].setName(notes[i].name);
        if(notes[i].completeFlag == false) {
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(notes[i].printedName), ui->taskList);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }
    }
}

void Diary::writeTodayUnchecked() { // Запись невыполненных задач выбранного дня
    for(unsigned i = 0; i < notes.size(); i++) {
        notes[i].id = i;
        notes[i].setName(notes[i].name);
        if(notes[i].completeFlag == false && notes[i].date == ui->calendar->selectedDate()) {
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(notes[i].printedName), ui->taskList);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }
    }
}

void Diary::writeToday() { // Запись сегодняшних задач
    for (unsigned int i = 0; i < notes.size(); i++){
        notes[i].id = i;
        notes[i].setName(notes[i].name);
        if (notes[i].date == ui->calendar->selectedDate()) {
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(notes[i].printedName), ui->taskList);
            if(notes[i].completeFlag == true) {
                item->setCheckState(Qt::Checked);
            }
            else {
                item->setCheckState(Qt::Unchecked);
            }
        }
     }
}

int Diary::getIndex(std::string text) { // Получить индекс элемента списка
    int index = 0;
    unsigned int i = 0;
    for(; i < 5; i++) {
        if(text[i + 1] == '.') {
            break;
        }
    }
    for(int j = i; j >= 0; j--) {
        index += (text[i - j] - 48) * pow(10, j);
    }
    return index;
}

void Diary :: calendar_color(QDate date) { // календарь будет закрашивать дату последней созданной заметки
    QTextCharFormat format = ui->calendar->dateTextFormat(date); // закрашивание ячейки календаря
    format.setBackground(QBrush(QColor (200,244,99), Qt::SolidPattern));                 // в QColor потом подберем цвет ячейки календаря
    ui->calendar->setDateTextFormat(date, format);
}

void Diary::on_saveButton_clicked() // Сохранения заметки - теперь это не тут должно быть
{
    Save_load file;
    uint size_of_note;
    QString config;
    size_of_note = notes.size();
    qDebug() << size_of_note << "<--------- size of note";
    file.load_config(&config);

    QList<QString>note_list;
    QList<QString>name_list;
    QList<QString>time_list;
    QList<QString>date_list;
    QList<bool>checked;

    /*
    QStringList note_list,name_list,time_list,date_list;
    note_list.append(size_of_note);
    name_list.append(size_of_note);
    time_list.append(size_of_note);
    date_list.append(size_of_note);
   */

        for(uint Counter = 0; Counter < size_of_note; Counter++)
        {
            checked.append(notes[Counter].completeFlag);
            name = QString::fromStdString(notes[Counter].name); //имя   заметки
            note = QString::fromStdString(notes[Counter].note); //сама  заметка
            date = notes[Counter].date.toString("dd.MM.yyyy");  //дата  заметки
            time = notes[Counter].time.toString("hh:mm");       //время заметки                     //номер заметки
            //checked[Counter].append(notes[Counter].completeFlag);//convert bool to something
            qDebug() << "sample text";

            name_list.append(name);
            //name_list[number] = name;
            qDebug() << "NAME";
            note_list.append(note);
            qDebug() << "NOTE";
            date_list.append(date);
            qDebug() << "DATE";
            time_list.append(time);
            qDebug() << "TIME";
        }
        file.save_file(config,date_list,note_list,time_list,name_list,checked);


    
    /*if(editFlag != -1 && ui->taskText->toPlainText().toStdString() != "") { // Редактирование существующей заметки
        notes[editFlag].setId(editFlag);
        notes[editFlag].setName(ui->taskText->toPlainText().toStdString());
        notes[editFlag].setNote(ui->taskText->toPlainText().toStdString());
        notes[editFlag].setTime(ui->timeEdit->text().toStdString());
        QDate tmp = notes[editFlag].date;
        notes[editFlag].setDate ( ui->calendar->selectedDate());
        //sorting
        // в локальной QDate сохраняем предыдущую дату и проверяем на оставшиеся задачи, удаляем окрашивание
        if (day_is_empty(tmp)) {
            QTextCharFormat format = ui->calendar->dateTextFormat(tmp); // закрашивание ячейки календаря
            format.clearBackground();                                   // в QColor потом подберем цвет ячейки календаря
            ui->calendar->setDateTextFormat(tmp, format);
        }
        QTextCharFormat format = ui->calendar->dateTextFormat(ui->calendar->selectedDate()); // закрашивание ячейки календаря
        format.setBackground(QBrush(QColor (200,244,99), Qt::SolidPattern));                 // в QColor потом подберем цвет ячейки календаря
        ui->calendar->setDateTextFormat(ui->calendar->selectedDate(), format);

        ui->timeEdit->setTime(QTime::fromString("00:00"));
        ui->taskText->clear();
        hide = true;                // Охлаждает обработчик событий на листе
        ui->taskList->clear();      // Здесь
        if(ui->hideCompleted->isChecked())
            writeUnchecked();
        else
            Diary::write();         // Обработчик
        editFlag = -1;              // Отдыхает
        hide = false;               // Обработчик снова в деле
    }

    else if(ui->taskText->toPlainText().toStdString() != "") { // Создание новой заметки
        Note note;
        note.id = notes.size();
        note.setName(ui->taskText->toPlainText().toStdString());
        note.setNote(ui->taskText->toPlainText().toStdString());
        note.setTime(ui->timeEdit->text().toStdString());
        note.setDate(ui->calendar->selectedDate());
        notes.push_back(note);
        //sorting

        ui->timeEdit->setTime(QTime::fromString("00:00"));
        ui->taskText->clear();
        hide = true;
        ui->taskList->clear();
        if(ui->hideCompleted->isChecked())
            writeUnchecked();
        else
            Diary::write();
        QTextCharFormat format = ui->calendar->dateTextFormat(ui->calendar->selectedDate()); // закрашивание ячейки календаря
        format.setBackground(QBrush(QColor (200,244,99), Qt::SolidPattern)); // в QColor потом подберем цвет ячейки календаря
        ui->calendar->setDateTextFormat(ui->calendar->selectedDate(), format);

        hide = false;
    }*/
}

void Diary::on_deleteButton_clicked()  // Удаление заметки
{
    if(ui->taskList->currentItem()) {
        QMessageBox del(QMessageBox::Question, tr("Удаление задачи"), tr("Вы действительно хотите удалить задачу?"),
                                                                QMessageBox::Yes | QMessageBox::No, this);
        del.setButtonText(QMessageBox::Yes, tr("Хочу!"));
        del.setButtonText(QMessageBox::No, tr("Не хочу!"));
        if(del.exec() == QMessageBox::Yes) {

            QDate tmp =  notes[getIndex(ui->taskList->currentItem()->text().toStdString())].date;

            qDebug() << "deleted from vector - " << getIndex(ui->taskList->currentItem()->text().toStdString());
            qDebug() << "deleted - " << ui->taskList->currentRow();

            notes.erase(notes.begin() + getIndex(ui->taskList->currentItem()->text().toStdString()));
            delete ui->taskList->currentItem();
            ui->taskText->clear();

            // перекрашивание ячейки, если на день нет больше заданий
            if (day_is_empty(tmp)) {
                QTextCharFormat format = ui->calendar->dateTextFormat(tmp);
                format.clearBackground();
                ui->calendar->setDateTextFormat(tmp, format);
            }
            ui->taskList->clear();
            write();
        }
    }
}

void Diary::on_editButton_clicked()  // Редактирование заметки
{
    if(ui->taskList->currentItem()) {
        editFlag = getIndex(ui->taskList->currentItem()->text().toStdString());

        QDate tmp =  notes[getIndex(ui->taskList->currentItem()->text().toStdString())].date;
        QTextCharFormat format = ui->calendar->dateTextFormat(tmp);
        format.clearBackground();
        ui->calendar->setDateTextFormat(tmp, format);

        on_newNoteButton_clicked();
    }
}

void Diary::on_taskList_itemDoubleClicked()  // Редактирование заметки
{
    on_editButton_clicked();
}

void Diary::on_hideCompleted_stateChanged(int arg1) // Скрыть выполненные задачи
{
    if(arg1 && todayTasksFlag == true) {
        //Write today's unchecked
        hideCompletedFlag = true;

        hide = true;
        ui->taskList->clear();
        writeTodayUnchecked();
        hide = false;
        ui->taskText->clear();
    }
    else if(arg1) {
        // Write unchecked
        hideCompletedFlag = true;

        hide = true;
        ui->taskList->clear();
        writeUnchecked();
        hide = false;
        ui->taskText->clear();
    }
    else {
        // Write all
        hideCompletedFlag = false;

        hide = true;
        ui->taskList->clear();
        if(todayTasksFlag == true) {
            writeToday();
        } else {
            write();
        }
        hide = false;
    }
}


void Diary::on_taskList_itemChanged(QListWidgetItem *item) // Обработчик событий на листе, синхронизирует переменные и галочки
{

    //ui->calendar->setSelectedDate(notes[getIndex(item->text().toStdString())].date);
    if(!hide) {
        if(item->checkState() == Qt::Checked) {
            notes[getIndex(item->text().toStdString())].completeFlag = true;
            qDebug() << "true" << ui->taskList->row(item);
            qDebug() << "true at vector" << getIndex(item->text().toStdString());
        }

        else {
            notes[getIndex(item->text().toStdString())].completeFlag = false;
            qDebug() << "false" << ui->taskList->row(item);
            qDebug() << "false at vector" << getIndex(item->text().toStdString());
        }
    }

}

/*void Diary::on_calendar_clicked(const QDate &date) //Запрет на создание новых дел для прошедших дней
{
    if (date < QDate::currentDate()) ui->saveButton->setDisabled(true);
    else ui->saveButton->setDisabled(false);
}*/

void Diary::on_todayTasks_stateChanged(int arg1) // Список событий на конкретную дату
{
    if(arg1 && hideCompletedFlag == true) {
        todayTasksFlag = true;

        hide = true;
        ui->taskList->clear();
        writeTodayUnchecked();
        hide = false;
        ui->taskText->clear();
    }
    else if (arg1) {
        todayTasksFlag = true;

        hide = true;
        ui->taskList->clear();
        hide = false;
        writeToday();
        ui->taskText->clear();
     } else {
        todayTasksFlag = false;

        hide = true;
        ui->taskList->clear();
        if(hideCompletedFlag == true) {
            writeUnchecked();
        } else {
            write();
        }
        hide = false;
    }
 }


bool Diary :: day_is_empty(QDate &date) { // Проверка, остались ли дела на указанный день

    for (unsigned int i = 0; i < notes.size(); i++)
        if (date == notes[i].date) return 0;
    return 1;
}

void Diary::on_instruction_triggered()  // Инструкция
{
    QString information = "Приложение \"Ежедневник\" позволяет создавать и редактировать задачи, отсортированные по дате и времени, а также контролировать их выполнение.\n"
                          "В левом поле Ваша заметка Вы можете ввести задачу, в календаре над полем выбрать дату не чёто плохо заходит и спать охота напишу потом";
    QMessageBox::information(this, "Инструкция", information);
}

void Diary::on_exit_triggered()         // Выход
{
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

/*void Diary::on_timeEdit_timeChanged(const QTime &time) //это теперь тоже должно быть не здесь
{
    if (ui->calendar->selectedDate() == QDate :: currentDate()) {
    if (time < QTime::currentTime()) ui->saveButton->setDisabled(true);
    else ui->saveButton->setDisabled(false);
    }
    else ui->saveButton->setDisabled(false);
}*/

void Diary::on_menuButton_clicked()     // Переход в главное меню
{
    Menu *m = new Menu(this);
    m->show();
    m->setFixedSize(m->size());

    ui->taskText->clear();
    this->close();
}

void Diary::on_newNoteButton_clicked()      // Создание новой заметки
{
    CreateNote *c = new CreateNote(this);
    c->show();
    c->setFixedSize(c->size());
    ui->taskList->clear();

    ui->taskText->clear();
    this->close();
}

void Diary::on_taskList_itemClicked(QListWidgetItem *item)      // Текс выбранной задачи
{
    ui->taskText->setPlainText(QString::fromStdString(notes[getIndex(item->text().toStdString())].note));
}

void Diary::on_clearTextButton_clicked()        // Очистка окна с текстом выбранной задачи
{
    ui->taskText->clear();
}

void Diary::on_clearTasksButton_clicked()       // Удаление всех задач
{
    QMessageBox clear(QMessageBox::Question,
                tr("Очистка"),
                tr("Вы действительно хотите очистить ежедневник?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
        clear.setButtonText(QMessageBox::Yes, tr("Действительно хочу!"));
        clear.setButtonText(QMessageBox::No, tr("НЕТ!"));

    if (clear.exec() == QMessageBox::Yes){
        for (unsigned int i = 0; i < notes.size(); i++) {
            if (i >=1 && notes[i].date == notes[i-1].date) continue;
            QTextCharFormat format = ui->calendar->dateTextFormat(notes[i].date);
            format.clearBackground();
            ui->calendar->setDateTextFormat(notes[i].date, format);
        }
        notes.clear();
        notes.resize(0);
        ui->taskList->clear();
        ui->taskText->clear();
    }
}
