#include "scanner.h"
#include "database.h"

#include <QFile>
#include <qDebug>

scanner::scanner(const QString &file) :
    QThread(),
    _file(file),
    _is_file(true),
    _paused(false),
    _percent(0),
    _stopped(false)
{
}

scanner::scanner(const QByteArray &data) :
    QThread(),
    _data(data),
    _is_file(false),
    _paused(false),
    _percent(0),
    _stopped(false)
{
}

int scanner::get_percent() const
{
    return _percent;
}

QString scanner::get_threats()
{
    _stopped = true;
    return _threats;
}

void scanner::pause(bool p)
{
    _paused = p;
}

void scanner::run()
{
    switch(_is_file)
    {
    case true:
        scan_file();
        break;
    case false:
        scan_data();
        break;
    }
}

void scanner::scan_file()
{
    qDebug() << "Start reading file " << _file;
    QFile file(_file);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "Error opening file " << _file;
        return;
    }
    qint64 file_size = file.size();
    qint64 piece_size = 1024*1024; //1 MB
    qint64 t = (file_size/piece_size + (file_size%piece_size != 0));
    qDebug() << "File size is " << file_size << " Will be processed at " << t << " iterations";
    if (!t)
    {
        _percent = 100;
        file.close();
        while(!_stopped)
            QThread::msleep(100);
        return;
    }
    for (qint64 i = 0; i < t; ++i)
    {
        if (_stopped)
            return;
        while(_paused)
        {
            //qDebug() << "OnPause";
            QThread::msleep(100);
        }
        int current_size = ((i + 1) * piece_size - database::get_sequesce_max_size() > file_size) ? (file_size - i * piece_size) : (piece_size + database::get_sequesce_max_size());
        uchar* memory = file.map(i*piece_size, current_size);
        //qDebug() << QByteArray::fromRawData(reinterpret_cast<char*>(memory), current_size).toHex();
        if (memory)
        {
            _threats.append(database::check_data(QByteArray::fromRawData(reinterpret_cast<char*>(memory), current_size).toHex()));
            file.unmap(memory);
        }
        _percent = 100*(i + 1)/t;
    }
    file.close();
    while(!_stopped)
        QThread::msleep(100);
}

void scanner::scan_data()
{
    _threats.append(database::check_data(_data));
    _percent = 100;
}

void scanner::stop()
{
    _stopped = true;
}

