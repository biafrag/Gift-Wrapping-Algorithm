#include "convexhull2d.h"
#include <fstream>
#include <iostream>

ConvexHull2D::ConvexHull2D()
{
    //readFile("");
    //giftWrappingAlgorithm();
}


bool myfunction (QVector3D v1,QVector3D v2)
{
    return (v1.x()<v2.x());
}



bool ConvexHull2D::isOrientedAntiClockWise(QVector3D p1, QVector3D p2, QVector3D p3)
{
    //Fazendo determinante
//    float det = (p1.x() * p2.y() + p2.x()*p3.y()) - (p2.x()*p1.y() + p3.x()*p2.y());
    QVector3D det = QVector3D::crossProduct(p3 - p1, p1 - p2);
    if(det.z() > 0)
        return true;
    return false;
}

void ConvexHull2D::incrementalAlgorithm()
{
    std::sort(_points.begin(),_points.end(), myfunction);

    for(auto point : _points)
    {
        std::cout<<point.x()<< " "<<point.y()<<std::endl;
    }

    //3 First vertexes
    if(isOrientedAntiClockWise(_points[0], _points[1], _points[2]))
    {
        _hull.push_back(0);
        _hull.push_back(1);
        _hull.push_back(2);
    }
    else
    {
        _hull.push_back(2);
        _hull.push_back(1);
        _hull.push_back(0);
    }

    for(unsigned int i = 3; i < _points.size(); i++)
    {
        //Adiciona ponto a direita na ordem correta
        QVector3D point = _points[i];

        for(unsigned int j = 0; j < _hull.size() - 1; j++)
        {
            unsigned int ind1 = _hull[j];
            unsigned int ind2 = _hull[j + 1];
            if(isOrientedAntiClockWise(point, _points[ind1], _points[ind2]))
            {
                _hull.insert(_hull.begin() + j, i);
                break;
            }
        }

        //Elimina pontos do fecho antigo
    }
}


unsigned int ConvexHull2D::findFirstPoint()
{
    unsigned int indMenor = 0;
    for(unsigned int i = 0; i < _points.size(); i++)
    {
        if(_points[i].x() < _points[indMenor].x())
        {
            indMenor = i;
        }

    }
    return  indMenor;
}

void ConvexHull2D::giftWrappingAlgorithm()
{
    unsigned int indFirst = findFirstPoint();
    _hull.push_back(indFirst);
    unsigned int ind = indFirst;
    unsigned int currentInd = ind;
    unsigned int indStart;
    QVector3D currentVec;
    if(indFirst != 0)
    {
        currentVec = _points[0] - _points[ind];
        indStart = 0;
    }
    else
    {
        currentVec = _points[1] - _points[ind];
        indStart = 1;
    }
    do
    {
        ind = indStart;
        for(unsigned int i = 0; i < _points.size(); i++)
        {
            if(i != currentInd && _alreadyOnHull[i] == false)
            {
                if(i !=  ind)
                {

                    QVector3D vecCompare = _points[i] - _points[currentInd];
                    QVector3D cross = QVector3D::crossProduct(currentVec, vecCompare);
                    if(cross.z() < 0)
                    {
                        currentVec = vecCompare;
                        ind = i;
                    }
                    else
                    {
                        indStart = i;
                    }
                }
            }
        }
        _hull.push_back(ind);
        currentInd = ind;
        _alreadyOnHull[currentInd] = true;
        currentVec = _points[indStart] - _points[ind];

    }while(ind != indFirst);
    giftWrappingFinished(_points, _hull);

}

void ConvexHull2D::readFile(std::string fileName)
{
    //fileName = "../ConvexHull2D/fecho1.txt";
    _points.clear();
    _hull.clear();
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
    _alreadyOnHull = std::vector<bool>(_points.size(), false);
    giftWrappingFinished(_points, _hull);

}

std::vector<QVector3D> ConvexHull2D::sortVectorByX()
{
    std::vector<QVector3D> sorted;
    return sorted;
}



void ConvexHull2D::generatePoints(unsigned int n)
{
    _points.clear();
    _hull.clear();

    float LO = -999.9;
    float HI = 999.9;
    for(unsigned int i = 0; i < n; i++)
    {
        float x = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        float y = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));

        _points.push_back(QVector3D(x, y, 0));
    }
    giftWrappingFinished(_points, _hull);
    _alreadyOnHull = std::vector<bool>(_points.size(), false);

}


