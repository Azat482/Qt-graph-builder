#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <qmath.h>
#include <QSettings>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    int comp();
    double Step();
    int MinValue();
    int MaxValue();
    ~Settings();

private slots:



    void on_EXITANDSAVE_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

private:
    Ui::Settings *ui;
    int MinVal;
    int MaxVal;
    double step;
    QSettings* settings;
    void load_settings();
    void save_settings();
signals:
    void call_H();

};

#endif // SETTINGS_H
