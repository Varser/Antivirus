#include "scanner.h"
#include <QDirIterator>
#include <QDebug>
#include <QTcpSocket>
#include <QtNetwork>

void scanner::run()
{
    qint64 total_files_size = 0;
    QDirIterator files(_dir, QDir::Files, QDirIterator::Subdirectories);
    while(files.hasNext() && !_stopped)
    {
        while(_paused)
        {
            QThread::msleep(50);
            if (_stopped)
            {
                return;
            }
        }
        QThread::msleep(50);
        QString path = files.next();
        qDebug() << path;
        _files.push_back(new file_scan(path, this));
        total_files_size += _files.back()->get_file_size();
    }

    if (!total_files_size)
        return;

    while(_paused)
    {
        QThread::msleep(50);
        if (_stopped)
        {
            return;
        }
    }

    QMutableListIterator<file_scan*> file(_files);
    if (!file.hasNext())
    {
        return;
    }
    file_scan* fs = file.next();
    fs->send_for_scan();
    qint64 last_progress = 0;
    do
    {
        while(_paused)
        {
            fs->pause(_paused);
            QThread::msleep(50);
            if (_stopped)
            {
                fs->stop();
                return;
            }
        }
        QThread::msleep(50);
        if (_stopped)
        {
            fs->stop();
            return;
        }
        qint64 t_progress = fs->get_progress();
        _progress = last_progress + t_progress*fs->get_file_size()/total_files_size;
        emit progress(_progress);
        if (t_progress == 100)
        {
            QString thrts = fs->get_threats();
            if (!thrts.isEmpty())
            {
                _threats.append(fs->get_file_name());
                _threats.append(": ");
                _threats.append(thrts);
                _threats.append("\n");
            }
            if (!file.hasNext())
            {
                break;
            }
            fs = file.next();
            fs->send_for_scan();
            file.remove();
            last_progress = _progress;
        }
    } while (file.hasNext());
    emit progress(100);
    emit threats_list(_threats);
}


scanner::scanner(QString dir, QObject *parent) :
    QThread(parent),
    _stopped(false),
    _progress(0),
    _paused(false)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    _dir = dir;
}

int scanner::get_progress()
{
    return _progress;
}

QString scanner::get_threats()
{
    return _threats;
}

void scanner::pause(bool b_pause)
{
    _paused = b_pause;
}

void scanner::stop_thread()
{
    _stopped = true;
}

