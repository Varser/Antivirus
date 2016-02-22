#ifndef SCANNER_H
#define SCANNER_H

#include <QThread>
#include <QString>


class scanner : public QThread
{
    Q_OBJECT

public:
    void run();
    void scan_file();
    void scan_data();

public:
    scanner(const QString& path);
    scanner(const QByteArray& path);

    int get_percent() const;
    QString get_threats();

    void pause(bool);
    void stop();

private:
    int _percent;
    bool _paused,
        _stopped,
        _is_file;
    QString _threats,
        _file;
    QByteArray _data;
};

#endif // SCANNER_H
