#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QVector>
#include <QPanGesture>
#include <QPinchGesture>
#include <QWheelEvent>
//#include <

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    void setGraphSS(QVector<double> X_val, QVector<double> Y_val, bool mode = true);
    ~Form();

private:
    Ui::Form *ui;
protected:
    QPointF currentTouchPointPos;
    bool event(QEvent *Ev);
private slots:
    void H_call();
signals:
    void H_show();
};

#endif // FORM_H
