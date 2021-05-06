#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QSettings>
#include <QMessageBox>
#include <QtDebug>

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = nullptr);
    void saveSettings(QString name);
    void loadSettings();
    void clearSettings();
    ~RegisterPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegisterPage *ui;
    bool newUser;
    QString passwordCheck;
};

#endif // REGISTERPAGE_H
