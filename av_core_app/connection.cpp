#include "connection.h"

#include "scanner_manager.h"

connection::connection(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    _socket(socket)
{

}

QPair<QByteArray, QByteArray> connection::tokenize_data(const QByteArray& data)
{
    QPair<QByteArray, QByteArray> request;
    int delimeter = data.indexOf('=') + 1;
    if (!delimeter)
        return QPair<QByteArray, QByteArray>();
    request.first.setRawData(data.data(), delimeter);
    request.second.setRawData(data.data() + delimeter, data.size() - delimeter);
    return request;
}

QByteArray connection::process_request(const QByteArray &data)
{
    QPair<QByteArray, QByteArray> request = tokenize_data(data);

    if (request.first.contains("add_file="))
    {
        return QByteArray::number(scanner_manager::create_scanner(QString(request.second)));
    }

    else if (request.first.contains("add_data="))
    {
        return QByteArray::number(scanner_manager::create_scanner(request.second));
    }

    else if (request.first.contains("get_percent="))
    {
        return QByteArray::number(scanner_manager::get_percent(request.second.toInt()));
    }

    else if (request.first.contains("get_threats="))
    {
        return scanner_manager::get_threats(request.second.toInt()).toUtf8();
    }

    else if (request.first.contains("process_stop="))
    {
        scanner_manager::process_stop(request.second.toInt());
        return "ok";
    }

    else if (request.first.contains("process_pause="))
    {
        scanner_manager::process_pause(request.second.toInt());
        return "ok";
    }

    else if (request.first.contains("process_unpause="))
    {
        scanner_manager::process_unpause(request.second.toInt());
        return "ok";
    }

    return "unknown";;
}

void connection::process()
{
    _socket->waitForReadyRead();
    QByteArray request = _socket->readAll();
    qDebug() << "\tObtained new connection with request " << request;
    QByteArray result = process_request(request);
    qDebug() << "\tSending result " << result;

    _socket->write(result.data());
    _socket->flush();
    _socket->waitForBytesWritten(3000);
    qDebug() << "\tClose connection " << result;
    _socket->close();
}
