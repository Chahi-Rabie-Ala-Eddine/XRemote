#include "xremotedbmanagement.h"
#include "xremoteauthentication.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include <QCryptographicHash>

#include <QDebug>

using namespace std;

/*Create and/or connect to database*/
void _DBConnection(const char* name)
{
    //CHECK IF NAME IS IN WHITE LIST MADE ONLY BY ALPHABETIC LETTERS

    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName(name);

        if(!db.open())
            qWarning() << "ERROR : " << db.lastError().text();
    }
    else
        qWarning() << "ERROR : no driver " << DRIVER << " available !";
}

/*Create table*/
void _DBCreateTable(const string tableName){

    QSqlQuery query(QString::fromStdString("CREATE TABLE " + tableName + " (id INTEGER PRIMARY KEY, mail TEXT UNIQUE, password TEXT)"));

    if(!query.isActive())
        qWarning() << "Table creation error : " << query.lastError().text();

}

/*Insert element to table*/
void _DBInsertElement(const string tableName, const string mail, const string password){

    QSqlQuery query;

    if(!query.exec(QString::fromStdString("INSERT INTO " + tableName + "(mail, password) VALUES('" + mail + "','" + QString(QCryptographicHash::hash((password.c_str()), QCryptographicHash::Keccak_512).toHex()).toUtf8().constData() + "')")))
        qWarning() << "Inesrtion error : " << query.lastError().text();
}

/*Delete element*/
void _DBDeleteElement(const string tableName, unsigned int id){

    QSqlQuery query;
    query.prepare(QString::fromStdString("DELETE FROM " + tableName + " WHERE id = ?"));
    query.addBindValue(id);

    if(!query.exec())
        qWarning() << "Deletion error : " << query.lastError().text();
}

/*Select element*/
void _DBSelectElementById(const string tableName, unsigned int id, const string argument) {

    QSqlQuery query;
    query.prepare(QString::fromStdString("SELECT " + argument + " FROM " + tableName + " WHERE id = ?"));
    query.addBindValue(id);

    if(!query.exec())
        qWarning() << "Selection error : " << query.lastError().text();

    if(query.first())
        printf("Argument = [%s]\n", query.value(0).toString().toUtf8().constData());

    else
        printf("Element not found\n");
}

/*Select element*/
string _DBSelectElementByMail(const string tableName, const string mail) {

    QSqlQuery query;
    query.prepare(QString::fromStdString("SELECT password FROM " + tableName + " WHERE mail = '" + mail + "'"));

    if(!query.exec())
        qWarning() << "Selection error : " << query.lastError().text();

    if(!query.first())
        qWarning() << "Selection error : " << query.lastError().text();

     return (string)query.value(0).toString().toUtf8().constData();
}

/*Check if user exist*/
bool _DBCheckElementByMail(const string tableName, const string mail){

    QSqlQuery query;
    query.prepare(QString::fromStdString("SELECT * FROM " + tableName + " WHERE mail = '" + mail + "'"));

    if(!query.exec())
        qWarning() << "Selection error : " << query.lastError().text();

    return (query.first()) ? true : false;
}

/*Print table*/
void _DBPrintTable(const string tableName){

    QSqlQuery query(QString::fromStdString("SELECT * FROM " + tableName));

    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n                                                                 Table : %s\n-----------------------------------------------------------------------------------------------------------------------------------------\n\n",tableName.c_str());

    while (query.next()) {

        QString _id = query.value(0).toString();
        QString _mail = query.value(1).toString();
        QString _password = query.value(2).toString();
        printf("id(%s)\n@mail(%s)\npassword(%s)\n\n",  _id.toUtf8().constData(), _mail.toUtf8().constData(), _password.toUtf8().constData());

    }
}

/*Exec example*/
void _DBExecExample(){

    _DBConnection("./database");
    _DBCreateTable("user");
    _DBInsertElement("user", "aladin@xremote.fr", "mypassword");
    _DBInsertElement("user", "yasmine@xremote.fr", "passpass");
    _DBInsertElement("user", "yanis@xremote.fr", "ihavepass");
    _DBPrintTable("user");

    if(_DBCheckElementByMail("user", "aladin@xremote.fr"))
        printf("Exist !\n");
    else
        printf("Dosnt exist !\n");

    printf("password(%s)\n",_DBSelectElementByMail("user", "yanis@xremote.fr").c_str());

    if(_CheckSignIn("aladin@xremote.fr", "mypassword"))
        printf("Connected !");

    else
        printf("Connection fail !");

    if(_CheckSignIn("aladin@xremote.fr", "pass"))
        printf("Connected !\n");

    else
        printf("Connection fail !\n");

    system("rm database");
}
