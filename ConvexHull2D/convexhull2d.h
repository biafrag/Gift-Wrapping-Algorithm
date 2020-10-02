#pragma once
#include <vector>
#include <QVector3D>
#include<QObject>



class ConvexHull2D : public QObject
{
    Q_OBJECT
public:
    ConvexHull2D();
    void incrementalAlgorithm();
    void giftWrappingAlgorithm();
    unsigned int findFirstPoint();
    void readFile(std::string fileName);
    std::vector<QVector3D> sortVectorByX();
    void generatePoints(unsigned int n);


signals:
    void giftWrappingFinished(std::vector<QVector3D> points, std::vector<unsigned int> hull);
private:
    std::vector<QVector3D> _points;
    std::vector<bool> _alreadyOnHull;
    std::vector<unsigned int> _hull;
    bool isOrientedAntiClockWise(QVector3D p1, QVector3D p2, QVector3D p3);
};
