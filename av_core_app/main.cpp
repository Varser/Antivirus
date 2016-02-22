#include <QCoreApplication>

#include "ipc.h"
#include "database.h"
#include "scanner.h"

#define DISABLE_UNUSED_WARNING(a) void(0)

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        qDebug() << "\tArgument " << i << ": " << argv[i];
    }
    if (argc < 2)
    {
        qDebug() << "Error: Put the correct path to database file as command line argument";
        return -1;
    }
    QCoreApplication a(argc, argv);
    database::load_database(argv[1]);
    ipc _ipc;
    DISABLE_UNUSED_WARNING(_ipc);
    return a.exec();
}
