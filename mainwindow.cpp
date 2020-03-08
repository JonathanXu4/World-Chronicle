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
    qApp->exit();
}

void MainWindow::on_worldsB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    if (!QDir("worlds").exists()) {
        QDir().mkdir("worlds");
    }

//    QFileSystemModel *model = new QFileSystemModel;
//    model->setRootPath(QDir::currentPath());
//    QTreeView *tree = new QTreeView(ui->treeView);
//    tree->setModel(model);
//    qDebug() << QDir("worlds").absolutePath();
//    tree->setRootIndex(model->index(QDir("worlds").absolutePath()));

}

void MainWindow::on_articlesB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    QDirIterator it("worlds", QDirIterator::Subdirectories);
    QSet<QString> *set = new QSet<QString>();
    while (it.hasNext()) {
        set->insert(it.next());
//        QFile f(it.next());
//        f.open(QIODevice::ReadOnly);
//        qDebug() << f.fileName() << f.readAll().trimmed().toDouble() / 1000 << "MHz";
    }
    QStringList list = categorize(1, *set);
    ui->articleList->addItems(list);
    //ui->treeView->update();
}

QStringList MainWindow::categorize(int type, QSet<QString> set) {
    /*  world       .wcwd   1
     *  category    .wcct   2
     *  article     .wcar   3
    */
    QString extension;
    if (type == 0) {
        extension = ".wcwd";
    } else if (type == 1) {
        extension = ".wcct";
    } else if (type == 2) {
        extension = ".wcar";
    }
    QStringList list = {};
    QSet<QString>::iterator i;
    for (i = set.begin(); i != set.end(); ++i) {
        if (i->contains(extension)) {
            list << i->split("/").last().remove(extension);
        }
    }
    return list;

}

void MainWindow::on_articleList_itemClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
}
