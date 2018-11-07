#ifndef ALTERNATIVE_SAVE_LOAD_H
#define ALTERNATIVE_SAVE_LOAD_H
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QStandardPaths>
#include <QDebug>
#include <QFile>
#include <QDir>

void standart_path(QString *Standart_path)
{

    QVariant currentUserData = 1;
    QStandardPaths::StandardLocation type = static_cast<QStandardPaths::StandardLocation>(currentUserData.toInt());
    QStringList paths = QStandardPaths::standardLocations(type);
    QString s = "//",
            Diary = "Alternative Diary";
    QString str = paths.join("");
    str = paths.join(",");

    str.replace("/","//");

    *Standart_path = str + s + Diary;

}

void make_dir(QString NameDiary)
{

    QString s = "//";

    QString Standart_path;

    standart_path(&Standart_path);  // получения пути на любом компе путь к папке documents

    QDir().mkdir(Standart_path);

    QString path = Standart_path + s + NameDiary;

    QDir().mkdir(path);

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

void load_file(QString Path, QStringList *Date, QStringList *Note, QStringList *Time, QStringList *Name)
{

    QString Text;
    QList<QString>date;
    QList<QString>note;
    QList<QString>time;
    QList<QString>name;


    load_f(Path,&Text);

    QStringList stringList = Text.split("ノート",QString::SkipEmptyParts);
    int size;



    size = stringList.size();

        qDebug() << size;
    size = size/4;
        qDebug() << size;

    int a = 0,
        b = 1,
        c = 2,
        d = 3;

    for(int n = 0; n < size; n++)
    {
        date.append(stringList[a]);
        qDebug() << "DATE" << n << "from load_file" << date;
        time.append(stringList[b]);
        qDebug() << "TIME" << n << "from load_file" << time;
        name.append(stringList[c]);
        qDebug() << "NAME" << n << "from load_file" << name;
        note.append(stringList[d]);
        qDebug() << "NOTE" << n << "from load_file" << note;

        a = a + 4;
        b = b + 4;
        c = c + 4;
        d = d + 4;

    }

    *Date = date;
    *Note = note;
    *Time = time;
    *Name = name;
}

void save_file(QString NameDiary, QStringList Date, QStringList Text, QStringList Time, QStringList Name)
{

    make_dir(NameDiary);
    make_config(NameDiary);

    QString standartPath,what_to_save = "";
    standart_path(&standartPath);
    standartPath = standartPath + "//" + NameDiary + "//data.tfd";

    int size = Date.size();
    qDebug() << "size of lists" << size;


    for(int n = 0; n < size; n++)
    {
            QString ss  = "ノート"; //просто так:), если интересно, то переводится как "N0TE"

            what_to_save = what_to_save + Date[n] + ss + Time[n] + ss + Name[n] + ss + Text[n] + ss;


    }
    save_f(standartPath, what_to_save);

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

void load_config (QString *config)
{

    QString Standart_Path;
    standart_path(&Standart_Path);

    Standart_Path = Standart_Path + "//" + ".conf.ig";
    load_f(Standart_Path,&*config);

}


#endif // ALTERNATIVE_SAVE_LOAD_H
