#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTCPSocket>


class connection : public QObject
{
    Q_OBJECT
public:
    explicit connection(QTcpSocket* socket, QObject *parent = 0);
    void run();
private:
    QByteArray process_request(const QByteArray& data);
private:
    QTcpSocket* _socket;

signals:

public slots:

};

#endif // CONNECTION_H
