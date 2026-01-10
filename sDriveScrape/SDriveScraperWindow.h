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
#include <sstream>



template<QFileDialog::FileMode FILE_MODE>
class FileSelector : public QWidget {
    Q_OBJECT

    public:

    using DialogSelectionType = QStringList*; //std::conditional<FILE_MODE == QFileDialog::ExistingFiles, QStringList*, QString*>;
    QFileDialog* fileDialog = new QFileDialog();



    FileSelector(QWidget *parent = nullptr) : QWidget(parent) {
        this->build();
        QObject::connect(fileDialog, &QFileDialog::accepted, this, &FileSelector::handleDialogAccepted);

        // switch (FILE_MODE) {
        //     case QFileDialog::AnyFile:
        //         this->currentSelection= new QString();
        //     case QFileDialog::ExistingFile:
        //         this->currentSelection = new QString();
        //     case QFileDialog::Directory:
        //         this->currentSelection = new QString();
        //     case QFileDialog::ExistingFiles:
        this->currentSelection = new QStringList();
        };
    QLineEdit* currentFileLine;
    QToolButton* selectButton;
    QString getSelectedFile();

    signals:
    void file_selected(QStringList* filename);

    public slots:
    void handleDialogAccepted();
    void open_file_selection();

    private:

    QStringList* currentSelection;
    void build();
};



class DirectoryFileSelector : public FileSelector<QFileDialog::Directory> {
    Q_OBJECT
    public:
    DirectoryFileSelector(QWidget *parent = nullptr) : FileSelector(parent) {};
};

template<typename WIDGET_TYPE>
class LabeledWidget : public QWidget {
    Q_OBJECT
public:
    LabeledWidget(QString name, QWidget *parent = nullptr) : QWidget(parent) {
        this->build(name);
    };
    WIDGET_TYPE& getWidget() const;
    QString name() const;


    WIDGET_TYPE* widget;

private:
    QLabel *label;

    void build(const QString& name);
};


class LabeledLineEdit : public LabeledWidget<QLineEdit> {
    Q_OBJECT
public:
    LabeledLineEdit(QString name, QWidget *parent = nullptr) : LabeledWidget(name, parent) {};
};


class TypedConfigPanel : public QWidget {
    Q_OBJECT
    public:
    TypedConfigPanel(SearchSpec::NiceNameVariantTypeMap typed_widget_map, QWidget *parent = nullptr) : QWidget(parent) {
        this->current_variant_type_map = typed_widget_map;
        this->build();
    }
    public slots:

    template<typename value_type>
    void update_variant_typemap(std::string variant_nicename, value_type new_value);

    private:
    SearchSpec::NiceNameVariantTypeMap current_variant_type_map;


    void build();
};

//////////////////
class SDriveScraperWindow : public QMainWindow{
    Q_OBJECT


public:
    SDriveScraperWindow(SearchSpec::SearchSpecification initial_search_spec);

    ~SDriveScraperWindow() override;

static QTextEdit *output_box;

    signals:
    void start_search_button_clicked(std::shared_ptr<SearchSpec::SearchSpecification> spec);
    public slots:
    void progress_updated(int current, int total);
    void search_completed();
    void copy_completed();
private:
    static build(SearchSpec::SearchSpecification search_spec);

    static LabeledLineEdit* build_labeled_line_edit(QString& name);
    static QWidget* build_output_textbox();
    static QWidget* build_config_panel();

    



    std::shared_ptr<SearchSpec::SearchSpecification> get_current_search_spec;
        
};

