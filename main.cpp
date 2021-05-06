#include "table.h"
#include <QApplication>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/new/prefix1/dallor sign.png"));
    Login log;
    log.show();
    return a.exec();
}

// IF FTH occurs, clean project, run qmake, rebuild, run
