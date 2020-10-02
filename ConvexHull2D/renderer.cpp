#include "renderer.h"
#include <iostream>
#include <fstream>
#include <QOpenGLFunctions>
#include<QOpenGLWidget>
#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>

Renderer::Renderer(QWidget* parent)
        :QOpenGLWidget(parent)
{

}

void Renderer::readFile(std::string fileName)
{
    fileName = "../ConvexHull2D/fecho1.txt";
    std::ifstream file;
    file.open(fileName);
    if (!file)
    {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    float x,y;
    while (file >> x >> y)
    {
        QVector3D p(x, y, 0);
        _points.push_back(p);
    }

    file.close();
}



void Renderer::findMinMax()
{
    _min = _max = _points[0];
    for(auto point : _points)
    {
        if(point.x() > _max.x())
        {
            _max.setX(point.x());
        }
        else if (point.x() < _min.x())
        {
            _min.setX(point.x());
        }
        if(point.y() > _max.y())
        {
            _max.setY(point.y());
        }
        else if (point.y() < _min.y())
        {
            _min.setY(point.y());
        }
    }
}


//bool myfunction (QVector3D v1,QVector3D v2)
//{
//    return (v1.x()<v2.x());
//}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();
    glLineWidth(1.5f);
    glPointSize(6.0f);

    makeCurrent();
    glViewport(0,0,width(),height());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0,0,0,1);
    glViewport(0,0,width(),height());

    _program = new QOpenGLShaderProgram();

    //Adicionando shaders ao programa

    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertexShader.glsl");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragmentShader.glsl");

    //Linka shaders que foram adicionados ao programa
    _program->link();

    if (!_program->isLinked())
    {
        std::cout<<"Problemas ao linkar shaders de Gbuffer"<<std::endl;
    }

    _program->bind();

    //readFile("");
    //std::sort(_points.begin(),_points.end(), myfunction);
    for(auto point : _points)
    {
        std::cout<<point.x()<< " "<<point.y()<<std::endl;
    }
    //createVAO();
    _pointsCircleBuffer.create();
    _pointsBuffer.create();

}



void Renderer::resizeGL(int w, int h)
{
    //Atualizar a viewport
    glViewport(0,0,w,h);
}



void Renderer::paintGL()
{
    _program->bind();
    //glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POINTS);
    glEnd();

    _vao.bind();
     _proj.setToIdentity();
     float left = _min.x() - 200;
     float right = _max.x()  + 200;
     float bottom = _min.y() - 200;
     float up = _max.y() + 200;
     _proj.ortho(left, right, bottom, up, 0, 100);
     QMatrix4x4 mvp = _proj;
     _program->setUniformValue("mvp", mvp);
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


     //Desenha a bezier
     _pointsBuffer.bind();
     _pointsBuffer.allocate( _points.data(), (int)_points.size()*sizeof(QVector3D) );
     _program->enableAttributeArray(0);
     _program->setAttributeBuffer(0,GL_FLOAT,0,3,sizeof(QVector3D));
     _program->setUniformValue("color", QVector3D(1,1,1));

     glDrawArrays(GL_POINTS, 0, (int)_points.size());

     _pointsBuffer.bind();
     _program->setUniformValue("color", QVector3D(0.6,0.2,0.6));
     _pointsBuffer.allocate( _pointsHull.data(), (int)_pointsHull.size()*sizeof(QVector3D) );
     glDrawArrays(GL_LINE_STRIP, 0, (int)_pointsHull.size());
}



void Renderer::updateData(std::vector<QVector3D> points, std::vector<unsigned int> hull)
{
    _pointsHull.clear();
    _points = points;
    findMinMax();
    _proj.setToIdentity();
    float left = _min.x() - 10;
    float right = _max.x()  + 10;
    float bottom = _min.y() - 10;
    float up = _max.y() + 10;
    _proj.ortho(left, right, bottom, up, 0, 100);

    for(auto ind : hull)
    {
        _pointsHull.push_back(points[ind]);
    }
    update();
}



Renderer::~Renderer()
{

}



void Renderer::createVAO()
{
    //Criando e configurando vao
    _vao.create();
    _vao.bind();

//    //Criando buffer de pontos dos vértices
//    glGenBuffers(1, &_pointsCircleBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, _pointsCircleBuffer);
//    glBufferData(GL_ARRAY_BUFFER, _pointsCircle.size()*sizeof(QVector3D), _pointsCircle.data(), GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
//    glEnableVertexAttribArray(0);

}

