#ifndef ALPM_BACKEND_H
#define ALPM_BACKEND_H

#include <alpm.h>
#include <QStringList>
#include <QVector>

bool ab_setup_libalpm();
bool ab_cleanup_libalpm();
QVector<QStringList> ab_get_local_package_list();

#endif // ALPM_BACKEND_H
