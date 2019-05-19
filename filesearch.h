#ifndef FILESEARCH_H
#define FILESEARCH_H

#include <QDialog>
#include <QWidget>
#include <QFileSystemModel>
#include <QDir>

namespace Ui {
class filesearch;
}

class filesearch : public QDialog
{
    Q_OBJECT

public:
    explicit filesearch(QWidget *parent = nullptr);

    ~filesearch();

private slots:
    void on_listFileSystem_doubleClicked(const QModelIndex &index);

    void on_listFileSystem_clicked(const QModelIndex &index);

    void on_selectButton_clicked();

signals:
    void sysFilePath(const QString &str);

private:
    Ui::filesearch *ui;
    QFileSystemModel *model;
};

#endif // FILESEARCH_H
