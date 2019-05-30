#ifndef ADD_GLOBAL_H
#define ADD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ADD_LIBRARY)
#  define ADDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ADDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ADD_GLOBAL_H
