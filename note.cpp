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
