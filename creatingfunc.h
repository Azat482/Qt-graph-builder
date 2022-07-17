#ifndef CREATINGFUNC_H
#define CREATINGFUNC_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <ctype.h>
#include <cstdlib>
#include <QStack>
#include <math.h>
#include <form.h>
#include<QVector>
#include<qmath.h>

class CreatingFunc : public QWidget
{
    Q_OBJECT
private:
    Form *Maker = new Form;
    QChar     G_dig[500];
    QVector<double>num_X;
    QVector<double>num_Y;
    enum signs {
                plus = 1, //    ПЛЮС             1
                minus,    //    МИНУС            2
                mult ,    //    УМНОЖЕНИЕ        3
                div  ,    //    ДЕЛЕНИЕ          4
                deg  ,    //    СТЕПЕНЬ          5
                Esin  ,   //    СИНУС            6
                Ecos  ,   //    КОСИНУС          7
                Esqrt ,   //    КОРЕНЬ           8
                FE   ,    //    ЗАМЕНЕННЫЙ       9
                Eend  ,   //    КОНЕЦ            10
                closeSK,  //    ЗАКРЫТАЯ СКОБКА  11
                openSK    //    ОТКРЫТАЯ СКОБКА  12
                };
    signs symbols, Buff_symbols;
    QStack<double>   digit;
    QStack<signs> symbol;
public:
    CreatingFunc();
    void show_values();
    double set_value(QStack<double> &dig, QStack<signs> &sym);
private slots:
    void set_value(QString buff, int M_ALL, int MaxV, int MinV, double STP, bool chan);
    void H_in();
signals:
    void in_CT();
};

#endif // CREATINGFUNC_H
