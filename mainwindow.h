#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString world;
    QString page;
    QString category;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

    void on_exitB_clicked();

    void on_worldsB_clicked();

    void on_articlesB_clicked();

    void on_flexList_itemClicked(QListWidgetItem *item);

    void on_loadWorld_clicked();

    void on_categoriesB_clicked();

private:
    Ui::MainWindow *ui;

    QStringList categorize(int index, QSet<QString> set);

    QSet<QString> retrieveDir(QString dir);

    void loadFlex(QString flex, int type);

    void loadFlex(QString flex, QString dir, int type);

};
#endif // MAINWINDOW_H
