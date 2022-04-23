/****************************************************************************
** Meta object code from reading C++ file 'Chroma2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Chroma2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Chroma2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Chroma2_t {
    QByteArrayData data[22];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Chroma2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Chroma2_t qt_meta_stringdata_Chroma2 = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Chroma2"
QT_MOC_LITERAL(1, 8, 12), // "colorChanged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 31), // "color_onButtonPickScreenClicked"
QT_MOC_LITERAL(4, 54, 14), // "video_openFile"
QT_MOC_LITERAL(5, 69, 10), // "video_play"
QT_MOC_LITERAL(6, 80, 21), // "edit_toleranceChanged"
QT_MOC_LITERAL(7, 102, 16), // "edit_softChanged"
QT_MOC_LITERAL(8, 119, 20), // "edit_defringeChanged"
QT_MOC_LITERAL(9, 140, 22), // "edit_buttonSaveClicked"
QT_MOC_LITERAL(10, 163, 17), // "mediaStateChanged"
QT_MOC_LITERAL(11, 181, 19), // "QMediaPlayer::State"
QT_MOC_LITERAL(12, 201, 5), // "state"
QT_MOC_LITERAL(13, 207, 15), // "positionChanged"
QT_MOC_LITERAL(14, 223, 8), // "position"
QT_MOC_LITERAL(15, 232, 15), // "durationChanged"
QT_MOC_LITERAL(16, 248, 8), // "duration"
QT_MOC_LITERAL(17, 257, 11), // "setPosition"
QT_MOC_LITERAL(18, 269, 11), // "handleError"
QT_MOC_LITERAL(19, 281, 12), // "frameChanged"
QT_MOC_LITERAL(20, 294, 11), // "QVideoFrame"
QT_MOC_LITERAL(21, 306, 5) // "frame"

    },
    "Chroma2\0colorChanged\0\0"
    "color_onButtonPickScreenClicked\0"
    "video_openFile\0video_play\0"
    "edit_toleranceChanged\0edit_softChanged\0"
    "edit_defringeChanged\0edit_buttonSaveClicked\0"
    "mediaStateChanged\0QMediaPlayer::State\0"
    "state\0positionChanged\0position\0"
    "durationChanged\0duration\0setPosition\0"
    "handleError\0frameChanged\0QVideoFrame\0"
    "frame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Chroma2[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   87,    2, 0x0a /* Public */,
       4,    0,   88,    2, 0x0a /* Public */,
       5,    0,   89,    2, 0x0a /* Public */,
       6,    0,   90,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    0,   93,    2, 0x0a /* Public */,
      10,    1,   94,    2, 0x08 /* Private */,
      13,    1,   97,    2, 0x08 /* Private */,
      15,    1,  100,    2, 0x08 /* Private */,
      17,    1,  103,    2, 0x08 /* Private */,
      18,    0,  106,    2, 0x08 /* Private */,
      19,    1,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::LongLong,   14,
    QMetaType::Void, QMetaType::LongLong,   16,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void Chroma2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Chroma2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->color_onButtonPickScreenClicked(); break;
        case 2: _t->video_openFile(); break;
        case 3: _t->video_play(); break;
        case 4: _t->edit_toleranceChanged(); break;
        case 5: _t->edit_softChanged(); break;
        case 6: _t->edit_defringeChanged(); break;
        case 7: _t->edit_buttonSaveClicked(); break;
        case 8: _t->mediaStateChanged((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 9: _t->positionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 10: _t->durationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 11: _t->setPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->handleError(); break;
        case 13: _t->frameChanged((*reinterpret_cast< QVideoFrame(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVideoFrame >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Chroma2::*)(QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Chroma2::colorChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Chroma2::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Chroma2.data,
    qt_meta_data_Chroma2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Chroma2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Chroma2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Chroma2.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Chroma2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Chroma2::colorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
