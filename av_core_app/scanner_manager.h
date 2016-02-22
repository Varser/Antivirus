#ifndef SCANNER_MANAGER_H
#define SCANNER_MANAGER_H

#include <QMap>
#include <QString>
#include <QSharedPointer>

#include "scanner.h"

typedef int SCANNER_ID;

class scanner_manager
{
private:
    static scanner_manager _manager;
    QMap<SCANNER_ID, QSharedPointer<scanner> > _scanners;
    static SCANNER_ID _id;

public:
    static SCANNER_ID create_scanner(const QString& file);
    static SCANNER_ID create_scanner(const QByteArray& data);

    static int get_percent(SCANNER_ID);
    static QString get_threats(SCANNER_ID);

    static void process_stop(SCANNER_ID);
    static void process_pause(SCANNER_ID);
    static void process_unpause(SCANNER_ID);

private:
    scanner_manager();
    ~scanner_manager();

    scanner_manager(const scanner_manager &);
    scanner_manager & operator=(const scanner_manager &);
};

#endif // SCANNER_MANAGER_H
