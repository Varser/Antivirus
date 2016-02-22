#ifndef FILE_SCAN_H
#define FILE_SCAN_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class file_scan : public QObject
{
    Q_OBJECT
public:
    explicit file_scan(QString file, QObject *parent = 0);
    int get_progress();
    qint64 get_file_size();
    QString get_threats();
    QString get_file_name();
    void stop();
    void pause(bool);
    void send_for_scan();

private:
    QTcpSocket* _socket;
    QString _file;
    QByteArray _id;
    qint64 _file_size;
    bool _paused;

signals:

public slots:
};

#endif // FILE_SCAN_H
