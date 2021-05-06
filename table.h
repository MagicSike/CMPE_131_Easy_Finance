#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include "form.h"
#include "login.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QTableView>
#include <QtDebug>
#include <QListView>
#include <QSettings>
#include <QStandardPaths>
#include <QVector>
#include <vector>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class Table; }
QT_END_NAMESPACE

class Table : public QMainWindow
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();

    void messageInformation(const QString &t_display, const int t_mType);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_8_clicked();

private:
    Ui::Table *ui;
    Form *newWindows;
    std::vector<std::vector<QString>> *test;
    QVector<QString> *testNames;

    enum graph {line, scatter, bar, pie, box, area, lineBar, hBar};
    void loadSettings();
    void saveTableData();
};
#endif // TABLE_H
