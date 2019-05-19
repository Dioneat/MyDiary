#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QTreeWidgetItem>
#include <QDialog>
#include <QWidget>
#include <QFileSystemModel>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTreeWidget>
#include <QFileDialog>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDateTime>
//#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:

private slots:
    void on_action_triggered();

    void recieveData(const QString &nameFile, int comboBox, bool choiceMain, const QString &filePath);

    void ReadToFile(const QString &filePath);

    void on_searchWords_triggered();

    void on_action_4_triggered();
    void on_action_2_triggered();

    void on_action_5_triggered();

    void recieveSearchLine(const QString &searchString);



    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *itm, int column);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

    void on_action_3_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_8_triggered();

    void on_action_13_triggered(bool checked);

    void on_action_14_triggered(bool checked);

    void on_action_15_triggered(bool checked);

    void on_action_10_triggered();

    void on_treeWidget_collapsed(const QModelIndex &index);

    void on_treeWidget_expanded(const QModelIndex &index);

signals:
        void sysFilePath(const QString &str);
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QFileSystemModel *FSmodel;
    QString currentFile;



};

#endif // MAINWINDOW_H
