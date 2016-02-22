#ifndef SCAN_RESULTS_TEXT_EDIT_H
#define SCAN_RESULTS_TEXT_EDIT_H

#include <QTextEdit>

class scan_results_text_edit : public QTextEdit
{
    Q_OBJECT
public:
    explicit scan_results_text_edit(QWidget *parent = 0);

signals:

public slots:
};

#endif // SCAN_RESULTS_TEXT_EDIT_H
