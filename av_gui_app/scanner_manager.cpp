#include "scanner_manager.h"

#include <QFileDialog>

scanner_manager::scanner_manager(QWidget *parent) :
    QWidget(parent),
    _scanner(QPair<bool, scanner*>(false, 0))
{
}

scanner_manager::~scanner_manager()
{
    if (_scanner.first)
    {
        _scanner.first = false;
        delete _scanner.second;
    }
}

void scanner_manager::on_progress(int pr)
{
        emit set_progress(pr);
}

void scanner_manager::on_threats(QString tr)
{
    emit set_threats(tr);
}

void scanner_manager::on_scan()
{
    _directory = QFileDialog::getExistingDirectory(this, "Choose folder for scan...", "/");
    if (_directory.isEmpty())
    {
        emit directory_not_choosen();
    }
    else
    {
        _scanner.second = new scanner(_directory);
        connect(_scanner.second, SIGNAL(progress(int)), this, SLOT(on_progress(int)));
        connect(_scanner.second, SIGNAL(threats_list(QString)), this, SLOT(on_threats(QString)));
        _scanner.first = true;
        _scanner.second->start();
    }
}

void scanner_manager::on_stop()
{
    if (_scanner.first)
    {
        _scanner.first = false;
        _scanner.second->stop_thread();
    }
}

void scanner_manager::on_pause()
{
    if (_scanner.first)
        _scanner.second->pause(true);
}

void scanner_manager::on_continue()
{
    if (_scanner.first)
        _scanner.second->pause(false);
}

void scanner_manager::on_scan(bool b_scan)
{
    switch (b_scan)
    {
    case true:
        on_scan();
        break;
    case false:
        on_stop();
        break;
    }
}

void scanner_manager::on_pause(bool b_pause)
{
    switch (b_pause)
    {
    case true:
        on_pause();
        break;
    case false:
        on_continue();
        break;
    }
}

