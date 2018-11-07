#ifndef STANDART_PATH_H
#define STANDART_PATH_H
#include <QStandardPaths>
#include <QFile>
#include <QDebug>
#include <QTime>
#include <QDir>

void standart_paths(QString *Standart_path)
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
void check_Diaries(QStringList *dirs)
{
    QString StandartPath;
    standart_paths(&StandartPath);
    QDir folder(StandartPath);
        QStringList allFolders = folder.entryList(QDir::Dirs|QDir::Hidden|QDir::NoDotAndDotDot);
    QString Folders = allFolders.join("\n");
    qDebug() << "CHECK DIRS OF DIRECTORY " << Folders;
    *dirs = allFolders;
}
void savef       (QString Path, QString text)
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
void make_cfg  (QString NameDiary)
{

    QString Standart_Path;
    standart_paths(&Standart_Path);
    Standart_Path = Standart_Path + "//.conf.ig";
    savef(Standart_Path, NameDiary);

}

#endif // STANDART_PATH_H
