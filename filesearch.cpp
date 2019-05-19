#include "filesearch.h"
#include "ui_filesearch.h"
#include <QDateTime>
#include <QMessageBox>
QString filePath;
filesearch::filesearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filesearch)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries); // Отображатся будут только директории с фалами
    model->setRootPath(""); // Указываем путь к корневой папке
    ui->listFileSystem->setModel(model);

}

filesearch::~filesearch()
{
    delete ui;
}


void filesearch::on_listFileSystem_doubleClicked(const QModelIndex &index)
{
    QListView* listView = (QListView*)sender();
      QFileInfo fileInfo = model->fileInfo(index);// доступ к информации о директории и файлам
      //при щелчке по элементу ".." отображаем содержимое родительской директории
      if (fileInfo.fileName() == ".."){
        QDir dir = fileInfo.dir();
        dir.cdUp(); // Возвращаемся к родительской директории
        listView->setRootIndex(model->index(dir.absolutePath())); // Принимаем все значения dir к model и передаем указываем папку в List View
      }
      //при щелчке по элементу "." отображаем корневые элементы файловой структуры
      else if (fileInfo.fileName() == ".")
      {
        listView->setRootIndex(model->index(""));
      }
      //при щелчке по элементу соответствущему директории, отображаем содержимое этой директории
      else if (fileInfo.isDir())
      {
        listView->setRootIndex(index);

      }
      if(fileInfo.fileName().contains(".txt"))
      {
      ui->editFile->setText(fileInfo.filePath());
      emit sysFilePath(ui->editFile->text());
      close();
      }

}

void filesearch::on_listFileSystem_clicked(const QModelIndex &index)
{
    QListView* listView = (QListView*)sender();
      QFileInfo fileInfo = model->fileInfo(index);
    ui->editFile->setText(fileInfo.filePath());
}

void filesearch::on_selectButton_clicked()
{
    if(ui->editFile->text().contains(".txt"))
    {
    emit sysFilePath(ui->editFile->text());
    close();
    }
    else {
        QMessageBox::critical(this, "HEY", "Поддерживается только формат .txt!", QMessageBox::Ok);
    }
}
