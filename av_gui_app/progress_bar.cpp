#include "progress_bar.h"

progress_bar::progress_bar(QWidget *parent) :
    QProgressBar(parent)
{
//    setVisible(false);
    setRange(0, 100);
    this->setValue(0);
}

void progress_bar::show_hide(bool shown)
{
    this->setValue(0);
    this->setVisible(shown);
}

void progress_bar::set_progress(int pr)
{
    setValue(pr);
}

