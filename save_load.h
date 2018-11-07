#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H
#include <QStandardPaths>
#include <QFile>
#include <QDebug>
#include <QTime>
#include <QDir>

void DeletingF         (QString Path)
{
    QFile(Path).remove();
}
void date         (QString Year,QString Month,QString Day,QString *Date)
{

    QString p = ".";

    *Date = Day + p + Month + p + Year;

}
void standart_path(QString *Standart_path)
{

    QVariant currentUserData = 1;
    QStandardPaths::StandardLocation type = static_cast<QStandardPaths::StandardLocation>(currentUserData.toInt());
    QStringList paths = QStandardPaths::standardLocations(type);
    QString s = "//",
            Diary = "Diary_v3";
    QString str = paths.join("");
    str = paths.join(",");

    str.replace("/","//");

    *Standart_path = str + s + Diary;

}
void checkDiaries(QStringList *dirs)
{
    QString StandartPath;
    standart_path(&StandartPath);
    QDir folder(StandartPath);
        QStringList allFolders = folder.entryList(QDir::Dirs|QDir::Hidden|QDir::NoDotAndDotDot);
    QString Folders = allFolders.join("\n");
    qDebug() << "CHECK DIRS OF DIRECTORY " << Folders;
    *dirs = allFolders;
}

//SAVING||||||SAVING||||||SAVING||||||SAVING||||||SAVING||||||SAVING||||||SAVING||||||SAVING||||||SAVING||||||SAVING||||||
void make_path    (QString date, QString NumberNote, QString *PTime, QString *PNote, QString *PName)
{
    QString Standart_path;
    standart_path(&Standart_path);

    QString s = "//";
    QString Path = Standart_path + s + date + s + NumberNote;

    QString time = "time.tfd",
            note = "note.tfd",
            name = "name.tfd";

    *PTime = Path + s + time;
    *PNote = Path + s + note;
    *PName = Path + s + name;

}
void save_f       (QString Path, QString text)
{
    QFile fileOut(Path);
    qDebug() << "SAVE FILE" << Path;
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileOut);
        writeStream <<  text;
    qDebug() << "SAVE TEXT IN FILE" << text;
        fileOut.close();
    }
}
void make_config  (QString NameDiary)
{

    QString Standart_Path;
    standart_path(&Standart_Path);
    Standart_Path = Standart_Path + "//.conf.ig";
    save_f(Standart_Path, NameDiary);

}
void make_dir     (QString NameDiary, QString Date, QString NumberNote)
{

    QString s = "//";

    QString Standart_path;

    standart_path(&Standart_path);  // получения пути на любом компе путь к папке documents

    QDir().mkdir(Standart_path);

    QString path = Standart_path + s + NameDiary;

    QDir().mkdir(path);

    path = path + s + Date;

    QDir().mkdir(path);

    path = path + s + NumberNote;

    QDir().mkdir(path);

}
void path         (QString Date, QString NameDiary, QString NumberNote, QString *Path)
{

    QString Standart_Path;
    standart_path(&Standart_Path);

    QString s = "//";

    make_dir(NameDiary,Date,NumberNote);

    *Path = Standart_Path + s + NameDiary + s + Date + s + NumberNote + s;

}
void save_file    (QString NameDiary, QString NumberNote, QString Date, QString Text, QString Time, QString Name)
{

    QString Path;
    make_config(NameDiary);
    path(Date,NameDiary,NumberNote,&Path);

    QString PNote = Path + "note.tfd",
            PName = Path + "name.tfd",
            PTime = Path + "time.tfd";

    save_f(PNote,Text);
    save_f(PName,Name);
    save_f(PTime,Time);

}

//LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||
void load_f      (QString Path,QString *Text)
{

    QString string;
    QFile file(Path);
    qDebug() << "LOAD FILE" << Path;
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly))
        return;
    data = file.readAll();
    string = QString(data);
    qDebug() << "LOAD TEXT FROM FILE" << string;
    *Text = string;

}
void load_file   (QString Path, QString *Note, QString *Time, QString *Name)
{

    QString s = "//";
    QString PNote,PName,PTime,
             note, name, time;

    PNote = Path + "note.tfd";
    PName = Path + "name.tfd";
    PTime = Path + "time.tfd";

    load_f(PNote,&note);
    *Note = note;
    load_f(PTime,&time);
    *Time = time;
    load_f(PName,&name);
    *Name = name;


    DeletingF(PNote);
    DeletingF(PName);
    DeletingF(PTime);


}
void checkdirs   (QString *dirs)
{
    QString StandartPath;
    standart_path(&StandartPath);
    QDir folder(StandartPath);
        QStringList allFolders = folder.entryList(QDir::Dirs|QDir::Hidden|QDir::NoDotAndDotDot);
    QString Folders = allFolders.join("\n");
    qDebug() << "CHECK DIRS OF DIRECTORY " << Folders;
    *dirs = Folders;
}
void check_dirs  (QString NameDiary, QString *dirs, QStringList *Folder_Number)
{
    QString StandartPath;
    standart_path(&StandartPath);
    StandartPath = StandartPath + "//" + NameDiary;
    QDir folder(StandartPath);
        QStringList allFolders = folder.entryList(QDir::Dirs|QDir::Hidden|QDir::NoDotAndDotDot);
        *Folder_Number = allFolders;
    QString Folders = allFolders.join("\n");
    qDebug() << "CHECK DIRS OF DIRECTORY " << Folders;
    *dirs = Folders;
}
void read        (QString folders, QString *Note, QString *Name, QString *Time)
{

    QString note = "note.tfd",
            name = "name.tfd",
            time = "time.tfd";

    QString NOTE,
            NAME,
            TIME;

    QString Standart_Path;
    standart_path(&Standart_Path);
    Standart_Path = Standart_Path + "//" + folders + "//";

    note = Standart_Path + note;
    name = Standart_Path + name;
    time = Standart_Path + time;

    load_f(note, &NOTE);
    load_f(name, &NAME);
    load_f(time, &TIME);

    *Note = NOTE;
    *Name = NAME;
    *Time = TIME;

}
void load_config (QString *config)
{

    QString Standart_Path;
    standart_path(&Standart_Path);

    Standart_Path = Standart_Path + "//" + ".conf.ig";
    load_f(Standart_Path,&*config);

}

//LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||LOADING|||||


const QString PATH = "//home//time_bitch//Documents//Diary_v3//university";

#endif // SAVE_LOAD_H

