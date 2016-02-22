#ifndef SCAN_STOP_BUTTON_H
#define SCAN_STOP_BUTTON_H

#include <QPushButton>

class scan_stop_button : public QPushButton
{
    Q_OBJECT
public:
    explicit scan_stop_button(QWidget *parent = 0);
signals:
    void scan(bool);
public slots:
    void on_scan();
    void on_scan(bool);
    void on_stop();
    void change_state();
};

#endif // SCAN_STOP_BUTTON_H
