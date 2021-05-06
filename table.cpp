#include "table.h"
#include "ui_table.h"

using namespace std;
QT_CHARTS_USE_NAMESPACE

Table::Table(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Table), test(nullptr)
{
    ui->setupUi(this);

    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "SuperBanking", "EasyFinance");
    setting.beginGroup("TableData");

    bool fileExists = false;
    if ((setting.contains("ColumnCount")))
    {
        fileExists = true;
    }
    setting.endGroup();

    if (fileExists)
        loadSettings();
    else
    {
        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Category"));
        ui->tableWidget->setItem(1, 0, checkBoxItem);
    }

}

void Table::on_pushButton_clicked() // insert row
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void Table::on_pushButton_2_clicked() // insert column
{
    ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
    QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
    checkBoxItem->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(1, ui->tableWidget->columnCount() - 1, checkBoxItem);
    ui->tableWidget->setItem(0, ui->tableWidget->columnCount() - 1, new QTableWidgetItem("Category"));
}

void Table::on_pushButton_3_clicked() // Generate Button
{

    //Error Checking for missing number in data
    vector<int> *checkBox = new vector<int>();
    vector<int> rowUsedList;

    int rowEntryUp = 0;
    int rowEntryDown = 0;

    for(int column = 0; column < ui->tableWidget->columnCount(); column++)
    {
        if (Qt::Checked == ui->tableWidget->item(1, column)->checkState()) // checks if box is checked or not
        {
            checkBox->push_back(column);

            rowEntryUp = ui->tableWidget->rowCount() - 1;
            rowEntryDown = ui->tableWidget->rowCount() - 1;

            for(int row = 2; row < ui->tableWidget->rowCount(); row++) // data starts on third row
            {
                QTableWidgetItem *current = ui->tableWidget->item(row, column);
                if (!current || current->text().isEmpty())
                {
                    rowEntryUp = row;
                    break;
                }
            }

            bool end = false;
            for(int row = ui->tableWidget->rowCount() - 1; row >= 2; row--) //y
            {
                QTableWidgetItem *current = ui->tableWidget->item(row, column);
                if (!(!current || current->text().isEmpty()))
                {

                    if(rowEntryDown == row)
                        end = true;
                    else
                        rowEntryDown = row + 1; // to reach the last blank and not the last appearance of a number

                    break;
                }
            }

            if(rowEntryUp != rowEntryDown)
            {
                messageInformation(QStringLiteral("Entry not filled in column: %1").arg(column + 1), 2);
                return;
            }

            if(!end)
                rowUsedList.push_back(rowEntryDown);
            else
                rowUsedList.push_back(rowEntryDown + 1);

        }
    }


   std::vector<std::vector<QString>> xAxis;
   std::vector<std::vector<QString>> yAxis;

   test = new vector<vector<QString>>;
   testNames = new QVector<QString>;
   int sizeCheck = checkBox->size();
   if(sizeCheck != 0)
   {
       for(int column = 0, index = 0; column < ui->tableWidget->columnCount(); column++) //x
       {
           vector<QString> x;
           int rowIndex = 0;
           if(sizeCheck == 0)
               break;
           else if (checkBox->at(index) != column)
               continue;
           else
           {
               rowIndex = index;
               index++;
               sizeCheck--;
           }

           QTableWidgetItem *current = ui->tableWidget->item(0, column);
           if (!(!current || current->text().isEmpty()))
           {
               testNames->push_back(current->text());
           }
           else
               testNames->push_back(" ");

           for(int row = 2; row < rowUsedList.at(rowIndex); row++)
           {

               QTableWidgetItem *current = ui->tableWidget->item(row, column);
               QString value = current->data(Qt::DisplayRole).toString();

                x.push_back(value);
           }

           if(xAxis.size() == yAxis.size())
               xAxis.push_back(x);
           else
               yAxis.push_back(x);

           test->push_back(x);

       }

       QString text = ui->comboBox->currentText();


       if(text.toStdString() == "Line Series")
       {
           if(xAxis.size() == yAxis.size())
           {
                for(unsigned int check = 0; check < xAxis.size(); check++)
                {
                    if(xAxis.at(check).size() != yAxis.at(check).size())
                    {
                        messageInformation(QStringLiteral("Entry not filled for corresponding x,y values for x - axis # %1").arg(check + 1), 2);
                        return;
                    }

                }
           }
           else
           {
               messageInformation(QStringLiteral("y-axis not found for corresponding x-axis # %1").arg(xAxis.size()), 2);
               return;
           }

           newWindows = new Form(xAxis, yAxis, testNames, line);
           delete newWindows;
           newWindows = nullptr;
       }
       else if(text.toStdString() == "Bar Series")
       {
           newWindows = new Form(test, testNames, bar);
           delete newWindows;
           newWindows = nullptr;
       }
       else if(text.toStdString() == "Horizontal Bar Series")
       {
           newWindows = new Form(test, testNames, hBar);
           delete newWindows;
           newWindows = nullptr;
       }
       else if (text.toStdString() == "Scatter Series")
       {
           if(xAxis.size() == yAxis.size())
           {
                for(unsigned int check = 0; check < xAxis.size(); check++)
                {
                    if(xAxis.at(check).size() != yAxis.at(check).size())
                    {
                        messageInformation(QStringLiteral("Entry not filled for corresponding x,y values for x - axis # %1").arg(check + 1), 2);
                        return;
                    }

                }
           }
           else
           {
               messageInformation(QStringLiteral("y-axis not found for corresponding x-axis # %1").arg(xAxis.size()), 2);
               return;
           }
           newWindows = new Form(xAxis, yAxis, testNames, scatter);
           delete newWindows;
           newWindows = nullptr;

       }
       else if (text.toStdString() == "Pie Series")
       {

           newWindows = new Form(test, testNames, pie);
           delete newWindows;
           newWindows = nullptr;

       }
       else if (text.toStdString() == "Box and Whisker Series")
       {
           newWindows = new Form(test, testNames, box);
           delete newWindows;
           newWindows = nullptr;
       }
       else if (text.toStdString() == "Area Series")
       {
           if(xAxis.size() == yAxis.size())
           {
                for(unsigned int check = 0; check < xAxis.size(); check++)
                {
                    if(xAxis.at(check).size() != yAxis.at(check).size())
                    {
                        messageInformation(QStringLiteral("Entry not filled for corresponding x,y values for x - axis # %1").arg(check + 1), 2);
                        return;
                    }

                }
           }
           else
           {
               messageInformation(QStringLiteral("y-axis not found for corresponding x-axis # %1").arg(xAxis.size()), 2);
               return;
           }

           newWindows = new Form(xAxis, yAxis, testNames, area);
           delete newWindows;
           newWindows = nullptr;
       }
       else if (text.toStdString() == "Line Bar Series")
       {
           newWindows = new Form(test, testNames, lineBar);
           delete newWindows;
           newWindows = nullptr;
       }
       else if (text.toStdString() != "Select options...")
           QMessageBox::information(this, "Nothing", "Nothing Yet");

   }

}

void Table::on_pushButton_4_clicked()
{
    if(ui->tableWidget->columnCount() != 1)
        ui->tableWidget->removeColumn(ui->tableWidget->columnCount() - 1);
}

void Table::on_comboBox_activated(const QString &arg1) // Hide select options...
{
    arg1.size();
    qobject_cast<QListView *>(ui->comboBox->view())->setRowHidden(0, true);

}

void Table::on_pushButton_6_clicked() // Save
{
    saveTableData();
}

void Table::on_pushButton_5_clicked() // Load
{
    loadSettings();
}

void Table::loadSettings()
{
    //QSettings setting("SuperBanking", "EasyFinance"); // company, application
    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "SuperBanking", "EasyFinance");
    setting.beginGroup("TableData");


    bool fileExists = false;
    if ((setting.contains("ColumnCount")))
    {
        fileExists = true;
    }

    if(fileExists)
    {

        int columnCount = setting.value("ColumnCount").toInt();
        int rowCount = setting.value("RowCount").toInt();


        ui->tableWidget->setRowCount(rowCount); // resets the table
        ui->tableWidget->setColumnCount(columnCount);

        for(int column = 0; column < ui->tableWidget->columnCount(); column++)
        {
            //sets the current state
            std::string saveCheck = "1" + std::to_string(column);
            QString qstr = QString::fromStdString(saveCheck);

            if(Qt::Checked == setting.value(qstr))
            {
                QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
                checkBoxItem->setCheckState(Qt::Checked);
                ui->tableWidget->setItem(1, column, checkBoxItem);
            }
            else
            {
                 QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
                checkBoxItem->setCheckState(Qt::Unchecked);
                ui->tableWidget->setItem(1, column, checkBoxItem);
            }

            //sets the text in row 0
            saveCheck = "0" + std::to_string(column);
            qstr = QString::fromStdString(saveCheck);

            if(setting.value(qstr).toString() != "Empty")
            {
                ui->tableWidget->setItem(0, column , new QTableWidgetItem(setting.value(qstr).toString()));
            }
            else
            {
                ui->tableWidget->removeCellWidget(0, column);
            }

            //sets the data
            for(int row = 2; row < ui->tableWidget->rowCount(); row++)
            {
                std::string saveCheck = std::to_string(row) + std::to_string(column);
                QString qstr = QString::fromStdString(saveCheck);

                if (setting.value(qstr).toString() != "Empty")
                {
                    ui->tableWidget->setItem(row, column , new QTableWidgetItem(setting.value(qstr).toString()));
                }
                else
                    ui->tableWidget->removeCellWidget(row, column);
            }
        }
    }

    setting.endGroup();

    qDebug() << "Loaded";

}

void Table::saveTableData()
{
    QSettings setting(QSettings::IniFormat, QSettings::UserScope, "SuperBanking", "EasyFinance"); // company, application
    setting.beginGroup("TableData");
    setting.setValue("ColumnCount", ui->tableWidget->columnCount());
    setting.setValue("RowCount", ui->tableWidget->rowCount());

    for(int column = 0; column < ui->tableWidget->columnCount(); column++)
    {
        //Stores the current state from row of checkboxes
        std::string saveCheck = "1" + std::to_string(column);
        QString qstr = QString::fromStdString(saveCheck);
        setting.setValue(qstr, ui->tableWidget->item(1, column)->checkState());

        //Stores the current name from row of each text box
        saveCheck = "0" + std::to_string(column);
        qstr = QString::fromStdString(saveCheck);

        QTableWidgetItem *current = ui->tableWidget->item(0, column);
        if (!current || current->text().isEmpty())
        {
            setting.setValue(qstr, "Empty");
            qDebug() << "Empty";
        }
        else
        {
            setting.setValue(qstr, ui->tableWidget->item(0, column)->text());
            //qDebug() << ui->tableWidget->item(0, column)->text();
        }


        for(int row = 2; row < ui->tableWidget->rowCount(); row++)
        {
            QTableWidgetItem *current = ui->tableWidget->item(row, column);
            std::string saveCheck = std::to_string(row) + std::to_string(column);
            QString qstr = QString::fromStdString(saveCheck);

            if (!current || current->text().isEmpty())
            {
                setting.setValue(qstr, "Empty"); // sets empty spaces to zero
            }
            else
            {
                setting.setValue(qstr, current->text());
            }

        }
    }

    setting.endGroup();

    qDebug() << "Saved";

}

void Table::on_pushButton_7_clicked() // remove row
{
    if(ui->tableWidget->rowCount() != 1)
        ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);

}

void Table::on_comboBox_currentTextChanged(const QString &arg1) // information on current plot
{
    if(arg1.toStdString() == "Line Series")
        messageInformation("Assume first checked category to be x-axis values.\n"
                           "Second category to be y-axis values.", 1);
    else if(arg1.toStdString() == "Bar Series")
        messageInformation("Assume first checked category to be x-axis values.", 1);
    else if(arg1.toStdString() == "Horizontal Bar Series")
        messageInformation("Assume first checked category to be y-axis values.", 1);
    else if (arg1.toStdString() == "Scatter Series")
        messageInformation("Assume first checked category to be x-axis values.\n"
                           "Second category to be y-axis values.", 1);
    else if (arg1.toStdString() == "Pie Series")
        messageInformation("Assume each checked category to be a pie slice.", 1);
    else if (arg1.toStdString() == "Box and Whisker Series")
        messageInformation("Assume each checked category to have an individual box and whisker series.", 1);
    else if (arg1.toStdString() == "Area Series")
        messageInformation("Assume first checked category to be x-axis values.\n"
                           "Second category to be y-axis values.", 1);
    else if (arg1.toStdString() == "Line Bar Series")
        messageInformation("Assume 1st checked category to be x-axis.\n"
                            "2nd checked category to be y-axis for line series.\n"
                            "All other checked categories are y-xais values for bar series.", 1);
}

void Table::messageInformation(const QString &t_display, const int t_mType)
{
    switch (t_mType)
    {
    case 1:
    {
        QMessageBox::information(this, "Information", t_display);
        break;
    }
    case 2:
    {
        QMessageBox::critical(this, "Error", t_display);
        break;
    }
    }
}

Table::~Table()
{
    delete ui;
    if(test != nullptr)
        delete test;
}

void Table::on_pushButton_8_clicked() // clear
{
    ui->tableWidget->clearContents();
    for(int column = 0; column < ui->tableWidget->columnCount(); column++)
    {

        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(1, column, checkBoxItem);
    }

}
