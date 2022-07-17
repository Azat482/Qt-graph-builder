#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <creatingfunc.h>
#include <QValidator>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->setText("0");

    change_func = true;
    ui->funcS->insertItem(0, "f(x) = y");
    ui->funcS->insertItem(1, "f(y) = x");

    ///////////////////////////////////////////////////////////////////////
    connect(ui->pushButton,    SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_2,  SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_3,  SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_4,  SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_5,  SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_6,  SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_7,  SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_8,  SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_9,  SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_19, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    connect(ui->pushButton_25, SIGNAL(clicked()), this, SLOT(G_BUTTON()) );
    ///////////////////////////////////////////////////////////////////////



    connect(ui->CAL_FRAPH_BUTTON, SIGNAL(clicked()), this, SLOT(G_call()) );


    ///////////////////PIXMAP OF BUTTONS///////////////////////////////////




    //QPixmap G_func("E:\\My programms\\pictures_for_programs//G_Func");
    //ui->CAL_FRAPH_BUTTON->setIcon(G_func);
    //ui->CAL_FRAPH_BUTTON->setIconSize(ui->CAL_FRAPH_BUTTON->size());




    ///////////////////END OF PIXMAP BUTTONS///////////////////////////////
    connect(settings, SIGNAL(call_H()), this, SLOT(SHOW()) );



}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::G_BUTTON()                       //setEXP
{
   O_time = ((QPushButton*)sender())->text();
   Width_Label = ui->label->width();
   Heidh_Label = ui->label->height();
   SizeStr = Width_Label/19 ;
   Size_Flow = Heidh_Label/19 - 1;

   if(Exp.size() <= (MAX_SIZE - 3))
   {
   Exp+=O_time;
   }

  // qDebug() << SizeStr << '\n' << Width_Label << '\n' << Size_Flow << endl <<
  //             "EXP: " << Exp.size() << endl << "SIZESTR: " << SizeStr << endl;

   ui->label->setText(Exp);




}


void MainWindow::on_clear_button_clicked()         //CLEANING
{
    Exp.clear();
    ui->label->setText(Exp);

}

void MainWindow::on_pushButton_back_clicked()       // -1 SIMPHOL
{
    QString  Buff;
    QString::iterator it = Exp.end();
    --it;
    *it = '#';
    for(int i = 0; Exp[i] != '#' && !Exp.isEmpty() ; i++) Buff[i] = Exp[i];
    Exp = Buff;
    ui->label->setText(Exp);
}


void MainWindow::G_call()                          //CALLING GRAPH_FUNC
{
   int MaxAll = settings->comp();
   int MaxV = settings->MaxValue();
   int MinV = settings->MinValue();
   double step = settings->Step();
   emit graph_set(Exp, MaxAll, MaxV, MinV, step, change_func);
   this->hide();
}

void MainWindow::SHOW()
{
    this->show();

}








void MainWindow::on_pushButton_22_clicked()
{
    this->hide();
    settings->show();

}

void MainWindow::on_funcS_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0: change_func = true; ui->pushButton_17->setText("X"); break;
    case 1: change_func = false; ui->pushButton_17->setText("Y"); break;
    }

}
