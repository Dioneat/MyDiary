#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"
#include <QDialog>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QMainWindow>
#include "filesearch.h"




namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void onButtonSend();

    void OkClicked();

    void recieveSysFilePath(const QString &str);

    void on_toolButton_clicked();

signals:
    void sendData(const QString &nameFile, int comboBox, bool choiceMain, const QString &filePath);

    void FilePath(const QString &str);


private:
    Ui::Dialog *ui;
    MainWindow *mymain;
    QSqlDatabase dbd;
    QSqlTableModel *model;


};

#endif // DIALOG_H
