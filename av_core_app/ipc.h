#ifndef IPC_H
#define IPC_H

#include <QObject>
#include <QTcpServer>

class ipc : public QObject
{
    Q_OBJECT
public:
    explicit ipc(QObject *parent = 0);

signals:

public slots:
    void on_connect();
private:
    QTcpServer* _server;
};

#endif // IPC_H
