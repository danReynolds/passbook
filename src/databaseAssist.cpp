#include "databaseAssist.h"
#include <QtSql/QtSql>
#include <bb/data/SqlDataAccess>
using namespace bb::data;

DataAssist::DataAssist() {

}
DataAssist::~DataAssist() {
	if (myDB.isOpen()) {
		QSqlDatabase::removeDatabase(myDBNameWithPath);
		myDB.removeDatabase("QSQLITE");
	}

}
bool DataAssist::copyToFolder(const QString databaseName) {
	QString dataFolder= QDir::homePath();
	QString newFileName = dataFolder + "/" + databaseName; //makes new name for file in data folder
	QFile newFile(newFileName); //makes a new file with that name.

	if (!newFile.exists()) { //checks if that file we just made exists, if not proceed.
		QString appFolder(QDir::homePath());
		appFolder.chop(4); //gets rid of end of original location.
		QString originalFileName = appFolder + "app/native/assets/sql/" + databaseName; //makes original file name
		QFile originalFile(originalFileName); //makes file of original file

		if (originalFile.exists()) {
			return originalFile.copy(newFileName); //returns the original file copied with the new file name.
		}
		else {
			qDebug() << "Failed to copy file";
			return false;
		}
	}
	return true;
}
QVariantList DataAssist::setClass(QString search) {
	QVariantList sqlData;
		QString myDBNameWithPath= "data/quotes.db"; //the string for the location of the NEWLY MOVED database.
		SqlDataAccess sqlDataAccess(myDBNameWithPath); //simple interface for retrieving data from or updating data in an Sql database.
		sqlData = sqlDataAccess.execute("Select * from grades where classes like '%" + search + "%' or title like '%" + search + "%'").value<QVariantList>();
		return sqlData;
}
double DataAssist::countGrades(QString classes, int desired) {
	//sqlQuery.prepare(
	//"UPDATE " + myTable + " SET classes=:classes, title=:title, description=:description, marks=:marks, weighting=:weighting WHERE id=:id");

	//  sqlQuery.bindValue(":classes", map["classes"]);

	const QString pass="SELECT * FROM grades WHERE title='" + classes + "'";
	QSqlQuery query(pass,myDB);
	int fieldNo = query.record().indexOf("marks");
	int fieldNo2= query.record().indexOf("weighting");
	double sum=0;
	double sum2=0;
	double sum3=0;
	double sum4=0;
	while (query.next()) {
		double mark = query.value(fieldNo).toDouble();
		double weighting=query.value(fieldNo2).toDouble();
		sum+=mark;
		sum2+=weighting; //sum of weightings
		sum4+=weighting*(mark/100); //used in weighted average prior to dividing by total of weightings/100
		sum3+=weighting-weighting*(mark/100);
	}
	if (desired==1)
		return 100-sum3; //highest achievable
	else if (desired==2)
		return sum4; //percent earned in class
	else
		return (sum4/sum2*100); //weighted average 50*80/100/50*100
}
int DataAssist::numberOfGrades(QString classes, int desired) {
	const QString pass="SELECT * FROM grades WHERE classes='" + classes + "'";
	QSqlQuery query(pass,myDB);
	int fieldNo = query.record().indexOf("marks");
	int sum=0;
	while (query.next()) {
		QString country = query.value(fieldNo).toString();
		sum+=1;
	}
	return sum;
}
QVariantList DataAssist::loadDatabase(const QString databaseName, const QString table) {
	QVariantList sqlData;
	if (copyToFolder(databaseName)) {
		myDBNameWithPath= "data/" + databaseName; //the string for the location of the NEWLY MOVED database.
		SqlDataAccess sqlDataAccess(myDBNameWithPath); //simple interface for retrieving data from or updating data in an Sql database.
		//uses queries supplied in execute method.
		//Open the data base to enable editing via SQL queries using the non default connection to not conflict with the database connection set up
		//set up by SQLDataAccess.
		myDB= QSqlDatabase::addDatabase("QSQLITE", "database_helper_connection");
		myDB.setDatabaseName(myDBNameWithPath);

		if (!myDB.isValid()) {
			qWarning() << "Could not set data base name probably due to invalid driver.";
			return sqlData;
		}

		bool success = myDB.open();

		if (!success) {
			qWarning() << "Could not open";
			return sqlData;
		}
		if (myDB.tables().contains("grades")) {
			qWarning() << "contains marks database!";
		}
		else {
			qWarning() << "doesNot contain SONGSFINISHED TABLE";
			createTable();
		}
		//data access object, loads all entries in the table and executes the load.
		sqlData = sqlDataAccess.execute("Select * from " + table).value<QVariantList>();

		if (sqlDataAccess.hasError()) {
			DataAccessError err = sqlDataAccess.error();
			qWarning() << "SQL error: type=" << err.errorType() << ": " << err.errorMessage();
			return sqlData;
		}



		myTable=table;

	}
	return sqlData;
}
bool DataAssist::deleteById(QVariant id)
{

	if (id.canConvert(QVariant::String)) {
		QString query = "DELETE FROM " + myTable + " WHERE id=" + id.toString();
		return queryDatabase(query);
	}

	qWarning() << "Failed to delete item with id: " << id;

	return false;
}
bool DataAssist::queryDatabase(const QString query)
{
	// Execute the query.
	QSqlQuery sqlQuery(query, myDB);

	QSqlError err = sqlQuery.lastError();

	if (err.isValid()) {
		qWarning() << "SQL reported an error for query: " << query << " error: "
				<< myDB.lastError().text();
		return false;
	}
	return true;
}
QVariant DataAssist::insert(QVariantMap map)
{

	QSqlQuery sqlQuery(myDB);

	// The Queries are hardcoded for the quotes database. We use the prepare version of
	// the Qt SDK API's since they are safer then constructing queries ourselves.
	// For example a ' sign inside a quote is tricky to handle if one does not bind
	// the values like this.
	myTable="grades";
	sqlQuery.prepare("INSERT INTO " + myTable + " (classes, title, description, marks, weighting)"
			"VALUES(:class, :title, :description,:marks, :weighting)");
	sqlQuery.bindValue(":classes", map["classes"]);
	sqlQuery.bindValue(":title",map["title"]);
	sqlQuery.bindValue(":description", map["description"]);
	sqlQuery.bindValue(":marks", map["marks"]);
	sqlQuery.bindValue(":weighting",map["weighting"]);
	sqlQuery.exec();
	QSqlError err = sqlQuery.lastError();
	return sqlQuery.lastInsertId();
}

bool DataAssist::update(QVariantMap map)
{
	QSqlQuery sqlQuery(myDB);

	// Query hard coded for the quotes database.
	sqlQuery.prepare(
			"UPDATE " + myTable + " SET classes=:classes, title=:title, description=:description, marks=:marks, weighting=:weighting WHERE id=:id");

	sqlQuery.bindValue(":classes", map["classes"]);
	sqlQuery.bindValue(":title",map["title"]);
	sqlQuery.bindValue(":description", map["description"]);
	sqlQuery.bindValue(":marks", map["marks"]);
	sqlQuery.bindValue(":weighting",map["weighting"]);
	sqlQuery.bindValue(":id", map["id"].toString());
	sqlQuery.exec();

	QSqlError err = sqlQuery.lastError();

	if (!err.isValid()) {
		return true;
	}

	qWarning() << "SQL reported an error : " << err.text();

	return false;
}

bool DataAssist::createTable() {
	bool ret =false;

	if (myDB.isOpen()) {
		QSqlQuery query(myDB);
		ret = query.exec("create table grades"
				"(id integer primary key, "
				"classes varchar(60), "
				"title varchar(60), "
				"description varchar(600), "
				"marks int(100), "
				"weighting int(100))");

		qWarning() << "success";
	}
	qWarning() << "wentThrough";
	return ret;
}

