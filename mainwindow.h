#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // current world
    QString world;
    // current version of flex page
    QString page;
    // create, edit, view
    int mode;
    // Currently edited object
    QString current;
    // Current category
    QString category;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_exitB_clicked();

    void on_worldsB_clicked();

    void on_articlesB_clicked();

    void on_flexList_itemClicked(QListWidgetItem *item);

    void on_loadWorld_clicked();

    void on_categoriesB_clicked();

    void on_createB_clicked();

    void on_editB_clicked();

    void on_viewB_clicked();

    void on_artB_clicked();

    void on_saveB_clicked();

    void on_newWorld_clicked();

    void on_createC_clicked();

private:
    Ui::MainWindow *ui;

    QStringList categorize(QString type, QSet<QString> set);

    QStringList categorize(QString type, QString dir);

    QSet<QString> retrieveDir(QString dir);

    void loadFlex(QString flex, QString type);

    void loadFlex(QString flex, QString dir, QString type);

    void loadMode(int change);

    void loadEdit();

    void loadView();

    void loadCreate(int type);

    QStringList loadArt();

    QString toClass(QString ext);

};
#endif // MAINWINDOW_H








