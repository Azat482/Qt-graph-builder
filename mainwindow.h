#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <creatingfunc.h>
#include <QRegExp>
#include <QPainter>
#include <QTextOption>
#include <settings.h>


namespace Ui {
class MainWindow;

}

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    QString O_time;
    QString Exp, ExpCl;
    ~MainWindow();

private slots:

    void G_BUTTON();
    void on_clear_button_clicked();
    void on_pushButton_back_clicked();
    void G_call();
    void SHOW();



    void on_pushButton_22_clicked();

    void on_funcS_currentIndexChanged(int index);

signals:

    void graph_set(QString, int, int, int, double, bool);

private:
    Settings *settings = new Settings;
    int Width_Label   ,
        SizeStr       ,
        Heidh_Label   ,
        Size_Flow     ;
    const int MAX_SIZE = 500;
    bool change_func;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
