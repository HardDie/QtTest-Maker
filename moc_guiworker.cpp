/****************************************************************************
** Meta object code from reading C++ file 'guiworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "guiworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guiworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GUIWorker_t {
    QByteArrayData data[13];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUIWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUIWorker_t qt_meta_stringdata_GUIWorker = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GUIWorker"
QT_MOC_LITERAL(1, 10, 13), // "setTestString"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "text"
QT_MOC_LITERAL(4, 30, 5), // "index"
QT_MOC_LITERAL(5, 36, 16), // "returnToMainMenu"
QT_MOC_LITERAL(6, 53, 13), // "setTestModeQA"
QT_MOC_LITERAL(7, 67, 13), // "setTestModeAQ"
QT_MOC_LITERAL(8, 81, 14), // "setTestModeMix"
QT_MOC_LITERAL(9, 96, 17), // "setTestModeTypeQA"
QT_MOC_LITERAL(10, 114, 17), // "setTestModeTypeAQ"
QT_MOC_LITERAL(11, 132, 18), // "setTestModeTypeMix"
QT_MOC_LITERAL(12, 151, 12) // "nextTestStep"

    },
    "GUIWorker\0setTestString\0\0text\0index\0"
    "returnToMainMenu\0setTestModeQA\0"
    "setTestModeAQ\0setTestModeMix\0"
    "setTestModeTypeQA\0setTestModeTypeAQ\0"
    "setTestModeTypeMix\0nextTestStep"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUIWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   65,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    0,   67,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GUIWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUIWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setTestString((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->returnToMainMenu(); break;
        case 2: _t->setTestModeQA(); break;
        case 3: _t->setTestModeAQ(); break;
        case 4: _t->setTestModeMix(); break;
        case 5: _t->setTestModeTypeQA(); break;
        case 6: _t->setTestModeTypeAQ(); break;
        case 7: _t->setTestModeTypeMix(); break;
        case 8: _t->nextTestStep(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GUIWorker::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIWorker::setTestString)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GUIWorker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIWorker::returnToMainMenu)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GUIWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GUIWorker.data,
    qt_meta_data_GUIWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GUIWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUIWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUIWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GUIWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GUIWorker::setTestString(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUIWorker::returnToMainMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
