#ifndef SCANNER_H
#define SCANNER_H

#include "file_scan.h"

#include <QObject>
#include <QList>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>


class scanner : public QThread
{
    Q_OBJECT
public:
    explicit scanner(QString dir, QObject *parent = 0);
    int get_progress();
    QString get_threats();
    void pause(bool);
    void stop_thread();
private:
    QList<file_scan*> _files;
    QString _dir;
    volatile bool _stopped;
    volatile int _progress;
    QString _threats;
    volatile bool _paused;
signals:
    void threats_list(QString);
    void progress(int);
private:
    void run();
};

#endif // SCANNER_H
