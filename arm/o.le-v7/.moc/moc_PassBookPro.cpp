/****************************************************************************
** Meta object code from reading C++ file 'PassBookPro.hpp'
**
** Created: Wed Jan 2 13:44:54 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/PassBookPro.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PassBookPro.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PassBook[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      42,   18,   10,    9, 0x02,
      93,   71,    9,    9, 0x02,
     165,  123,    9,    9, 0x02,
     234,  227,    9,    9, 0x02,
     252,  123,    9,    9, 0x02,
     306,    9,    9,    9, 0x02,
     337,  321,   10,    9, 0x02,
     366,  321,  362,    9, 0x02,
     399,  394,    9,    9, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_PassBook[] = {
    "PassBook\0\0QString\0objectName,defaultValue\0"
    "getValueFor(QString,QString)\0"
    "objectName,inputValue\0"
    "saveValueFor(QString,QString)\0"
    "classes,title,description,marks,weighting\0"
    "updateSelectedRecord(QString,QString,QString,QString,QString)\0"
    "search\0setClass(QString)\0"
    "addNewRecord(QString,QString,QString,QString,QString)\0"
    "deleteRecord()\0classes,desired\0"
    "countGrades(QString,int)\0int\0"
    "numberOfGrades(QString,int)\0path\0"
    "findIndexPath(QVariantList)\0"
};

void PassBook::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PassBook *_t = static_cast<PassBook *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->getValueFor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: _t->saveValueFor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->updateSelectedRecord((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 3: _t->setClass((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->addNewRecord((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 5: _t->deleteRecord(); break;
        case 6: { QString _r = _t->countGrades((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: { int _r = _t->numberOfGrades((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: _t->findIndexPath((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PassBook::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PassBook::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PassBook,
      qt_meta_data_PassBook, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PassBook::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PassBook::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PassBook::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PassBook))
        return static_cast<void*>(const_cast< PassBook*>(this));
    return QObject::qt_metacast(_clname);
}

int PassBook::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
