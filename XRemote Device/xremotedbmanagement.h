#ifndef XREMOTEDBMANAGEMENT_H
#define XREMOTEDBMANAGEMENT_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

using namespace std;

/*Create and/or connect to database*/
void _DBConnection(const char* name);

/*Create table*/
void _DBCreateTable(const string tableName);

/*Insert element to table*/
void _DBInsertElement(const string tableName, const string mail, const string password);

/*Delete element*/
void _DBDeleteElement(const string tableName, unsigned int id);

/*Select element by its id*/
void _DBSelectElementById(const string tableName, unsigned int id, const string argument);

/*Select element by its mail address*/
string _DBSelectElementByMail(const string tableName, const string mail);

/*Check if user exist*/
bool _DBCheckElementByMail(const string tableName, const string mail);

/*Print table*/
void _DBPrintTable(const string tableName);

/*Exec example*/
void _DBExecExample();

#endif // XREMOTEDBMANAGEMENT_H
