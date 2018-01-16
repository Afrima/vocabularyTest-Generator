#ifndef VOKABELLIST_H
#define VOKABELLIST_H

#include <QDialog>
#include <QInputDialog>
#include <QDir>

namespace Ui {
class VokabelList;
}

class VokabelList : public QDialog
{
    Q_OBJECT

public:
    explicit VokabelList(QWidget *parent = 0);
    ~VokabelList();
    void setListId(int id);

public slots:
    void addVokable();
    void saveVokable();
    void cancel();

private:
    Ui::VokabelList *ui;
    int listId=0;
signals:
    void saveVokablen(int key,QString deutsch,QString jap);
    void saveVokableListe(int key,QString name);
    void save();
};

#endif // VOKABELLIST_H
