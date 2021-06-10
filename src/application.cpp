#include "application.h"
#include "mainwindow_ui.h"
#include "alpm.h"
MyWindow::MyWindow()
{
    set_title("Basic application");
    set_default_size(200, 200);
}

int run_application(int argc, char** argv)
{
    auto app = Gtk::Application
        ::create("org.gtkmm.examples.base");
    Glib::RefPtr<Gtk::Builder> builder =
        Gtk::Builder::create_from_file("../mainwindow.ui");
//        Gtk::Builder::create_from_string(
//            (char*)__mainwindow_ui);
    Gtk::Window* mainWindow = nullptr;
    builder->get_widget("window", mainWindow);
    return app->run(*mainWindow, argc, argv);
}
