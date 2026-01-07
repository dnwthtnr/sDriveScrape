#include "SDriveScraperWindow.h"





SDriveScraperWindow::SDriveScraperWindow() {
    QWidget* centralWidget = SDriveScraperWindow::build();
    this->setCentralWidget(centralWidget);
    this->show();
};

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

LabeledLineEdit* SDriveScraperWindow::build_labeled_line_edit(QString& name) {
    auto lineedit = new LabeledLineEdit(name);
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

template<typename WIDGET_TYPE>
void LabeledWidget<WIDGET_TYPE>::build(const QString& name) {
    auto layout = new QHBoxLayout();
    this->setLayout(layout);
    
    this->widget = new WIDGET_TYPE();
    label->setText(name);

    this->layout()->addWidget(label, Qt::AlignLeft);
    this->layout()->addWidget(widget);
}

template<typename WIDGET_TYPE>
QString LabeledWidget<WIDGET_TYPE>::name() const {
    return this->label->text();
}


template<QFileDialog::FileMode FILE_MODE>
QString FileSelector<FILE_MODE>::getSelectedFile() {
    return currentFileLine->text();
};

template<QFileDialog::FileMode FILE_MODE>
void FileSelector<FILE_MODE>::open_file_selection() {
    this->fileDialog->setFileMode(FILE_MODE);
    fileDialog->setDirectory(this->getSelectedFile());
    fileDialog->open();
}

template<QFileDialog::FileMode FILE_MODE>
void FileSelector<FILE_MODE>::build() {
    currentFileLine = new QLineEdit();
    currentFileLine->setReadOnly(true);
    selectButton = new QToolButton();

    setLayout(new QHBoxLayout());
    this->layout()->addWidget(currentFileLine);
    this->layout()->addWidget(selectButton, Qt::AlignRight);
}

template<QFileDialog::FileMode FILE_MODE>
void FileSelector<FILE_MODE>::handleDialogAccepted(DialogSelectionType& selection) {
    currentFileLine->setText(selection);
    emit file_selected(selection);
}



