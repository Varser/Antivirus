#include "scan_stop_button.h"

scan_stop_button::scan_stop_button(QWidget *parent) :
    QPushButton(parent)
{
    setText("&Scan...");
    connect(this, SIGNAL(released()), this, SLOT(change_state()));
}

void scan_stop_button::on_scan()
{
    setText("&Stop...");
    emit scan(true);
}

void scan_stop_button::on_stop()
{
    setText("&Scan...");
    emit scan(false);
}

void scan_stop_button::on_scan(bool b_scan)
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

void scan_stop_button::change_state()
{
        on_scan(!text().compare("&Scan..."));
}
