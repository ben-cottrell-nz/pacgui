#include <QDebug>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "alpm_backend.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ab_setup_libalpm();
    //insert tree items
    QStringList packageTreeViewColumns;
    packageTreeViewColumns << "Name" << "Description";
    QVector<QStringList> list = ab_get_local_package_list();
    ui->treeWidget->setHeaderLabels(packageTreeViewColumns);
    for (auto i : list) {
        qDebug() << i[1];
        QTreeWidgetItem* twi =
            new QTreeWidgetItem(
                ui->treeWidget, i);
        ui->treeWidget->addTopLevelItem(twi);
    }
}

MainWindow::~MainWindow()
{
    ab_cleanup_libalpm();
    delete ui;
}
