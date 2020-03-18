/*  Errors
 *  case for missing favorite worlds and categories
 *  Case for missing worlds
 *
 *
 */

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
    world = categorize(".wcwf", "worlds/").first();
    category = categorize(".wccf", "worlds/" + world).first();

    // Initializes to create mode
    loadMode(0);
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
}

// Sidebar articles button
// Changes current page to articles page and loads articles
// Only shows articles in current world
void MainWindow::on_articlesB_clicked()
{
    loadFlex("Articles", world + "/" + category, ".wcar");
}

// Combines categorize and retrieveDir methods
QStringList MainWindow::categorize(QString type, QString dir) {
    return categorize(type, retrieveDir(dir));
}

// Private helper method
// creates a list from a set based on extensions
QStringList MainWindow::categorize(QString type, QSet<QString> set) {
    /*  world       .wcwd   0
     *  category    .wcct   1
     *  article     .wcar   2
     *  defWorld    .wcwf   3
     *  defCategory .wccf   4
    */
    QStringList list = {};
    QSet<QString>::iterator i;
    for (i = set.begin(); i != set.end(); ++i) {
        if (i->contains(type) && i->lastIndexOf("s") != i->length() - 1) {
            list << i->split("/").last().remove(type);
        }
    }
    return list;
}

// Private helper method
// Returns a set of all files in the given directory
QSet<QString> MainWindow::retrieveDir(QString dir) {
    QDirIterator it(dir, QDirIterator::Subdirectories);
    QSet<QString> set = QSet<QString>();
    while (it.hasNext()) {
        set.insert(it.next());
    }
    return set;
}

// When an item in the flex list is clicked, something happens depending on the page
// World
//      Sets the selected world to current, filtering all future categories and articles
//      Then redirects to categories page
// Category
//      Shows a filtered list of articles under the category
// Article
//      Opens the article
void MainWindow::on_flexList_itemClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
    if (page == "Worlds") {
        // edit
        if (mode == 1) {
            QFile::rename("worlds/" + world + ".wcwf", "worlds/" + world + ".wcwd");
            QFile::rename("worlds/" + world + ".wcwfs", "worlds/" + world + ".wcwds");
            world = item->text();
            QFile::rename("worlds/" + world + ".wcwd", "worlds/" + world + ".wcwf");
            QFile::rename("worlds/" + world + ".wcwds", "worlds/" + world + ".wcwfs");
            category = categorize(".wccf", "worlds/" + world).first();
            loadEdit(world + ".wcwf");
        // view
        } else if (mode == 2) {
            if (world != item->text()) {
                // Sets selected world to favorite
                QFile::rename("worlds/" + world + ".wcwf", "worlds/" + world + ".wcwd");
                QFile::rename("worlds/" + world + ".wcwfs", "worlds/" + world + ".wcwds");
                world = item->text();
                QFile::rename("worlds/" + world + ".wcwd", "worlds/" + world + ".wcwf");
                QFile::rename("worlds/" + world + ".wcwds", "worlds/" + world + ".wcwfs");
                category = categorize(".wccf", "worlds/" + world).first();
            }
            on_categoriesB_clicked();
        }
    } else if (page == "Categories") {
        // edit
        if (mode == 1) {
            QFile::rename("worlds/" + world + "/" + category + ".wccf", "worlds/" + world + "/" + category + ".wcct");
            QFile::rename("worlds/" + world + "/" + category + ".wccfs", "worlds/" + world + "/" + category + ".wccts");
            category = item->text();
            QFile::rename("worlds/" + world + "/" + category + ".wcct", "worlds/" + world + "/" + category + ".wccf");
            QFile::rename("worlds/" + world + "/" + category + ".wccts", "worlds/" + world + "/" + category + ".wccfs");
            loadEdit(world + "/" + category + ".wccf");
        // view
        } else if (mode == 2) {
            if (category != item->text()) {
                // Sets selected world to favorite
                QFile::rename("worlds/" + world + "/" + category + ".wccf", "worlds/" + world + "/" + category + ".wcct");
                QFile::rename("worlds/" + world + "/" + category + ".wccfs", "worlds/" + world + "/" + category + ".wccts");
                category = item->text();
                QFile::rename("worlds/" + world + "/" + category + ".wcct", "worlds/" + world + "/" + category + ".wccf");
                QFile::rename("worlds/" + world + "/" + category + ".wccts", "worlds/" + world + "/" + category + ".wccfs");
            }
            loadFlex("Articles", world + "/" + category, ".wcar");
        }
    } else if (page == "Articles") {
        // edit
        if (mode == 1) {
            loadEdit(world + "/" + category + "/" + item->text() + ".wcar");
        }
    }
}

// Load world button on worlds page
void MainWindow::on_loadWorld_clicked()
{
    // Includes favorite world
    loadFlex("Worlds", ".wcwd");
    ui->flexList->insertItem(0, world);
}

// 2 parameter load flex
void MainWindow::loadFlex(QString flex, QString type) {
    loadFlex(flex, "", type);
}

// private helper method
// sets up the flex page to its correct page
void MainWindow::loadFlex(QString flex, QString dir, QString type) {
    ui->stackedWidget->setCurrentIndex(1);
    page = flex;
    ui->flexHeader->setText(page);
    ui->flexList->clear();
    ui->flexList->addItems(categorize(type, "worlds/" + dir));
    ui->flexList->sortItems(Qt::AscendingOrder);
}

// Sidebar categories button
// Changes current page to categories page and loads categories
// Only shows categories for selected world
void MainWindow::on_categoriesB_clicked()
{
    loadFlex("Categories", world, ".wcct");
    ui->flexList->insertItem(0, category);
}

// mode 0, 1, 2
// create, edit, view
void MainWindow::on_createB_clicked()
{
    loadMode(0);
}

void MainWindow::on_editB_clicked()
{
    loadMode(1);
}

void MainWindow::on_viewB_clicked()
{
    loadMode(2);
}

void MainWindow::loadMode(int change) {
    if (mode != change) {
        if (mode == 0) {
            ui->createB->setStyleSheet("");
        } else if (mode == 1) {
            ui->editB->setStyleSheet("");
        } else if (mode == 2) {
           ui->viewB->setStyleSheet("");
        }
        mode = change;
        if (mode == 0) {
            ui->createB->setStyleSheet("background-color: rgb(255, 225, 227);");
        } else if (mode == 1) {
            ui->editB->setStyleSheet("background-color: rgb(255, 225, 227);");
        } else if (mode == 2) {
           ui->viewB->setStyleSheet("background-color: rgb(255, 225, 227);");
        }
    }
}

// Sidebar art button
// Creates a list of png and jpg files and changes the page to art
void MainWindow::on_artB_clicked()
{
    QSet<QString> set = retrieveDir("art");

    QStringList list = {};
    QSet<QString>::iterator i;
    for (i = set.begin(); i != set.end(); ++i) {
        if (i->contains(".png")) {
            list << i->split("/").last().remove(".png");
        } else if (i->contains(".jpg")) {
            list << i->split("/").last().remove(".jpg");
        }
    }

    ui->stackedWidget->setCurrentIndex(1);
    page = "Art";
    ui->flexHeader->setText(page);
    ui->flexList->clear();
    ui->flexList->addItems(list);
    ui->flexList->sortItems(Qt::AscendingOrder);
}

// Saves whatever is currently being edited
void MainWindow::on_saveB_clicked()
{
    QFile path(current);
    QFile side(current + "s");
    path.open(QIODevice::WriteOnly);
    side.open(QIODevice::WriteOnly);
    path.QFile::resize(0);
    side.QFile::resize(0);
    QTextDocument document;
    document.setHtml(ui->descBox->toHtml());
    QTextStream out(&path);
    out << document.toHtml();
    document.setHtml(ui->sideBox->toHtml());
    QTextStream out2(&side);
    out2 << document.toHtml();
}

void MainWindow::loadEdit(QString file) {
    current = "worlds/" + file;
    QFile path(current);
    QFile side(current + "s");

    ui->stackedWidget->setCurrentIndex(2);
    ui->titleBox->setText(file.split("/").last().split(".").first());

    path.open(QIODevice::ReadOnly);
    side.open(QIODevice::ReadOnly);
    QTextStream in(&path);
    QTextStream in2(&side);
    QTextDocument document;
    document.setHtml(in.readAll());
    ui->descBox->setText(document.toHtml());
    document.setHtml(in2.readAll());
    ui->sideBox->setText(document.toHtml());

    //path.QFile::resize(0);
    //stream << document.toHtml();

    ui->classMenu->setCurrentIndex(2);
}
