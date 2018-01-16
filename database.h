#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QMap>
#include <QList>

class Database : public QObject
{
    Q_OBJECT
public:
    Database();
    ~Database();
    QStringList getVokableListen();
    QMap<QString,QString> getVokablen(QList<int> ids);
public slots:
    int getLastVokabellistId();
    void insertVokabeln(int key,QString deutsch,QString jap);
    void updateOrCreateVokablList(int key,QString name);


private:
    QSqlDatabase *db;
    void createDatabase();

};

#endif // DATABASE_H
