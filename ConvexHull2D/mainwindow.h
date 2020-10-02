#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "convexhull2d.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_fileButton_clicked();

    void on_pointsSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    ConvexHull2D *_convexHull;
};
#endif // MAINWINDOW_H
