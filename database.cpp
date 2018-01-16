#include "database.h"

Database::Database()
{
    QSqlDatabase dbTemp = QSqlDatabase::addDatabase("QSQLITE");
    dbTemp.setHostName("nihongo");
    dbTemp.setDatabaseName("VokableList");
    dbTemp.setUserName("deutsu");
    dbTemp.setPassword("nihongo");
    db = &dbTemp;
    if (!db->open()) {
        QMessageBox::critical(0, "Cannot open database",
                                "Unable to establish a database connection.\n"
                                "This example needs SQLite support. Please read "
                                "the Qt SQL driver documentation for information how "
                                "to build it.\n\n"
                                "Click Cancel to exit.", QMessageBox::Cancel);
        exit(1337);
    }
    else
        createDatabase();
}
Database::~Database()
{
    delete db;
}
void Database::createDatabase(){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS vokable(vokable_id INTEGER PRIMARY KEY,vokabellist_id INTEGER,deutsch TEXT, japanisch TEXT);");
    query.exec("CREATE TABLE IF NOT EXISTS vokableList(vokableList_id INTEGER  PRIMARY KEY, vokabellistname TEXT);");
}

int Database::getLastVokabellistId(){
    QSqlQuery query;
    query.prepare("Select vokableList_id From vokableList order by vokableList_id DESC LIMIT 1");
    query.exec();
    int returnInt;
    while (query.next()) {
        returnInt = query.value(0).toInt();
    }
    return returnInt;
}

void Database::insertVokabeln(int key,QString deutsch,QString jap){
    QSqlQuery query;
    query.prepare("INSERT INTO vokable(vokabellist_id,deutsch,japanisch) VALUES ("+QString::number(key)+",'"+deutsch+"','"+jap+"')");
    query.exec();
}

void Database::updateOrCreateVokablList(int key,QString name){
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO vokableList(vokableList_id,vokabellistname) VALUES ("+QString::number(key)+",'"+name+"')");
    query.exec();
}

QStringList Database::getVokableListen(){
    QStringList returnValue;
    QSqlQuery query;
    query.prepare("Select vokabellistname From vokableList order by vokableList_id ASC");
    query.exec();
    while (query.next()) {
        returnValue.append(query.value(0).toString());
    }
    return returnValue;
}

QMap<QString,QString> Database::getVokablen(QList<int> ids){
    QMap<QString,QString> returnValue;
    foreach(int id,ids)
    {
        QSqlQuery query;
        query.prepare("Select deutsch,japanisch From vokable where vokabellist_id="+QString::number(id));
        query.exec();
        while (query.next()) {
            QString test = query.value(1).toString();
            returnValue.insert(query.value(0).toString(),test);
        }
    }
    return returnValue;
}

