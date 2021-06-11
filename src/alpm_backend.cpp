#include "alpm_backend.h"
#include <QDebug>

alpm_handle_t* g_libalpm_handle;

//taken from https://git.archlinux.org/pacman.git/tree/src/pacman/callback.c
/* Callback to handle notifications from the library */
void ab_cb_log(void *ctx, alpm_loglevel_t level, const char *fmt, va_list args)
{
    (void)ctx;
    if(!fmt || strlen(fmt) == 0) {
        return;
    }

    //    if(on_progress) {
    //        char *string = NULL;
    //        pm_vasprintf(&string, level, fmt, args);
    //        if(string != NULL) {
    //            output = alpm_list_add(output, string);
    //        }
    //    } else {
    //        pm_vfprintf(stderr, level, fmt, args);
    //    }
    //the strings end with newline
    vfprintf(stderr, fmt, args);
    //fprintf(stderr, "\n");
}


bool ab_setup_libalpm()
{
    const char* default_root_dir = "/";
    const char* default_db_path = "/var/lib/pacman";
    alpm_errno_t alpm_err;
    g_libalpm_handle = alpm_initialize(default_root_dir,
                                       default_db_path,
                                       &alpm_err);
    if (!g_libalpm_handle) {
        qDebug() << "failed to initialize the alpm library\n";
        return false;
    }
    //set libalpm callbacks
    alpm_option_set_logcb(g_libalpm_handle, ab_cb_log, NULL);
    //    alpm_option_set_dlcb(handle, cb_download, NULL);
    //    alpm_option_set_eventcb(handle, cb_event, NULL);
    //    alpm_option_set_questioncb(handle, cb_question, NULL);
    //    alpm_option_set_progresscb(handle, cb_progress, NULL);
    return true;
}
bool ab_cleanup_libalpm()
{
    int ret;
    ret = alpm_release(g_libalpm_handle);
    if (ret != 0) {
        qDebug() << "alpm_released returned non-zero";
        return false;
    }
    return true;
}
QVector<QStringList> ab_get_local_package_list()
{
    QVector<QStringList> list;
    QStringList tmpList;
    alpm_db_t* db_local = alpm_get_localdb(g_libalpm_handle);
    alpm_list_t* i;
    alpm_pkg_t* pkg = nullptr;
    //cout << "Looking for \"" << name << "\"\n";
    for (i=alpm_db_get_pkgcache(db_local);
         i != nullptr;
         i = alpm_list_next(i)) {
        pkg = (alpm_pkg_t*)i->data;
        QString package_name = alpm_pkg_get_name(pkg);
        QString package_desc = alpm_pkg_get_desc(pkg);
        tmpList.clear();
        tmpList << package_name << package_desc;
        list.append(tmpList);
    }
    return list;
}
