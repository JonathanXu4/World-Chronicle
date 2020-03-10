#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bannerWorld->setPixmap(QPixmap ("C:/Users/Chari/Desktop/Qt/WorldChronicle/banner.png"));
    ui->worldIcon->setPixmap(QPixmap ("C:/Users/Chari/Desktop/Qt/WorldChronicle/logo2.png").scaled(360, 360, Qt::KeepAspectRatio));
    world = categorize(3, retrieveDir("worlds/")).first();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// File menu exit button, closes program
void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

// Sidebar exit button, closes program
void MainWindow::on_exitB_clicked()
{
    qApp->exit();
}

// Sidebar worlds button
// Changes current page to worlds page
void MainWindow::on_worldsB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    if (!QDir("worlds").exists()) {
        QDir().mkdir("worlds");
    }

//    Obsolete tree model code
//    QFileSystemModel *model = new QFileSystemModel;
//    model->setRootPath(QDir::currentPath());
//    QTreeView *tree = new QTreeView(ui->treeView);
//    tree->setModel(model);
//    qDebug() << QDir("worlds").absolutePath();
//    tree->setRootIndex(model->index(QDir("worlds").absolutePath()));

}

// Sidebar articles button
// Changes current page to articles page and loads articles
void MainWindow::on_articlesB_clicked()
{
    loadFlex("Articles", 2);
}

// Private helper method, creates a list from a set
// based on extensions
QStringList MainWindow::categorize(int type, QSet<QString> set) {
    /*  world       .wcwd   0
     *  category    .wcct   1
     *  article     .wcar   2
     *  default     .wcwf   3
    */
    QString extension;
    if (type == 0) {
        extension = ".wcwd";
    } else if (type == 1) {
        extension = ".wcct";
    } else if (type == 2) {
        extension = ".wcar";
    } else if (type == 3) {
        extension = ".wcwf";
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

// Returns a set of all files in the given directory
QSet<QString> MainWindow::retrieveDir(QString dir) {
    QDirIterator it(dir, QDirIterator::Subdirectories);
    QSet<QString> set = QSet<QString>();
    while (it.hasNext()) {
        set.insert(it.next());
//        QFile f(it.next());
//        f.open(QIODevice::ReadOnly);
//        qDebug() << f.fileName() << f.readAll().trimmed().toDouble() / 1000 << "MHz";
    }
    return set;
}

// Article selection on article page
void MainWindow::on_flexList_itemClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
    if (page == "Worlds") {
        if (world != item->text()) {
            // Sets selected world to favorite
            QString newW = item->text();
            QFile::rename("worlds/" + world + ".wcwf", "worlds/" + world + ".wcwd");
            world = item->text();
            QFile::rename("worlds/" + world + ".wcwd", "worlds/" + world + ".wcwf");
        }
            on_categoriesB_clicked();
    } else if (page == "Categories") {
        loadFlex("Articles", world + "/" + item->text(), 2);
    }
}

// Load world button on worlds page
void MainWindow::on_loadWorld_clicked()
{
    // Includes favorite world
    loadFlex("Worlds", 0);
    ui->flexList->insertItem(0, world);
}

// 2 parameter load flex
void MainWindow::loadFlex(QString flex, int type) {
    loadFlex(flex, "", type);
}

// private helper method
// sets up the flex page to its correct page
void MainWindow::loadFlex(QString flex, QString dir, int type) {
    ui->stackedWidget->setCurrentIndex(1);
    page = flex;
    ui->flexHeader->setText(page);
    ui->flexList->clear();
    ui->flexList->addItems(categorize(type, retrieveDir("worlds/" + dir)));
    ui->flexList->sortItems(Qt::AscendingOrder);
}

// Sidebar categories button
// Changes current page to categories page and loads categories
// Only shows categories for selected world
void MainWindow::on_categoriesB_clicked()
{
    loadFlex("Categories", world, 1);
}
