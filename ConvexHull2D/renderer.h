#pragma once

#include <QOpenGLFunctions>
#include<QOpenGLWidget>
#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>
#include<QOpenGLVertexArrayObject>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObject>

class Renderer:
        public QOpenGLWidget
        , protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    Renderer(QWidget *parent);
    ~Renderer();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

public slots:
    void updateData(std::vector<QVector3D> points, std::vector<unsigned int> hull);
private:

    QMatrix4x4 _model;
    QMatrix4x4 _proj;
    QOpenGLShaderProgram* _program{nullptr};
    QOpenGLVertexArrayObject _vao;
   // unsigned int _pointsCircleBuffer = static_cast<unsigned int>(-1);
    //unsigned int _pointsBuffer = static_cast<unsigned int>(-1);
    QOpenGLBuffer _pointsCircleBuffer;

    QOpenGLBuffer _pointsBuffer;



    void createVAO();
    void readFile(std::string fileName);
    void findMinMax();
    std::vector<QVector3D> _pointsHull;
    std::vector<QVector3D> _points;

    QVector3D _min;
    QVector3D _max;

};



