#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTCPSocket>


class connection : public QObject
{
    Q_OBJECT
public:
    explicit connection(QTcpSocket* socket, QObject *parent = 0);
    void process();
private:
    QByteArray process_request(const QByteArray& data);
    QPair<QByteArray, QByteArray> tokenize_data(const QByteArray& data);
private:
    QTcpSocket* _socket;

signals:

public slots:

};

#endif // CONNECTION_H
