#ifndef NOTE_H
#define NOTE_H
#include <iostream>
#include <QString>
#include <QDate>

class Note
{
public:
    std::string name;               // Фактическое имя
    std::string note;
    QTime time;
    std::string printedName;        // Печатаемое в списке имя (с индексом)
    QDate date;
    bool completeFlag = false;      // Галочка у заметки отсутствует
    int id;

    void setName(std::string text); // Задать фактическое имя и печатаемое (в соответствии с индексом)
    void setNote(std::string text);
    void setTime(QTime time);
    void setDate(QDate date);
    //void setId(int num);            // Стереть предыдущий индекс из печатаемого имени и записать новый

};

#endif // NOTE_H
