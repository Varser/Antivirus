#ifndef PAUSE_CONTINUE_BUTTON_H
#define PAUSE_CONTINUE_BUTTON_H

#include <QPushButton>

class pause_continue_button : public QPushButton
{
    Q_OBJECT
public:
    explicit pause_continue_button(QWidget *parent = 0);
signals:
    void pause(bool);
public slots:
    void on_pause();
    void on_pause(bool);
    void on_continue();
    void change_state();
    void setEnabled(bool);
};

#endif // PAUSE_CONTINUE_BUTTON_H
