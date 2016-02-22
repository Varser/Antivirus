#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QWidget>
#include <QProgressBar>

class progress_bar : public QProgressBar
{
    Q_OBJECT
public:
    explicit progress_bar(QWidget *parent = 0);

signals:

public slots:
    void show_hide(bool);
    void set_progress(int);
};

#endif // PROGRESS_BAR_H
