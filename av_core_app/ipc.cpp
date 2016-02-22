#include "ipc.h"
#include "connection.h"

#include <QTcpSocket>

ipc::ipc(QObject *parent) :
    QObject(parent)
{
    _server = new QTcpServer(this);
    connect(_server, SIGNAL(newConnection()), this, SLOT(on_connect()));
    if(!_server->listen(QHostAddress::LocalHost, 9959))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void ipc::on_connect()
{
    QTcpSocket * socket = _server->nextPendingConnection();
    connection* t_connection = new connection(socket);
    t_connection->run();
    delete t_connection;
}
