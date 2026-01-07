#pragma once
#include <qfiledialog.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qtextedit.h>

#include "SearchSpecification.h"
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QObject>
#include <QtCore/QtCore>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/QLineEdit>

#include <qtoolbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtextedit.h>




template<typename WIDGET_TYPE>
class LabeledWidget : public QWidget {
    Q_OBJECT
public:
    LabeledWidget(QString name, QWidget *parent = nullptr) : QWidget(parent) {
        this->build(name);
    };
    WIDGET_TYPE getWidget() const;
    QString name() const;



private:
    QLabel *label;
    WIDGET_TYPE* widget;

    void build(const QString& name);
};


class LabeledLineEdit : public LabeledWidget<QLineEdit> {
    Q_OBJECT
public:
    LabeledLineEdit(QString name, QWidget *parent = nullptr) : LabeledWidget(name, parent) {};
};

template<QFileDialog::FileMode FILE_MODE>
class FileSelector : public QWidget {
    Q_OBJECT

    public:

    using DialogSelectionType = std::conditional<FILE_MODE == QFileDialog::ExistingFiles, QStringList*, QString*>;
    QFileDialog* fileDialog = new QFileDialog();


    FileSelector(QWidget *parent = nullptr) : QWidget(parent) {
        this->build();
        connect(fileDialog, &QFileDialog::accepted, this, &FileSelector::handleDialogAccepted);

        switch (FILE_MODE) {
            case QFileDialog::AnyFile:
                this->currentSelection= new QString();
            case QFileDialog::ExistingFile:
                this->currentSelection = new QString();
            case QFileDialog::Directory:
                this->currentSelection = new QString();
            case QFileDialog::ExistingFiles:
                this->currentSelection = new QStringList();
        }
    }
    QLineEdit* currentFileLine;
    QToolButton* selectButton;
    QString getSelectedFile();

    signals:
    void file_selected(DialogSelectionType& filename);

    public slots:
    void handleDialogAccepted(DialogSelectionType& selection);
    void open_file_selection();

    private:

    DialogSelectionType currentSelection;
    void build();
};

//////////////////
class SDriveScraperWindow : public QMainWindow{
    Q_OBJECT


public:
    SDriveScraperWindow();

    ~SDriveScraperWindow() override;

static QTextEdit *output_box;

    signals:
    void start_search_button_clicked(std::shared_ptr<SearchSpecification> spec);
    public slots:
    void progress_updated(int current, int total);
    void search_completed();
    void copy_completed();
private:
    static QWidget* build();

    static LabeledLineEdit* build_labeled_line_edit(QString& name);
    static QWidget* build_output_textbox();
    static QWidget* build_config_panel();

    



    std::shared_ptr<SearchSpecification> get_current_search_spec;
        
};

