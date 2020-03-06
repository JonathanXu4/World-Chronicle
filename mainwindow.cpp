#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QFileSystemModel>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bannerWorld->setPixmap(QPixmap ("C:/Users/Chari/Desktop/Qt/WorldChronicle/banner.png"));
    ui->worldIcon->setPixmap(QPixmap ("C:/Users/Chari/Desktop/Qt/WorldChronicle/logo2.png").scaled(360, 360, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void MainWindow::on_exitB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    //qApp->exit();
}

void MainWindow::on_worldsB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    if (!QDir("worlds").exists()) {
        QDir().mkdir("worlds");
    }
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    QTreeView *tree = new QTreeView(ui->treeView);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir("worlds").path()));

//    QDirIterator it("worlds", QDirIterator::Subdirectories);
//    while (it.hasNext()) {
//        qDebug() << it.next();
//        QFile f(it.next());
//        f.open(QIODevice::ReadOnly);
//        qDebug() << f.fileName() << f.readAll().trimmed().toDouble() / 1000 << "MHz";
//    }
}
