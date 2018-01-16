#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtAlgorithms>
#include <QDebug>
#include "vokabellist.h"
#include "database.h"
#define RAND_MAX 1
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addVokabelList();
    void updateUi();

private:
    Ui::MainWindow *ui;
    VokabelList *vokabelList;
    Database * database;
    void generatList();
};

#endif // MAINWINDOW_H
