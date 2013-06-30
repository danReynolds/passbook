#ifndef _DATABASEASSIST_H_
#define _DATABASEASSIST_H_

#include <QtSql/QtSql>
#include <bb/data/SqlDataAccess>
using namespace bb::data;

class DataAssist {
public:
	DataAssist();
	~DataAssist();
	QVariantList loadDatabase(const QString databaseName, const QString table);
	bool copyToFolder(const QString databaseName);
	bool queryDatabase(const QString query);
	QVariant insert(QVariantMap map);
	bool update(QVariantMap map);
	bool createTable();
	bool deleteById(QVariant id);
	QVariantList setClass(QString search);
	double countGrades(const QString classes, int desired);
	int numberOfGrades(const QString classes, int desired);
private:

	QSqlDatabase myDB;
	QString myTable;
	QString myDBNameWithPath;
};
#endif
