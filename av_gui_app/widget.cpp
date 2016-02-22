#include "widget.h"

#include "Buttons/scan_stop_button.h"
#include "Buttons/pause_continue_button.h"
#include "progress_bar.h"
#include "scan_results_text_edit.h"
#include "scanner_manager.h"

#include <QStyleOption>
#include <QPainter>

/**---------
 * constants
 * -------*/
const QRect k_main_window_rect(500, 300, 500, 280);
const QSize k_button_size(110, 30);
const quint32 k_border(10);

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    _scan_stop(new scan_stop_button(this)),
    _pause_continue(new pause_continue_button(this)),
    _progress(new progress_bar(this)),
    _scan_results(new scan_results_text_edit(this)),
    _scanner(new scanner_manager(this))
{
    prepare_background();
    prepare_buttons();
    prepare_progress_bar();
    prepare_text_edit();

    connect(_scan_stop, SIGNAL(scan(bool)), _pause_continue, SLOT(setEnabled(bool)));
    connect(_scan_stop, SIGNAL(scan(bool)), _scanner, SLOT(on_scan(bool)));
    connect(_scanner, SIGNAL(directory_not_choosen()), _scan_stop, SLOT(on_stop()));
    connect(_scanner, SIGNAL(set_threats(QString)), _scan_stop, SLOT(on_stop()));
    connect(_scanner, SIGNAL(set_progress(int)), _progress, SLOT(set_progress(int)));
    connect(_scanner, SIGNAL(set_threats(QString)), _scan_results, SLOT(setText(QString)));
    connect(_pause_continue, SIGNAL(pause(bool)), _scanner, SLOT(on_pause(bool)));
    //connect(_scan_stop, SIGNAL(scan(bool)), _progress, SLOT(show_hide(bool)));
}

void Widget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void Widget::prepare_background()
{
    this->setGeometry(k_main_window_rect);
    this->setObjectName(QString("MainWindow"));
    this->setStyleSheet("QWidget#MainWindow {"
        "background-image: url(:/resources/worker-250x250.png); "
        "background-position: top left; "
        "background-repeat: no-repeat; "
        "}"
    );
}

void Widget::prepare_buttons()
{
    QPoint scan_stop_button_position(
                k_border,
                k_main_window_rect.height() - k_button_size.height() - k_border);
    _scan_stop->setGeometry(QRect(scan_stop_button_position, k_button_size));

    QPoint pause_continue_button_position(
                k_border + k_border + k_button_size.width(),
                k_main_window_rect.height() - k_button_size.height() - k_border);
    _pause_continue->setGeometry(QRect(pause_continue_button_position, k_button_size));
}

void Widget::prepare_progress_bar()
{
    QPoint progress_position(
                k_main_window_rect.width()/2,
                k_main_window_rect.height() - k_button_size.height() - k_border);
    QSize progress_size(size().width() - progress_position.rx() - k_border, k_button_size.height());
    _progress->setGeometry(QRect(progress_position, progress_size));
}

void Widget::prepare_text_edit()
{
    _scan_results->setGeometry(k_main_window_rect.width()/2,
                               k_border,
                               k_main_window_rect.width()/2 - k_border,
                               k_main_window_rect.height() - k_button_size.height() - 3 * k_border);
}
