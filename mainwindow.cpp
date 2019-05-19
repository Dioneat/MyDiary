#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchwords.h"
#include "dialog.h"
#include <QFontDialog>
//#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
//#if QT_CONFIG(printer)
//#if QT_CONFIG(printdialog)
#include <QtPrintSupport/QPrinter>
//#endif // QT_CONFIG(printdialog)
#include <QtPrintSupport/QPrintDialog>
//#endif // QT_CONFIG(printer)
//#endif // QT_PRINTSUPPORT_LIB

QTreeWidgetItem *itm = new QTreeWidgetItem(2);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    FSmodel = new QFileSystemModel(this);
    FSmodel->setFilter(QDir::QDir::AllEntries); // Отображатся будут только директории с фалами
    FSmodel->setRootPath(""); // Указываем путь к корневой папке
    ui->listView->setModel(FSmodel);

    itm->setText(0, "Главный");
    ui->treeWidget->addTopLevelItem(itm);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setPort(3306);
    db.setHostName("127.0.0.1");
    db.setDatabaseName("MyDiary");
    db.setUserName("root");
    db.setPassword("1234567");
    model = new QSqlTableModel(this, db);
        /*ui->comboBox->setModel(model);
        ui->comboBox->setModelColumn(0)*/;
    if(!db.open())
    {
        qDebug() << db.lastError().text(); // Вывод ошибки на консоль
        return;
    }
        else
        {
            qDebug() << "Success!";
        }

    for(int i = 0; i < ui->treeWidget->columnCount(); ++i)
            ui->treeWidget->resizeColumnToContents(i);
    //или применить только к последней
    ui->treeWidget->resizeColumnToContents(ui->treeWidget->columnCount() - 1);
//#if !QT_CONFIG(printer)
//    ui->actionPrint->setEnabled(false);
//#endif

//#if !QT_CONFIG(clipboard)
//    ui->actionCut->setEnabled(false);
//    ui->actionCopy->setEnabled(false);
//    ui->actionPaste->setEnabled(false);
//#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Добавление нового виджета и/или файла */
void MainWindow::on_action_triggered()
{
    Dialog *dw = new Dialog(this);
    dw->show();
    connect(dw, SIGNAL(FilePath(QString)), this, SLOT(ReadToFile(QString)));
    connect(dw, SIGNAL(sendData(QString, int, bool, QString)), this, SLOT(recieveData(QString, int, bool, QString)));


}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QListView* listView = (QListView*)sender();
      QFileInfo fileInfo = FSmodel->fileInfo(index);// доступ к информации о директории и файлам
      //при щелчке по элементу ".." отображаем содержимое родительской директории
      if (fileInfo.fileName() == ".."){
        QDir dir = fileInfo.dir();
        dir.cdUp(); // Возвращаемся к родительской директории
        listView->setRootIndex(FSmodel->index(dir.absolutePath())); // Принимаем все значения dir к model и передаем указываем папку в List View
      }
      //при щелчке по элементу "." отображаем корневые элементы файловой структуры
      else if (fileInfo.fileName() == ".")
      {
        listView->setRootIndex(FSmodel->index(""));
      }
      //при щелчке по элементу соответствущему директории, отображаем содержимое этой директории
      else if (fileInfo.isDir())
      {
        listView->setRootIndex(index);

      }
      if(fileInfo.fileName().contains(".txt"))
      {

          ui->statusBar->showMessage(fileInfo.filePath());
          QString filePath = fileInfo.filePath();
          QFile mFile(filePath);
          if(!mFile.open(QFile::ReadOnly | QFile::Text))
             {

          }
          else
          {
              QTextStream stream(&mFile);
              QString buffer = stream.readAll();
              ui->textEdit->setText(buffer);
              mFile.flush();
              mFile.close();

          }
//      ui->editFile->setText(fileInfo.filePath());
//      emit sysFilePath(ui->editFile->text());
//      close();
      }
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QListView* listView = (QListView*)sender();
      QFileInfo fileInfo = FSmodel->fileInfo(index);

     if(fileInfo.fileName().contains(".txt"))
     {
         ui->statusBar->showMessage(fileInfo.filePath());
         QString filePath = fileInfo.filePath();
         QFile lFile(filePath);
         if(!lFile.open(QFile::ReadOnly | QFile::Text))
            {

         }
         else
         {
             QTextStream stream(&lFile);
             QString buffer = stream.readAll();
             ui->textEdit->setText(buffer);
             lFile.flush();
             lFile.close();

         }
     }
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *itm, int column = 0)
{
    ui->statusBar->showMessage(ui->treeWidget->currentItem()->text(0));
    QString filePath = ui->treeWidget->currentItem()->text(0);
    QFile mFile(filePath);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
       {

    }
    else
    {
        QTextStream stream(&mFile);
        QString buffer = stream.readAll();
        ui->textEdit->setText(buffer);
        mFile.flush();
        mFile.close();

    }

}

void MainWindow::ReadToFile(const QString &filePath)
{

        QFile mFile(filePath);
        if(!mFile.open(QFile::ReadOnly | QFile::Text))
           {

           }
        else
        {
            QTextStream stream(&mFile);
            QString buffer = stream.readAll();
            ui->textEdit->setText(buffer);
            mFile.flush();
            mFile.close();

        }

}

void MainWindow::on_searchWords_triggered()
{
    searchWords *sw = new searchWords(this);
    sw->show();
    connect(sw, SIGNAL(sendSearch(QString)), this, SLOT(recieveSearchLine(QString)));
}


void MainWindow::recieveData(const QString &nameFile, int comboBox, bool choiceMain, const QString &filePath)
{
    QSqlQuery query = QSqlQuery(db);
    QFile mFile(filePath);
    QTextStream stream(&mFile);

    if(choiceMain == false)
    {
        if(!(filePath == ""))
        {
            if(comboBox == 0)
            {
                QTreeWidgetItem *itm1 = new QTreeWidgetItem(2);
                ui->treeWidget->addTopLevelItem(itm1);
                itm1->setText(0, filePath);
                itm->setSelected(false);
                itm1->setSelected(false);
            }
            else
            {
                QTreeWidgetItem *child = new QTreeWidgetItem(2);
                child->setText(0, filePath);
                itm->addChild(child);
            }



        }
        else
        {
            QMessageBox::critical(this, "ТАК-С, ТАК-С", "Вы не вписали путь к файлу при его создании!");


        }
    }
    else
    {
       if(!(nameFile == ""))
       {
            QTreeWidgetItem *itm2 = new QTreeWidgetItem(2);
            ui->treeWidget->addTopLevelItem(itm2);
            itm2->setText(0, nameFile);
            //comboBox++;
       }
       else
       {
           QMessageBox::warning(this, "ВНИМАНИЕ!", "Вы не вписали наименование заголовка!");
       }
    }

    ui->statusBar->showMessage(nameFile);
}

/* Удаление виджетов */
void MainWindow::on_action_2_triggered()
{
    if(!(ui->treeWidget->currentItem()->text(0) == "Главный"))
    {
        ui->treeWidget->currentItem()->setHidden(true);
        ui->textEdit->clear();
    }
    else {
        QMessageBox::critical(this, "ВЫ ПОЙМАНЫ С ПОЛИЧНЫМ!!", "Главный корень нельзя удалить. Даже не пытайтесь!", tr("Нисколечки не пытайтесь, ни-ни-ни!"));
    }
}
/* Сохранение в указанном пути */
void MainWindow::on_action_4_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как ...");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка!", "Нельзя сохранить файл, ошибка: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}

/* Создание нового файла */
void MainWindow::on_action_5_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "ЭЙ!", "Хотите ли вы сохранить изменения? В ином случае, Ваши данные будут удалены", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как ...");
        QFile file(fileName);

        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Ошибка!", "Нельзя сохранить файл, ошибка: " + file.errorString());
            return;
        }
        currentFile = fileName;
        setWindowTitle(fileName);
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();

        ui->textEdit->clear();

        ui->treeWidget->addTopLevelItem(itm);
        itm->setText(0, "Новый файл");
    }
    else {
        ui->textEdit->clear();

        ui->treeWidget->addTopLevelItem(itm);
        itm->setText(0, "Новый файл");
    }
}

void MainWindow::recieveSearchLine(const QString &searchString)
{

    QTextDocument *document = ui->textEdit->document();
    bool found = false;
    document->undo();

    if (searchString.isEmpty()) {
        QMessageBox::information(this, tr("Поисковое поле пустое"),
                                 tr("Поисковое поле пустое. "
                                    "Пожалуйста, введите искомое слово и нажмите \"Поиск!\""));
    } else {
        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);
        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::red);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
            highlightCursor = document->find(searchString, highlightCursor,
                                             QTextDocument::FindWholeWords);

            if (!highlightCursor.isNull()) {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight,
                                             QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

        cursor.endEditBlock();

        if (found == false) {
            QMessageBox::information(this, tr("Слово не найденo"),
                                     tr("Извините, но искомое слово не было найдено."));
        }
    }
}



void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
        ui->statusBar->showMessage(ui->treeWidget->currentItem()->text(0));
        QString filePath = ui->treeWidget->currentItem()->text(0);
        QFile mFile(filePath);
        if(!mFile.open(QFile::ReadOnly | QFile::Text))
           {

        }
        else
        {
            QTextStream stream(&mFile);
            QString buffer = stream.readAll();
            ui->textEdit->setText(buffer);
            mFile.flush();
            mFile.close();

        }


}

void MainWindow::on_action_3_triggered()
{
    QString fileName;

    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Сохранить");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка!", "Нелья сохранить файл, ошибка: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_action_6_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_7_triggered()
{
    ui->textEdit->redo();
}



void MainWindow::on_action_8_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void MainWindow::on_action_13_triggered(bool checked)
{
    checked ? ui->textEdit->setFontWeight(QFont::Bold) :
           ui->textEdit->setFontWeight(QFont::Normal);
}

void MainWindow::on_action_14_triggered(bool checked)
{
    ui->textEdit->setFontItalic(checked);
}

void MainWindow::on_action_15_triggered(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
}

void MainWindow::on_action_10_triggered()
{
//#if QT_CONFIG(printer)
//    QPrinter printDev;
////#if QT_CONFIG(printdialog)
//    QPrintDialog dialog(&printDev, this);
//    if (dialog.exec() == QDialog::Rejected)
//        return;
////#endif // QT_CONFIG(printdialog)
//    ui->textEdit->print(&printDev);
//#endif // QT_CONFIG(printer)
}


void MainWindow::on_treeWidget_collapsed(const QModelIndex &index)
{
   ui->treeWidget->resizeColumnToContents(index.column());
}

void MainWindow::on_treeWidget_expanded(const QModelIndex &index)
{
        ui->treeWidget->resizeColumnToContents(index.column());
}
