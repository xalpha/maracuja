/****************************************************************************
** Meta object code from reading C++ file 'MaracujaMS.hpp'
**
** Created: Wed Apr 3 14:03:03 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../app/include/MaracujaMS.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MaracujaMS.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaracujaMS[] = {

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
      12,   11,   11,   11, 0x0a,
      28,   11,   11,   11, 0x0a,
      52,   11,   11,   11, 0x0a,
      67,   11,   11,   11, 0x0a,
      82,   11,   11,   11, 0x0a,
      99,   11,   11,   11, 0x0a,
     112,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     136,   11,   11,   11, 0x0a,
     156,   11,   11,   11, 0x0a,
     176,   11,   11,   11, 0x0a,
     196,   11,   11,   11, 0x0a,
     216,   11,   11,   11, 0x0a,
     238,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MaracujaMS[] = {
    "MaracujaMS\0\0on_addChannel()\0"
    "on_addDefaultChannels()\0on_loadImage()\0"
    "on_showImage()\0on_calculation()\0"
    "on_saveRGB()\0on_loadMS()\0on_saveMS()\0"
    "on_load_spectrum1()\0on_load_spectrum2()\0"
    "on_show_spectrum1()\0on_show_spectrum2()\0"
    "on_multiply_spectra()\0on_apply_spectrum2()\0"
};

void MaracujaMS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MaracujaMS *_t = static_cast<MaracujaMS *>(_o);
        switch (_id) {
        case 0: _t->on_addChannel(); break;
        case 1: _t->on_addDefaultChannels(); break;
        case 2: _t->on_loadImage(); break;
        case 3: _t->on_showImage(); break;
        case 4: _t->on_calculation(); break;
        case 5: _t->on_saveRGB(); break;
        case 6: _t->on_loadMS(); break;
        case 7: _t->on_saveMS(); break;
        case 8: _t->on_load_spectrum1(); break;
        case 9: _t->on_load_spectrum2(); break;
        case 10: _t->on_show_spectrum1(); break;
        case 11: _t->on_show_spectrum2(); break;
        case 12: _t->on_multiply_spectra(); break;
        case 13: _t->on_apply_spectrum2(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MaracujaMS::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MaracujaMS::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MaracujaMS,
      qt_meta_data_MaracujaMS, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaracujaMS::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaracujaMS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaracujaMS::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaracujaMS))
        return static_cast<void*>(const_cast< MaracujaMS*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MaracujaMS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
