#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    statement(false)
{
    ui->setupUi(this);
}

bool Login::nextState()
{
    return statement;
}

void Login::loadSettings()
{
    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "Data Foam", "sss");

    code = setting.value("key").toString();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked() // login
{
    //QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "Data Foam", "sss");

    if ((setting.contains("key")))
    {
        statement = true;
        loadSettings();
        qDebug() << "Loaded from login";
    }

    if(password == code && statement == true)
    {
        Table *table = new Table;

        table->show();

        hide();
    }
    else
    {
        ui->lineEdit->setStyleSheet("color:red;");
        ui->lineEdit->setText("Password is incorrect");
    }

}

void Login::on_pushButton_2_clicked() // register
{
    RegisterPage *registerP = new RegisterPage;
    registerP->show();
}
