#include "SDriveScraperWindow.h"

#include <qcheckbox.h>
#include <qspinbox.h>
#include <strstream>


SDriveScraperWindow::SDriveScraperWindow(SearchSpec::SearchSpecification initial_search_spec) {
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

    this->layout()->addWidget(label);
    this->layout()->addWidget(widget);
}

template<typename WIDGET_TYPE>
WIDGET_TYPE & LabeledWidget<WIDGET_TYPE>::getWidget() const {
    return *this->widget;
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
void FileSelector<FILE_MODE>::handleDialogAccepted() {
    auto selection = this->fileDialog->selectedFiles();
    auto displayableSelection = new QString();
    std::transform(selection.begin(), selection.end(), [=](const QString& s){displayableSelection->append(s);});
    currentFileLine->setText(*displayableSelection);
    free(displayableSelection);
    emit file_selected(selection);
}

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



template<typename value_type>
void TypedConfigPanel::update_variant_typemap(std::string variant_nicename, value_type new_value) {
    if (!this->current_variant_type_map.contains(variant_nicename)) {
        return;
    };
    this->current_variant_type_map.try_emplace(variant_nicename, new_value);
}

void TypedConfigPanel::build() {
    this->setLayout(new QVBoxLayout());
    for (auto& [name, variant] : this->current_variant_type_map) {
        if (std::holds_alternative<fs::path>(variant)) {
            LabeledWidget<DirectoryFileSelector> *widget = new LabeledWidget<DirectoryFileSelector>(QString::fromStdString(name));
            std::function f = [=, this](const QStringList * path) {
                this->update_variant_typemap(name, fs::path(path->at(0).toStdString() ) );
            };

            connect(widget->widget, &DirectoryFileSelector::file_selected, this, f);
            this->layout()->addWidget(widget);
            free(widget);
        } else if (std::holds_alternative<std::vector<std::string>>(variant)) {

            LabeledWidget<QLineEdit> *widget = new LabeledWidget<QLineEdit>(QString::fromStdString(name));

            std::function f = [=, this](QString text) {
                auto str = text.toStdString();
                std::vector<std::string> strvec;
                std::stringstream ss(str);
                std::string substr;
                while (std::getline(ss, substr, ',')) {
                    size_t pos = substr.find(' ');
                    while (pos == 0) {
                        substr.erase(pos, 1);
                        pos = substr.find(' ');
                    };
                    size_t rpos = substr.rfind(' ');
                    while (rpos == 0) {
                        substr.erase(substr.length()-1, 1);
                        rpos = substr.rfind(' ');
                    };
                    strvec.push_back(substr);
                };
                this->update_variant_typemap(name, strvec);
            };
            connect(widget->widget, &QLineEdit::textEdited, this, f);
            this->layout()->addWidget(widget);
            free(widget);


        } else if (std::holds_alternative<bool>(variant)) {
            LabeledWidget<QCheckBox> *widget = new LabeledWidget<QCheckBox>(QString::fromStdString(name));
            std::function f = [=, this](const int val) {
                this->update_variant_typemap(name, (val==Qt::CheckState::Checked) );
            };

            connect(widget->widget, &QCheckBox::stateChanged, this, f);
            this->layout()->addWidget(widget);
            free(widget);
        } else if (std::holds_alternative<int>(variant)) {
            LabeledWidget<QSpinBox> *widget = new LabeledWidget<QSpinBox>(QString::fromStdString(name));
            std::function f = [=, this](const int val) {
                this->update_variant_typemap(name, val );
            };

            connect(widget->widget, &QSpinBox::valueChanged, this, f);
            this->layout()->addWidget(widget);
            free(widget);
        };
    }
}


















