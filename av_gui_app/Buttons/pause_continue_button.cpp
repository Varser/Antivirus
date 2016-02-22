#include "pause_continue_button.h"

pause_continue_button::pause_continue_button(QWidget *parent) :
    QPushButton(parent)
{
    setText("&Pause...");
    setEnabled(false);
    connect(this, SIGNAL(released()), this, SLOT(change_state()));
}

void pause_continue_button::on_pause()
{
    setText("&Continue...");
    emit pause(true);
}

void pause_continue_button::on_continue()
{
    setText("&Pause...");
    emit pause(false);
}

void pause_continue_button::on_pause(bool b_pause)
{
    switch(b_pause)
    {
    case true:
        on_pause();
        break;
    case false:
        on_continue();
        break;
    }
}

void pause_continue_button::change_state()
{
        on_pause(!text().compare("&Pause..."));
}

void pause_continue_button::setEnabled(bool b_enabled)
{
    switch(b_enabled)
    {
    case true:
        QWidget::setEnabled(b_enabled);
        on_continue();
        break;
    case false:
        if (isEnabled())
            on_continue();
        QWidget::setEnabled(b_enabled);
        break;
    }
}
