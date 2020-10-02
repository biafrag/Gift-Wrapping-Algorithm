#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderer.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _convexHull = new ConvexHull2D();
    ui->setupUi(this);
    setFixedSize(1800,900);
    ui->pointsSpinBox->setVisible(false);
    connect(_convexHull, &ConvexHull2D::giftWrappingFinished, ui->openGLWidget, &Renderer::updateData);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    _convexHull->giftWrappingAlgorithm();
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->pointsSpinBox->setVisible(true);
    ui->fileButton->setVisible(false);
    _convexHull->generatePoints(ui->pointsSpinBox->value());
}

void MainWindow::on_radioButton_clicked()
{
    ui->pointsSpinBox->setVisible(false);
    ui->fileButton->setVisible(true);
}

void MainWindow::on_fileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Importar Pontos"), "", tr("Arquivos de malha (*.txt)"));

    if (!fileName.isEmpty() )
    {
        std::vector<std::string> v;
        v.push_back(fileName.toStdString());
        _convexHull->readFile(fileName.toStdString());
    }
}

void MainWindow::on_pointsSpinBox_valueChanged(int arg1)
{
    _convexHull->generatePoints(arg1);

}
