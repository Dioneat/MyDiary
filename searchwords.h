#ifndef SEARCHWORDS_H
#define SEARCHWORDS_H

#include <QDialog>

namespace Ui {
class searchWords;
}

class searchWords : public QDialog
{
    Q_OBJECT

public:
    explicit searchWords(QWidget *parent = nullptr);
    ~searchWords();

public slots:
    void on_button_search_clicked();
signals:

     void sendSearch(const QString &searchString);


private slots:

     void on_button_replace_clicked();

private:
    Ui::searchWords *ui;
};

#endif // SEARCHWORDS_H
