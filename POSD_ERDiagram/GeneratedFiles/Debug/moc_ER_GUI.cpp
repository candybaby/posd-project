/****************************************************************************
** Meta object code from reading C++ file 'ER_GUI.h'
**
** Created: Thu Dec 26 16:04:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ER_GUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ER_GUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ER_GUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      17,    7,    7,    7, 0x08,
      33,    7,    7,    7, 0x08,
      54,    7,    7,    7, 0x08,
      79,    7,    7,    7, 0x08,
     106,    7,    7,    7, 0x08,
     130,    7,    7,    7, 0x08,
     160,    7,    7,    7, 0x08,
     167,    7,    7,    7, 0x08,
     174,    7,    7,    7, 0x08,
     187,    7,    7,    7, 0x08,
     193,    7,    7,    7, 0x08,
     200,    7,    7,    7, 0x08,
     208,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ER_GUI[] = {
    "ER_GUI\0\0browse()\0saveComponent()\0"
    "saveComponentAsXml()\0pointerGroupClicked(int)\0"
    "changeToAddAttributeMode()\0"
    "changeToAddEntityMode()\0"
    "changeToAddRelationShipMode()\0undo()\0"
    "redo()\0deleteItem()\0cut()\0copy()\0"
    "paste()\0showAboutDialog()\0"
};

void ER_GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ER_GUI *_t = static_cast<ER_GUI *>(_o);
        switch (_id) {
        case 0: _t->browse(); break;
        case 1: _t->saveComponent(); break;
        case 2: _t->saveComponentAsXml(); break;
        case 3: _t->pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeToAddAttributeMode(); break;
        case 5: _t->changeToAddEntityMode(); break;
        case 6: _t->changeToAddRelationShipMode(); break;
        case 7: _t->undo(); break;
        case 8: _t->redo(); break;
        case 9: _t->deleteItem(); break;
        case 10: _t->cut(); break;
        case 11: _t->copy(); break;
        case 12: _t->paste(); break;
        case 13: _t->showAboutDialog(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ER_GUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ER_GUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ER_GUI,
      qt_meta_data_ER_GUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ER_GUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ER_GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ER_GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ER_GUI))
        return static_cast<void*>(const_cast< ER_GUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ER_GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
