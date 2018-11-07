#include "note.h"
#include <cstring>

void Note::setName(std::string text) {
    this->name = text;
    text.insert(text.begin(), this->id + 48);
    text.insert(text.begin() + 1, '.');
    text.insert(text.begin() + 2, ' ');
    this->printedName = text;
}

void Note::setNote(std::string text) {
    this->note = text;
}

void Note::setTime(QTime time) {
    this->time = time;
}

void Note::setDate(QDate date) {
    this->date = date;
}

/*void Note::setId(int num) {
    this->id = num;
    if(num < 10) {
        this->printedName.erase(this->name.begin(), this->name.begin() + 3);
        this->printedName.insert(this->name.begin(), this->id + 48);
        this->printedName.insert(this->name.begin() + 1, '.');
        this->printedName.insert(this->name.begin() + 2, ' ');

    }

    else if (num >= 10 && num < 100) {
        this->printedName.erase(this->name.begin(), this->name.begin() + 4);
        this->printedName.insert(this->name.begin(), this->id + 48);
        this->printedName.insert(this->name.begin() + 2, '.');
        this->printedName.insert(this->name.begin() + 3, ' ');
    }
}*/
