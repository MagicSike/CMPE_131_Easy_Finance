#include "registerpage.h"
#include "ui_registerpage.h"

RegisterPage::RegisterPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::RegisterPage), newUser(false), passwordCheck(" ")
{
    ui->setupUi(this);

    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "Data Foam", "sss");

    if(setting.contains("key"))
    {
        newUser = true;
        loadSettings();

        QMessageBox::critical(this, "Register", "Password was already set for this application.\n"
                                                "Re-registering will reset all values in the application.");
    }
}

void RegisterPage::saveSettings(QString name)
{
    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "Data Foam", "sss");
    setting.setValue("key", name);
}

void RegisterPage::loadSettings()
{
    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "Data Foam", "sss");
    passwordCheck = setting.value("key").toString();

}

void RegisterPage::clearSettings()
{
    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "SuperBanking", "EasyFinance");
    setting.beginGroup("TableData");
    setting.remove("");
    setting.endGroup();
}


void RegisterPage::on_pushButton_clicked() //register
{
    QString password = ui->lineEdit->text();
    QString check = ui->lineEdit_2->text();

    if(password.size() <= 7)
    {
        QMessageBox::critical(this, "Password size", "Password should at least be 8 characters long.");
    }
    else
    {
        if(password == check)
        {
            saveSettings(password);
            QMessageBox::information(this, "Register", "Password has been set.");
            clearSettings();
            hide();
        }
        else
            QMessageBox::critical(this, "Password not matched", "Re-entered password does not match password.");
    }

}

RegisterPage::~RegisterPage()
{
    delete ui;
}
