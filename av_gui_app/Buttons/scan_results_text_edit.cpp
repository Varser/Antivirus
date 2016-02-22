#include "scan_results_text_edit.h"

scan_results_text_edit::scan_results_text_edit(QWidget *parent) : QTextEdit(parent)
{
    this->setReadOnly(true);
}

