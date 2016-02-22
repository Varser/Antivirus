#include "file_scan.h"
#include <QFile>

file_scan::file_scan(QString file, QObject *parent) :
    QObject(parent),
    _socket(new QTcpSocket(this)),
    _file(file),
    _paused(false)
{
    QFile f(_file);
    if (!f.open(QFile::ReadOnly))
    {
        qDebug() << "Error opening file " << _file;
        return;
    }
    _file_size = f.size();
    f.close();
}

void file_scan::send_for_scan()
{
    _socket->connectToHost(QHostAddress::LocalHost, 9959);
    _socket->waitForConnected();
    if (_socket->state() != QTcpSocket::ConnectedState)
    {
        qDebug() << "Error connecting to server";
        return;
    }
    _socket->write(QByteArray("add_file=") + _file.toUtf8());
    _socket->flush();
    _socket->waitForBytesWritten();
    _socket->waitForReadyRead();
    _id = _socket->readAll();
    _socket->close();
}

int file_scan::get_progress()
{
    _socket->connectToHost(QHostAddress::LocalHost, 9959);
    _socket->waitForConnected();
    if (_socket->state() != QTcpSocket::ConnectedState)
    {
        qDebug() << "Error connecting to server";
        return 0;
    }
    _socket->write(QByteArray("get_percent=") + _id);
    _socket->flush();
    _socket->waitForBytesWritten();
    _socket->waitForReadyRead();
    QByteArray data = _socket->readAll();
    _socket->close();
    return data.toUInt();
}

qint64 file_scan::get_file_size()
{
    return _file_size;
}

QString file_scan::get_threats()
{
    _socket->connectToHost(QHostAddress::LocalHost, 9959);
    _socket->waitForConnected();
    if (_socket->state() != QTcpSocket::ConnectedState)
    {
        qDebug() << "Error connecting to server";
        return "";
    }
    _socket->write(QByteArray("get_threats=") + _id);
    _socket->flush();
    _socket->waitForBytesWritten();
    _socket->waitForReadyRead();
    QByteArray data = _socket->readAll();
    _socket->close();
    return data;
}

QString file_scan::get_file_name()
{
    return _file;
}

void file_scan::stop()
{
    _socket->connectToHost(QHostAddress::LocalHost, 9959);
    _socket->waitForConnected();
    if (_socket->state() != QTcpSocket::ConnectedState)
    {
        qDebug() << "Error connecting to server";
        return;
    }
    _socket->write(QByteArray("process_stop=") + _id);
    _socket->flush();
    _socket->waitForBytesWritten();
    _socket->waitForReadyRead();
    _socket->readAll();
    _socket->close();
}

void file_scan::pause(bool pause)
{
    if (_paused == pause)
        return;
    _paused = pause;
    _socket->connectToHost(QHostAddress::LocalHost, 9959);
    _socket->waitForConnected();
    if (_socket->state() != QTcpSocket::ConnectedState)
    {
        qDebug() << "Error connecting to server";
        return;
    }
    switch (pause)
    {
    case true:
        _socket->write(QByteArray("process_pause=") + _id);
        break;
    case false:
        _socket->write(QByteArray("process_unpause=") + _id);
        break;
    }
    _socket->flush();
    _socket->waitForBytesWritten();
    _socket->waitForReadyRead();
    _socket->readAll();
    _socket->close();
}

