#include "diary.h"
#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Menu m;
    m.show();
    m.setFixedSize(m.size());

    return a.exec();
}
