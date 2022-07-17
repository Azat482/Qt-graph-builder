
#include <QApplication>
#include <mainwindow.h>
#include <creatingfunc.h>
#include <form.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow Head;
    //Form Maker;
    CreatingFunc G_values;
    Head.show(); //usualy
    //Maker.show();
    //Head.showFullScreen();

    QObject::connect(&Head, SIGNAL(graph_set(QString, int, int, int, double, bool)), &G_values, SLOT(set_value(QString, int, int, int, double, bool)));
    QObject::connect(&G_values, SIGNAL(in_CT()), &Head, SLOT(SHOW()) );


    return a.exec();
}
