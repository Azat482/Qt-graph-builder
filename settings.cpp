#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    settings = new QSettings("AzApp", "Graph Maker", this);
    ui->setupUi(this);
    ui->spinBox->setRange(-1000000, 1000000);
    ui->spinBox_2->setRange(-1000000, 1000000);
    ui->doubleSpinBox_3->setRange(0.001, 1000);

    load_settings();
    ui->spinBox->setValue(MinVal);
    ui->spinBox_2->setValue(MaxVal);
    ui->doubleSpinBox_3->setValue(step);


}

Settings::~Settings()
{
    //save_settings();
    delete ui;
}



void Settings::on_EXITANDSAVE_clicked()
{
    save_settings();
    emit call_H();
    this->hide();
}

void Settings::on_spinBox_valueChanged(int arg1)
{
    MinVal = arg1;
}

void Settings::on_spinBox_2_valueChanged(int arg1)
{
    MaxVal = arg1;
}

void Settings::on_doubleSpinBox_3_valueChanged(double arg1)
{
    step = arg1;
}

void Settings::load_settings()
{
    MinVal = settings->value("min", -100).toInt() ;
    MaxVal = settings->value("max", 100).toInt();
    step = settings->value("step", 0.1).toDouble();
}

void Settings::save_settings()
{
    settings->setValue("min", MinVal);
    settings->setValue("max", MaxVal);
    settings->setValue("step", step);
}

int Settings::comp()
{
    int sum = qAbs(MinVal) + qAbs(MaxVal);
    return sum/step;
}

double Settings::Step()
{
    return step;
}

int Settings::MinValue()
{
    return MinVal;
}

int Settings::MaxValue()
{
    return MaxVal;
}
