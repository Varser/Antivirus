#ifndef SCANNER_MANAGER_H
#define SCANNER_MANAGER_H

#include "scanner.h"

#include <QWidget>

class scanner_manager : public QWidget
{
    Q_OBJECT
public:
    explicit scanner_manager(QWidget *parent = 0);
    ~scanner_manager();

signals:
    void directory_not_choosen();
    void set_progress(int);
    void set_threats(QString);
public slots:
    void on_scan();
    void on_stop();
    void on_pause();
    void on_continue();
    void on_scan(bool);
    void on_pause(bool);
    void on_progress(int);
    void on_threats(QString);
private:
    QString _directory;
    QPair<bool, scanner*> _scanner;
};

#endif // SCANNER_MANAGER_H
