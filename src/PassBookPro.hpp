// Tabbed pane project template
#ifndef PassBook_HPP_
#define PassBook_HPP_
#include "databaseAssist.h"

#include <bb/cascades/DataModel>
#include <bb/data/SqlDataAccess>
#include <bb/cascades/Event>
#include <bb/cascades/UiObject>
#include <bb/cascades/Control>
#include <bb/cascades/Application>
#include <bb/cascades/NavigationPane>
#include "databaseAssist.h"
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

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class PassBook : public QObject
{
    Q_OBJECT
public:
    PassBook(bb::cascades::Application *app);
    DataAssist *dataAssist;
    GroupDataModel *myDataModel;
    ListView *myListView;
    QVariantMap myMap;
          QVariant insertId;
          QVariantList indexPath;
    Q_INVOKABLE QString getValueFor(const QString &objectName, const QString &defaultValue);
    Q_INVOKABLE void saveValueFor(const QString &objectName, const QString &inputValue);
    Q_INVOKABLE
           void updateSelectedRecord(const QString &classes, const QString &title, const QString &description,
                  const QString &marks, const QString &weighting);
    Q_INVOKABLE
    	void setClass(QString search);
       Q_INVOKABLE
           void addNewRecord(const QString &classes, const QString &title, const QString &description,
                   const QString &marks, const QString &weighting);
       Q_INVOKABLE
           void deleteRecord();
       	   Q_INVOKABLE
       	   QString countGrades(const QString classes, int desired);
       	   Q_INVOKABLE
       	   int numberOfGrades(const QString classes, int desired);
       	   	   Q_INVOKABLE
       	   	   void findIndexPath(QVariantList path);
    virtual ~PassBook() {}
};

#endif /* PassBook_HPP_ */
