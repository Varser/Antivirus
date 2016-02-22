#include "ipc.h"
#include "connection.h"

#include <QTcpSocket>
#include <QSharedPointer>

ipc::ipc(QObject *parent) :
    QObject(parent),
    _server(this)
{
    connect(&_server, SIGNAL(newConnection()), this, SLOT(on_connect()));
}

bool ipc::init()
{
    if(!_server.listen(QHostAddress::LocalHost, 9959))
    {
        qDebug() << "Server could not start";
        return false;
    }
    else
    {
        qDebug() << "Server started!";
        return true;
    }
}

void ipc::on_connect()
{
    connection t_connection(_server.nextPendingConnection());
    t_connection.process();
}
