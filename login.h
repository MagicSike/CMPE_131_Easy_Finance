#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "table.h"
#include "registerpage.h"
#include <QSettings>
#include <QtDebug>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    bool nextState();
    void loadSettings();
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;
    bool statement;
    QString code;
};

#endif // LOGIN_H
