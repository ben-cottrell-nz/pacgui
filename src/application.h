#ifndef APPLICATION_H
#define APPLICATION_H
#include <gtkmm.h>

class MyWindow : public Gtk::Window
{
public:
    MyWindow();
};

int run_application(int, char**);


#endif // APPLICATION_H
