#include <alpm.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cassert>
#include <regex>

alpm_handle_t* g_libalpm_handle;
using namespace std;

#define print_function_header() printf("***\n%s\n***\n", __FUNCTION__)

//taken from https://git.archlinux.org/pacman.git/tree/src/pacman/callback.c
/* Callback to handle notifications from the library */
void cb_log(void *ctx, alpm_loglevel_t level, const char *fmt, va_list args)
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


bool setup_libalpm()
{
    const char* default_root_dir = "/";
    const char* default_db_path = "/var/lib/pacman";
    alpm_errno_t alpm_err;
    g_libalpm_handle = alpm_initialize(default_root_dir,
                                       default_db_path,
                                       &alpm_err);
    if (!g_libalpm_handle) {
        cerr << "failed to initialize the alpm library\n";
        return false;
    }
    //set libalpm callbacks
    alpm_option_set_logcb(g_libalpm_handle, cb_log, NULL);
//    alpm_option_set_dlcb(handle, cb_download, NULL);
//    alpm_option_set_eventcb(handle, cb_event, NULL);
//    alpm_option_set_questioncb(handle, cb_question, NULL);
//    alpm_option_set_progresscb(handle, cb_progress, NULL);
    return true;
}

bool cleanup_libalpm()
{
    print_function_header();
    int ret;
    ret = alpm_release(g_libalpm_handle);
    if (ret != 0) {
        cerr << "alpm_released returned non-zero";
        return false;
    }
    return true;
}

bool test_search_for_package(const char* name)
{
    print_function_header();
    //check local database first

    alpm_db_t* db_local = alpm_get_localdb(g_libalpm_handle);
    alpm_list_t* i;
    alpm_pkg_t* pkg = nullptr;
    cout << "Looking for \"" << name << "\"\n";
    for (i=alpm_db_get_pkgcache(db_local);
         i != nullptr;
         i = alpm_list_next(i)) {
        pkg = (alpm_pkg_t*)i->data;
        auto package_name = string(alpm_pkg_get_name(pkg));
        auto r = regex(name, regex::ECMAScript | regex::icase);
        if (regex_match(package_name, r) == 1) {
            cout << package_name << '\n'
                 << alpm_pkg_get_desc(pkg);
        }
    }
    return true;
}

bool test_regex_match()
{
    string s("hooray");
    regex r("hooray");
    return regex_match(s, r) == 1;
}

int main()
{
//    assert(test_regex_match());
    assert(setup_libalpm());
    assert(test_search_for_package("gtk"));
    assert(cleanup_libalpm());
    exit(0);
}
