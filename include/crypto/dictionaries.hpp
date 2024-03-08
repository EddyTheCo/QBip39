#pragma once
#include <QObject>
#include <QStringList>

#include <QtCore/QtGlobal>

#if defined(WINDOWS_QBIP39)
# define QBIP39_EXPORT Q_DECL_EXPORT
#else
#define QBIP39_EXPORT Q_DECL_IMPORT
#endif

namespace qcrypto {
namespace qwords {

enum Language:quint8
{
    En,
    Es,
    It,
    Ja,
    Ko
};

template<Language lg>
class Dictionary: public QStringList
{
public:
    Dictionary();
};

}
}
