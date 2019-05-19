#include "searchwords.h"
#include "ui_searchwords.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QRegExp>

searchWords::searchWords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchWords)
{
    ui->setupUi(this);

}

searchWords::~searchWords()
{
    delete ui;
}

void searchWords::on_button_search_clicked()
{

    emit sendSearch(ui->lineSearch->text());
}

void searchWords::on_button_replace_clicked()
{

}
