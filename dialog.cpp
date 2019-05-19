#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QtSql/QSqlError>




QString saveName;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->comboBox->setEnabled(false);
    ui->PathEdit->setEnabled(false);
    ui->toolButton->setEnabled(false);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(OkClicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel),SIGNAL(clicked()), SLOT(close()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(onButtonSend()));
//    dbd = QSqlDatabase::addDatabase("QMYSQL");
//    dbd.setPort(3306);
//    dbd.setHostName("127.0.0.1");
//    dbd.setDatabaseName("MyDiary");
//    dbd.setUserName("root");
//    dbd.setPassword("1234567");
//    if(!dbd.open())
//    {
//        qDebug() << dbd.lastError().text(); // Вывод ошибки на консоль
//        return;
//    }
//        else
//        {
//            qDebug() << "Success!";
//        }
//    model = new QSqlTableModel(this, dbd);
//    model->setTable("cities");
//        model->select();
//        ui->comboBox->setModel(model);
//        ui->comboBox->setModelColumn(0);
ui->comboBox->addItem("Без корня", 0);
ui->comboBox->addItem("Главный", 1);
    ui->radioButton->setChecked(true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::OkClicked()
    {
        emit FilePath(ui->PathEdit->text());
    close();
}


void Dialog::onButtonSend()
{
    saveName = ui->nameEdit->text();
    int comboBox;
    bool choiceMain = true;
    if(ui->radioButton_2->isChecked())
    {
        choiceMain = false;

    }
    else
    {
        if(ui->comboBox->currentIndex() == 0)
        {
            comboBox = 0;
        }
        else if (ui->comboBox->itemText(1) == "Main") {
            comboBox = 1;
        }
    }



    emit sendData(ui->nameEdit->text(), comboBox, choiceMain, ui->PathEdit->text());
    ui->comboBox->addItem(saveName, comboBox);
    close();

}

void Dialog::on_radioButton_clicked()
{
    ui->comboBox->setEnabled(false);
    ui->PathEdit->setEnabled(false);
    ui->toolButton->setEnabled(false);
    ui->nameEdit->setEnabled(true);
}

void Dialog::on_radioButton_2_clicked()
{

    ui->comboBox->setEnabled(true);
    ui->PathEdit->setEnabled(true);
    ui->toolButton->setEnabled(true);
    ui->nameEdit->setEnabled(false);
}


void Dialog::on_toolButton_clicked()
{
    ///////////////////////////////Старая версия/////////////////////////////
    /* filesearch *fs = new filesearch(this);
    fs->show();
    connect(fs, SIGNAL(sysFilePath(QString)), this, SLOT(recieveSysFilePath(QString)));*/

    ///////////////////////////Новая версия///////////////////////////////////////////////////
    const QString fileName = QFileDialog::getOpenFileName(this);
    ui->PathEdit->setText(fileName);
}

void Dialog::recieveSysFilePath(const QString &str)
{
    ui->PathEdit->setText(str);
}
