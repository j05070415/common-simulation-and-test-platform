#ifndef RESOURCEMANAGER_GLOBAL_H
#define RESOURCEMANAGER_GLOBAL_H

#if defined(RESOURCEMANAGER_LIBRARY)
#  define RESOURCEMANAGERSHARED_EXPORT __declspec(dllexport)
#else
#  define RESOURCEMANAGERSHARED_EXPORT
#endif

#endif // RESOURCEMANAGER_GLOBAL_H
