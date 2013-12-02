/****************************************************************************
** Meta object code from reading C++ file 'ER_TableView.h'
**
** Created: Mon Dec 2 14:29:25 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ER_TableView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ER_TableView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ER_TableView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ER_TableView[] = {
    "ER_TableView\0\0doubleClickedEvent(QModelIndex)\0"
};

void ER_TableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ER_TableView *_t = static_cast<ER_TableView *>(_o);
        switch (_id) {
        case 0: _t->doubleClickedEvent((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ER_TableView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ER_TableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_ER_TableView,
      qt_meta_data_ER_TableView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ER_TableView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ER_TableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ER_TableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ER_TableView))
        return static_cast<void*>(const_cast< ER_TableView*>(this));
    if (!strcmp(_clname, "ER_Observer"))
        return static_cast< ER_Observer*>(const_cast< ER_TableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int ER_TableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
