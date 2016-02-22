#include <QCoreApplication>

#include "ipc.h"
#include "database.h"
#include "scanner.h"


bool check_command_line_arguments(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        qDebug() << "\tArgument " << i << ": " << argv[i];
    }
    if (argc < 2)
    {
        qDebug() << "Error: Put the correct path to database file as command line argument";
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (!check_command_line_arguments(argc, argv))
        return -1;

    QCoreApplication a(argc, argv);

    database::load_database(argv[1]);

    ipc _ipc;
    if (!_ipc.init())
        return -2;

    return a.exec();
}
