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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStringList categorize(int index, QSet<QString> set);

private slots:
    void on_actionExit_triggered();

//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

    void on_exitB_clicked();

    void on_worldsB_clicked();

    void on_articlesB_clicked();

    void on_articleList_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
