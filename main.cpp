#include "mainwindow.h"

#include <QApplication>

#include "db_worker.h"
#include "periodic_table.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
