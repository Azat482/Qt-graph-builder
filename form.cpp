#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->widget->setInteractions(QCP::iRangeDrag |
                                QCP::iSelectAxes |
                                QCP::iSelectLegend |
                                QCP::iSelectPlottables);
     ui->widget->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения

    ui->widget->setAttribute(Qt::WA_AcceptTouchEvents);
    ui->widget->grabGesture(Qt::PinchGesture);

    connect(ui->pushButton, SIGNAL(clicked()) , this, SLOT(H_call()) );

}

Form::~Form()
{
    delete ui;
}

void Form::H_call()
{
    emit H_show();
    this->hide();
}

void Form::setGraphSS(QVector<double> X_val, QVector<double> Y_val, bool mode)
{

    QPen pen;// grid;
    pen.setColor(QColor(59, 59, 245));
    pen.setWidth(2);
   // grid.setColor(QColor(240, 240, 240));
    ui->widget->clearGraphs();

  //  qDebug() << mode << endl;
    switch(mode)
    {
      case true:  ui->widget->addGraph(); break;
      case false: ui->widget->addGraph(ui->widget->yAxis, ui->widget->xAxis); break;
    }

    //////////////////////////////////////////////////

    //////////////////////////////////////////////////

    ui->widget->yAxis->setBasePen(QPen(Qt::white));
    ui->widget->yAxis->setTickPen(QPen(Qt::white));
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
   // ui->widget->yAxis->grid()->setSubGridVisible(true);
    ui->widget->yAxis->setTickLabelColor(Qt::white);
    ui->widget->yAxis->setLabelColor(Qt::blue);


    ui->widget->xAxis->setBasePen(QPen(Qt::white));
    ui->widget->xAxis->setTickPen(QPen(Qt::white));
    ui->widget->xAxis->setSubTickPen(QPen(Qt::white));
   // ui->widget->xAxis->grid()->setSubGridVisible(true);
    ui->widget->xAxis->setTickLabelColor(Qt::white);
    ui->widget->xAxis->setLabelColor(Qt::blue);

    ui->widget->graph(0)->setData(X_val, Y_val);
    ui->widget->graph(0)->setPen(pen);
    ui->widget->setBackground(QColor(0 ,0, 0));


    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->xAxis->setRange(-4, 4);
    ui->widget->yAxis->setRange(-4, 4);

    ui->widget->replot();
    X_val.clear();
    Y_val.clear();


}

bool Form::event(QEvent *Ev){
    switch (Ev->type())
    {
    case QEvent::Gesture: {
                QGestureEvent *gestureEve = static_cast<QGestureEvent*>(Ev);
                if( QGesture *pinch = gestureEve->gesture(Qt::PinchGesture) )
                {
                    QPinchGesture *pinchEve = static_cast<QPinchGesture *>(pinch);
                  //  qreal scaleFactor = pinchEve->totalScaleFactor( );
                  // if( scaleFactor > 1.0 ){
                  //      scaleFactor *= 10;
                  //  }else{
                  //      scaleFactor *= -10;
                  //  }
                  //  QWheelEvent *wheelEve = new QWheelEvent( currentTouchPointPos, scaleFactor, Qt::NoButton, Qt::NoModifier, Qt::Vertical );
                  // ui->widget->wheelEvent( wheelEve );
                    ///////////////////////////////////////////
                    qreal scaleFactor = pinchEve->totalScaleFactor( );
                    if( scaleFactor > 1.0 ){
                        scaleFactor = fabs(1.0 - scaleFactor) - 1.0;
                    }else if( scaleFactor < 1.0 ){
                        scaleFactor = fabs(1.0 - scaleFactor) + 1.0;
                    }

                    if( scaleFactor < 0.98 )
                        scaleFactor = 0.98;
                    else if( scaleFactor > 1.02 )
                        scaleFactor = 1.02;

                    ui->widget->yAxis->scaleRange( scaleFactor, ui->widget->yAxis->range().center());
                    ui->widget->xAxis->scaleRange( scaleFactor, ui->widget->xAxis->range().center());
                    ui->widget->replot();
                    ///////////////////////////////////////////
                }
                return true;
            }
            case QEvent::TouchBegin:
            case QEvent::TouchUpdate:
            case QEvent::TouchEnd: {
                QTouchEvent *touchEvent = static_cast<QTouchEvent *>( Ev );
                QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints( );
                if( touchPoints.count( ) == 1 ){
                    const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first( );
                    currentTouchPointPos = touchPoint0.pos();
                    QMouseEvent *mouseEve = new QMouseEvent(QEvent::MouseButtonPress,currentTouchPointPos,Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
                    if( touchEvent->touchPointStates() == (Qt::TouchPointStates)Qt::TouchPointPressed ){
                        this->mousePressEvent( mouseEve );
                    }else if( touchEvent->touchPointStates() == (Qt::TouchPointStates)Qt::TouchPointMoved ){
                        this->mouseMoveEvent( mouseEve );
                    }else if( touchEvent->touchPointStates() == (Qt::TouchPointStates)Qt::TouchPointReleased ){
                        this->mouseReleaseEvent( mouseEve );
                    }
                }
                return true;
            }
            default: {
                break;
            }
    }

    return QWidget::event( Ev );
}
