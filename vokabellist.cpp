#include "vokabellist.h"
#include "ui_vokabellist.h"

VokabelList::VokabelList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VokabelList)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,405);
    ui->tableWidget->setColumnWidth(1,405);
    QObject::connect(ui->plus,&QPushButton::clicked,this,&VokabelList::addVokable);

    QObject::connect(ui->save,&QPushButton::clicked,this,&VokabelList::saveVokable);
    QObject::connect(ui->cancel,&QPushButton::clicked,this,&VokabelList::cancel);
}

VokabelList::~VokabelList()
{
    delete ui;
}

void VokabelList::addVokable(){
    int rows = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rows+1);
}

void VokabelList::saveVokable(){
    emit saveVokableListe(listId,ui->lineEdit->text());
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        emit saveVokablen(listId,ui->tableWidget->item(i,0)->text(),ui->tableWidget->item(i,1)->text());
    }
    emit save();
    this->close();
}

void VokabelList::cancel(){
    this->close();
}

void VokabelList::setListId(int id){
    listId = id;
}
