// Tabbed pane project template
#include "PassBookPro.hpp"
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include "databaseAssist.h"
#include <bb/cascades/GroupDataModel>
using namespace bb::cascades;
using namespace bb::data;

namespace bb
{
namespace cascades
{
class QmlDocument;
class Page;
class NavigationPane;
class ListView;
class GroupDataModel;
class TabbedPane;
}
}
PassBook::PassBook(bb::cascades::Application *app)
: QObject(app)
{
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("contextProperty", this);
	dataAssist= new DataAssist();
	QVariantList sqlData = dataAssist->loadDatabase("quotes.db", "grades");
	myDataModel =  new GroupDataModel(QStringList() << "title" << "classes");
	myDataModel->insertList(sqlData);
	myDataModel->setGrouping(ItemGrouping::ByFullValue);
	qml->setContextProperty("songsModel", myDataModel);
	saveValueFor("empty","0");
	AbstractPane *root = qml->createRootObject<AbstractPane>();
	app->setScene(root);
}
void PassBook::setClass(QString search) {
	myDataModel->clear();
	myDataModel->insertList(dataAssist->setClass(search));
}
QString PassBook::countGrades(const QString classes, int desired) {
	QString pass=classes;
	double sum=dataAssist->countGrades(pass,desired);
	QString sumString = QString::number(sum);
	//sumString.chop(sumString.size()-5);
	return sumString;
}
int PassBook::numberOfGrades(const QString classes, int desired) {
	QString pass=classes;
	int sum=dataAssist->numberOfGrades(classes,desired);
	return sum;
}
QString PassBook::getValueFor(const QString &objectName, const QString &defaultValue) {
	QSettings settings;

	// If no value has been saved return the value.
	if (settings.value(objectName).isNull()) {
		return defaultValue;
	}

	// Otherwise return the value stored in the settings object.
	return settings.value(objectName).toString();
}
void PassBook::saveValueFor(const QString &objectName, const QString &inputValue) {
	// A new value is saved to the application settings object.
	QSettings settings;
	inputValue.toUpper();
	settings.setValue(objectName, QVariant(inputValue));
}
void PassBook::addNewRecord(const QString &classes, const QString &title, const QString &description, const QString &marks, const QString &weighting)
{
	QVariantMap map;

	map["classes"] = QString(classes);
	map["title"] = QString(title);
	map["description"] = QString(description);
	map["marks"] = QString(marks);
	map["weighting"]= QString(weighting);
	// Add the new item to the database, the insert id is the unique database id which
	// is used for edit and delete functionality.
	insertId = dataAssist->insert(map);

	if (!insertId.isNull()) {
		map["id"] = insertId;
		myDataModel->insert(map);
	}
	myMap=map;
	qWarning() << "checkpoint hhhhhh";
}
void PassBook::updateSelectedRecord(const QString &classes, const QString &title, const QString &description,
		const QString &marks, const QString &weighting)
{
	// Get the item at the selected index, the item that has been updated.
	//QVariantList indexPath = myListView->selected();

	if (!indexPath.isEmpty()) {
		// Get the data item for the selected item so it can be updated.
		QVariantMap itemMapAtIndex = myDataModel->data(indexPath).toMap();

		// Update the data.
		itemMapAtIndex["classes"] = QString(classes);
		itemMapAtIndex["title"]= QString(title);
		itemMapAtIndex["description"] = QString(description);
		itemMapAtIndex["marks"] = QString(marks);
		itemMapAtIndex["weighting"]=QString(weighting);
		// Call the database helper to update the item data and update the model item.
		dataAssist->update(itemMapAtIndex);
		myDataModel->updateItem(indexPath, itemMapAtIndex);
	}
}
void PassBook::findIndexPath(QVariantList path) {
	indexPath=path;
}
void PassBook::deleteRecord()
{
	//QVariantList indexPath = myListView->selected();

	if (!indexPath.isEmpty()) {
		QVariantMap map = myDataModel->data(indexPath).toMap();

		// Delete the item from the database based on id, if successful remove it
		// from the model (which will remove the data from the list).
		if (dataAssist->deleteById(map["id"])) {

			// Delete is the only operation where the logics for updating which item
			// is selected is handled in code.
			// Before the item is removed, we store how many items there are in the
			// category that the item is removed from, we need this to select a new item.
			//QVariantList categoryIndexPath;
			//categoryIndexPath.append(indexPath.first());
			//int childrenInCategory = myDataModel->childCount(categoryIndexPath);

			myDataModel->remove(map);
		}
	}
	else
	{
		if (dataAssist->deleteById(myMap["id"])) {
			myDataModel->remove(myMap);
		}
		else
			qWarning()<< "faileFHAPFEHUAGFLAGBd";
	}
	// After removing the selected item we want another quote to be shown,
	// here we select the quote that is closest to the removed one in the list.
	/*if( childrenInCategory > 1) {

                // If the Category still has items select within the category.
                int itemInCategory = indexPath.last().toInt();

                if(itemInCategory < childrenInCategory - 1) {
                    myListView->select(indexPath);
                } else {
                    // The last item in the category was removed select the new last item.
                    indexPath.replace(1, QVariant(itemInCategory - 1));
                    myListView->select(indexPath);
                }
            } else {
                // If no items left in the category, move to the next category, if there are no more
                // categories below, select the previous, if no items left at all navigate to the list.
                QVariantList lastIndexPath = myDataModel->last();

                if (!lastIndexPath.isEmpty()) {
                    if (indexPath.first().toInt() <= lastIndexPath.first().toInt()) {
                        myListView->select(indexPath);
                    } else {
                        myListView->select(myDataModel->last());
                    }
                }
            }*/


}
