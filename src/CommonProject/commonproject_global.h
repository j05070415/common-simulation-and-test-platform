#ifndef COMMONPROJECT_GLOBAL_H
#define COMMONPROJECT_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QVector>

#ifdef COMMONPROJECT_LIB
# define COMMONPROJECT_EXPORT Q_DECL_EXPORT
#else
# define COMMONPROJECT_EXPORT Q_DECL_IMPORT
#endif

#include "typedefs.h"

typedef QVector<ItemInfor> ItemsInfor;

#endif // COMMONPROJECT_GLOBAL_H
