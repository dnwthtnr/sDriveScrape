#include "SDriveScraperWindow.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtextedit.h>




SDriveScraperWindow::SDriveScraperWindow() {
    QWidget* centralWidget = SDriveScraperWindow::build();
    this->setCentralWidget(centralWidget);
    this->show();
}

SDriveScraperWindow::~SDriveScraperWindow() {
}

QWidget* SDriveScraperWindow::build() {
    auto layout = new QHBoxLayout();
    auto widget = new QWidget();
    widget->setLayout(layout);

    auto output_window = build_output_textbox();
    
    layout->addWidget(output_window);
    
    return widget;
}

LabeledTextbox* SDriveScraperWindow::build_labeled_line_edit(QString name) {
    auto lineedit = new LabeledTextbox(name);
    return lineedit;
}

QWidget* SDriveScraperWindow::build_output_textbox() {
    auto layout = new QHBoxLayout();
    auto widget = new QWidget();
    widget->setLayout(layout);
    output_box = new QTextEdit();
    output_box->setReadOnly(true);
    
    layout->addWidget(output_box);
    return widget;
}

QWidget* SDriveScraperWindow::build_config_panel() {
    auto layout = new QHBoxLayout();
    auto widget = new QWidget();
    widget->setLayout(layout);
    return widget;
}

QTextEdit* SDriveScraperWindow::output_box = 0;

void SDriveScraperWindow::progress_updated(int current, int total) {
}

void SDriveScraperWindow::search_completed() {
}

void SDriveScraperWindow::copy_completed() {
}


void LabeledTextbox::build(const QString& name) {
    auto layout = new QHBoxLayout();
    this->setLayout(layout);
    
    label = new QLabel();
    label->setText(name);
    linedit = new QLineEdit();

    this->layout()->addWidget(label);
    this->layout()->addWidget(linedit);

    connect(linedit, &QLineEdit::textChanged, this, &LabeledTextbox::lineEdit_textChanged);
}
void LabeledTextbox::lineEdit_textChanged(const QString& text) {
emit this->textEdited(text);
}
QString LabeledTextbox::text() const {
    return this->linedit->text();
};

QString LabeledTextbox::name() const {
return this->label->text();
}



