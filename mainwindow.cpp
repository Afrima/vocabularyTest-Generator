#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vokabelList = new VokabelList();
    database = new Database();
    QObject::connect(ui->plus,&QPushButton::clicked,this,&MainWindow::addVokabelList);
    QObject::connect(ui->gen,&QPushButton::clicked,this,&MainWindow::generatList);
    QObject::connect(vokabelList,&VokabelList::saveVokableListe,database,&Database::updateOrCreateVokablList);
    QObject::connect(vokabelList,&VokabelList::saveVokablen,database,&Database::insertVokabeln);
    QObject::connect(vokabelList,&VokabelList::save,this,&MainWindow::updateUi);
    updateUi();
}

MainWindow::~MainWindow()
{
    delete vokabelList;
    delete ui;
}

void MainWindow::addVokabelList(){
    int lastId = ui->listWidget->count();
    vokabelList->setListId(lastId+1);
    vokabelList->show();
}


void MainWindow::updateUi(){
    ui->listWidget->clear();
    ui->listWidget->addItems(database->getVokableListen());
   // ui->listWidget->sortItems();
}

void MainWindow::generatList(){
    QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();
    QList<int> listIDs;
    foreach (QListWidgetItem* item, selectedItems) {
        listIDs.append(ui->listWidget->row(item)+1);
    }
    QMap<QString,QString> ids = database->getVokablen(listIDs);
    QStringList deuVok;
    foreach (QString deu, ids.keys()) {
        deuVok.append(deu);
    }
    for(int i=0;i<deuVok.length();i++){
        int rand1=qrand() % deuVok.length();
        int rand2=qrand() % deuVok.length();
        deuVok.swap(rand1,rand2);
        for(int i=0;i<deuVok.length();i++){
            int rand1=qrand() % deuVok.length();
            int rand2=qrand() % deuVok.length();
            deuVok.swap(rand1,rand2);
            for(int i=0;i<deuVok.length();i++){
                int rand1=qrand() % deuVok.length();
                int rand2=qrand() % deuVok.length();
                deuVok.swap(rand1,rand2);
            }
        }
    }
    QFile file("genVokTest.csv");
    if(file.exists())
        file.remove();
    QTextStream stream( &file );
    stream.setCodec("UTF-8");
    if ( file.open(QIODevice::ReadWrite) )
    {
        int breakCountDown = ui->spinBox->value();
        int countDown=0;
        if(ui->comboBox->currentIndex()==0){
            int rnd;
            foreach (QString deu, deuVok) {
                rnd = qrand() % ((1 + 1) - 0) + 0;
                if(rnd)
                    stream  << ";" << ids.value(deu) << endl;
                else
                    stream << deu << ";" << endl;
                countDown++;
                if(breakCountDown <= countDown)
                    break;
            }
        }
        else if(ui->comboBox->currentIndex() == 1){
            foreach (QString deu, deuVok) {
                    stream  << ";" << ids.value(deu) << endl;
                    countDown++;
                    if(breakCountDown <= countDown)
                        break;
            }
        }
        else if(ui->comboBox->currentIndex() == 2){
            foreach (QString deu, deuVok) {
                    stream  << deu << ";"  << endl;
                    countDown++;
                    if(breakCountDown <= countDown)
                        break;
            }
        }
        stream << ";"<< " / "<<breakCountDown;
        stream << endl << endl << endl <<"Loesungen"<<endl;
        countDown=0;
        foreach (QString deu, deuVok) {
                stream  << deu << ";"<< ids.value(deu) << endl;
                countDown++;
                if(breakCountDown <= countDown)
                    break;
        }

    }
    file.close();
}
