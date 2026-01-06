#pragma once
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


class LabeledTextbox : public QWidget {
    Q_OBJECT
public:
    LabeledTextbox(QString name, QWidget *parent = nullptr) : QWidget(parent) {
        this->build(name);
    };
    QString text() const;
    QString name() const;

    signals:
    void textEdited(const QString &);
    public slots:
    void lineEdit_textChanged(const QString& text);

private:
    QLabel *label;
    QLineEdit* linedit;

    void build(const QString& name);
};


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

    static LabeledTextbox* build_labeled_line_edit(QString name);
    static QWidget* build_output_textbox();
    static QWidget* build_config_panel();

    



    std::shared_ptr<SearchSpecification> get_current_search_spec;
        
};

