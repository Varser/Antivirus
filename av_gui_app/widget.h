#ifndef WIDGET_H
#define WIDGET_H

#include  "scanner_manager.h"

#include <QWidget>
#include <QProgressBar>
#include <QAbstractButton>
#include <QTextEdit>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

private:
    void prepare_background();
    void prepare_buttons();
    void prepare_progress_bar();
    void prepare_text_edit();

private:
    QAbstractButton* _scan_stop;
    QAbstractButton* _pause_continue;
    QProgressBar* _progress;
    QTextEdit* _scan_results;
    scanner_manager* _scanner;
};

#endif // WIDGET_H
